#include "shadowobject.h"
#include "xylitol/abstractlistmodel.h"
#include "xylitol/templates.h"

#include <QMetaMethod>

namespace Xylitol {

namespace {

int objectIndex(const AbstractListModel& abstractListModel, const QObject& object) {
    const int count = abstractListModel.rowCount();

    const QHash<int, QByteArray> roleNames = abstractListModel.roleNames();
    for(int index = 0; index < count; ++index) {
        for(QHash<int, QByteArray>::ConstIterator iter = roleNames.cbegin(); iter != roleNames.cend(); ++iter) {
            const int role = iter.key();
            const QVariant value = abstractListModel.data(abstractListModel.index(index), role);
            if(value.value<QObject*>() == &object) {
                return index;
            }
        }
    }

    return -1;
}

} // namespace

ShadowObject::ShadowObject(const QObject& target, QObject* parent)
    : ShadowObjectBase(parent) {
    const QMetaObject* metaObject = target.metaObject();
    int propertyOffset = QObject::staticMetaObject.propertyCount();
    int methodOffset = QObject::staticMetaObject.methodCount();

    const int propertyCount = metaObject->propertyCount();
    const int methodCount = metaObject->methodCount();

    // Special handling for AbstractListModel target
    const AbstractListModel* model = qobject_cast<const AbstractListModel*>(&target);
    if(model) {
        metaObject = model->metaObject();
        propertyOffset = AbstractListModel::staticMetaObject.propertyCount();
        methodOffset = AbstractListModel::staticMetaObject.methodCount();

        connectModel(*model);
    }

    // Connect property changes to propertySink
    for(int i = propertyOffset; i < propertyCount; ++i) {
        const QMetaProperty metaProperty = metaObject->property(i);
        const QVariant value = metaProperty.read(&target);

        if(metaProperty.hasNotifySignal()) {
            if(metaProperty.isStored()) {
                connect(&target, metaProperty.notifySignal(), this, QMetaMethod::fromSignal(&ShadowObjectBase::propertySink));
            }

            mPropertyMap.insert(metaProperty.notifySignalIndex(), metaProperty);
        }

        // Connect QObject* based properties
        if(value.canConvert<QObject*>() && metaProperty.isStored()) {
            const QObject* object = value.value<QObject*>();
            if(object) {
                connectObjectProperty(*object, QString::fromLatin1(metaProperty.name()));
            }
        }
    }

    // Connect all other signals to signalSink
    const QList<int> propertySignals = mPropertyMap.keys();
    for(int i = methodOffset; i < methodCount; ++i) {
        const QMetaMethod metaMethod = metaObject->method(i);

        if(metaMethod.methodType() == QMetaMethod::Signal && !propertySignals.contains(i)) {
            connect(&target, metaMethod, this, QMetaMethod::fromSignal(&ShadowObjectBase::signalSink));
        }
    }
}

int ShadowObject::qt_metacall(QMetaObject::Call call, int id, void** argv) {
    if(call == QMetaObject::InvokeMetaMethod) {
        if(id == QMetaMethod::fromSignal(&ShadowObjectBase::signalSink).methodIndex()) {
            const QMetaMethod metaMethod = sender()->metaObject()->method(senderSignalIndex());
            const QVariantList path{QString::fromLatin1(metaMethod.methodSignature())};

            QVariantList values;
            const int parameterCount = metaMethod.parameterCount();
            for(int i = 0; i < parameterCount; ++i) {
                // Default unknown types to int
                int parameterType = metaMethod.parameterType(i);
                if(parameterType == QMetaType::UnknownType) {
                    parameterType = QMetaType::Int;
                }

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
                const QVariant value(QMetaType(parameterType), argv[i + 1]);
#else
                const QVariant value(parameterType, argv[i + 1]);
#endif
                values.append(value);
            }

            emit invoked(path, values);
        }
        else if(id == QMetaMethod::fromSignal(&ShadowObjectBase::propertySink).methodIndex()) {
            const QMetaProperty metaProperty = mPropertyMap.value(senderSignalIndex());
            const QVariant readValue(metaProperty.read(sender()));
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
            const QVariant value((metaProperty.userType() == QMetaType::QVariant) ? QVariant(QMetaType(metaProperty.userType()), &readValue) : readValue);
#else
            const QVariant value((metaProperty.userType() == QMetaType::QVariant) ? QVariant(metaProperty.userType(), &readValue) : readValue);
#endif
            const QString name = QString::fromLatin1(metaProperty.name());

            emit updated({name}, value);

            // Connect new QObject* properties
            if(value.canConvert<QObject*>()) {
                const QObject* object = value.value<QObject*>();
                if(object) {
                    connectObjectProperty(*object, name);
                }
            }
        }
    }

    return ShadowObjectBase::qt_metacall(call, id, argv);
}

void ShadowObject::connectModel(const AbstractListModel& abstractListModel) {
    // AbstractListModel method signatures to be called at the receiving end
    static const QVariantList fromJsonPath{QStringLiteral("xylitolFromVariantList(QVariantList,QVariantList)")};
    static const QVariantList insertPath{QStringLiteral("xylitolInsert(int,QVariantList,QVariantList)")};
    static const QVariantList removePath{QStringLiteral("xylitolRemove(int,int)")};
    static const QVariantList movePath{QStringLiteral("xylitolMove(int,int,int)")};
    static const QVariantList setPath{QStringLiteral("xylitolSet(int,QVariantList,QVariantList)")};

    const QHash<int, QByteArray> roleNames = abstractListModel.roleNames();
    const QVariantList roles = toVariantList(roleNames.keys());

    connect(&abstractListModel, &AbstractListModel::rowsInserted, this, [this, &abstractListModel, roles](const QModelIndex& /*parent*/, int first, int last) {
        const QVariantList values{first, abstractListModel.xylitolToVariantList(first, last, roles), QVariant::fromValue(roles)};
        emit invoked(insertPath, values);

        // Connect new object values
        connectObjectValues(abstractListModel, first, last, roles);
    });
    connect(&abstractListModel, &AbstractListModel::rowsRemoved, this, [this](const QModelIndex& /*parent*/, int first, int last) {
        const QVariantList values{first, last};
        emit invoked(removePath, values);
    });
    connect(&abstractListModel, &AbstractListModel::rowsMoved, this, [this](const QModelIndex& /*parent*/, int first, int last, const QModelIndex& /*destination*/, int index) {
        const QVariantList values{first, last, index};
        emit invoked(movePath, values);
    });
    connect(&abstractListModel, &AbstractListModel::modelReset, this, [this, &abstractListModel, roles] {
        const QVariantList values{abstractListModel.xylitolToVariantList(0, abstractListModel.rowCount() - 1, roles), QVariant::fromValue(roles)};
        emit invoked(fromJsonPath, values);

        // Connect all object values
        connectObjectValues(abstractListModel, 0, abstractListModel.rowCount() - 1, roles);
    });
    connect(&abstractListModel, &AbstractListModel::dataChanged, this, [this, &abstractListModel, roleNames](const QModelIndex& topLeft, const QModelIndex& bottomRight, const QVector<int>& roles) {
        const int first = topLeft.row();
        const int last = bottomRight.row();
        const QVariantList roleList = toVariantList(roles.isEmpty() ? abstractListModel.roleNames().keys() : roles.toList());

        const QVariantList values{first, abstractListModel.xylitolToVariantList(first, last, roleList), roleList};
        emit invoked(setPath, values);

        // Connect new object values
        connectObjectValues(abstractListModel, first, last, roleList);
    });

    // Connect all object values
    connectObjectValues(abstractListModel, 0, abstractListModel.rowCount() - 1, roles);
}

void ShadowObject::connectObjectProperty(const QObject& object, const QString& name) {
    const ShadowObject* shadowObject = new ShadowObject(object, this);

    connect(shadowObject, &ShadowObject::invoked, this, [this, name](const QVariantList& path, const QVariantList& values) {
        emit invoked(QVariantList{name} + path, values);
    });
    connect(shadowObject, &ShadowObject::updated, this, [this, name](const QVariantList& path, const QVariant& value) {
        emit updated(QVariantList{name} + path, value);
    });
}

void ShadowObject::connectObjectValues(const AbstractListModel& abstractListModel, int first, int last, const QVariantList& roles) {
    for(int i = first; i <= last; ++i) {
        const QModelIndex modelIndex = abstractListModel.index(i);
        for(const QVariant& roleVariant : roles) {
            const int role = roleVariant.toInt();
            const QVariant value = abstractListModel.data(modelIndex, role);
            if(value.canConvert<QObject*>()) {
                const QObject* object = value.value<QObject*>();
                if(object) {
                    connectObjectValue(abstractListModel, *object, role);
                }
            }
        }
    }
}

void ShadowObject::connectObjectValue(const AbstractListModel& abstractListModel, const QObject& object, int role) {
    static const QString itemMetaNameTemplate = QStringLiteral("%1:%2");

    const ShadowObject* shadowObject = new ShadowObject(object, this);
    const QString roleName = QString::fromLatin1(abstractListModel.roleNames().value(role));

    connect(shadowObject, &ShadowObject::invoked, this, [this, &abstractListModel, &object, roleName](const QVariantList& path, const QVariantList& values) {
        const int index = objectIndex(abstractListModel, object);
        emit invoked(QVariantList{itemMetaNameTemplate.arg(index).arg(roleName)} + path, values);
    });
    connect(shadowObject, &ShadowObject::updated, this, [this, &abstractListModel, &object, roleName](const QVariantList& path, const QVariant& value) {
        const int index = objectIndex(abstractListModel, object);
        emit updated(QVariantList{itemMetaNameTemplate.arg(index).arg(roleName)} + path, value);
    });
}

} // namespace Xylitol
