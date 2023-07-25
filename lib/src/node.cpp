#include "xylitol/node.h"

#include "conversions.h"
#include "logging.h"
#include "shadowobject.h"
#include "xylitol/abstractlistmodel.h"
#include "xylitol/util.h"

#include <QGenericArgument>
#include <QMetaProperty>
#include <QMetaType>
#include <QModelIndex>
#include <QString>
#include <QStringList>

// clazy:excludeall=non-pod-global-static

namespace Xylitol {

namespace {

QObject* objectAtPath(QObject& root, const QVariantList& path) {
    QObject* object = &root;

    QVariantList temp = path;
    while(temp.count() > 1 && object) {
        const QString name = temp.takeAt(0).toString();
        const QStringList nameParts = name.split(QLatin1Char(':'));

        if(nameParts.count() == 1) { // QObject* property
            const int propertyIndex = object->metaObject()->indexOfProperty(name.toLatin1().data());
            const QMetaProperty metaProperty = object->metaObject()->property(propertyIndex);
            const QVariant value = metaProperty.read(object);

            if(value.canConvert<QObject*>()) {
                object = value.value<QObject*>();
            }
            else {
                qCDebug(xylitol) << "Path not found:" << path;
                object = nullptr;
            }
        }
        else if(nameParts.count() == 2) { // AbstractListModel* data
            const int index = nameParts.at(0).toInt();
            const QString roleName = nameParts.at(1);

            const AbstractListModel* model = qobject_cast<AbstractListModel*>(object);
            if(model && index >= 0 && index < model->rowCount()) {
                const int role = model->roleNames().key(roleName.toLatin1());
                const QVariant value = model->data(model->index(index), role);
                object = value.value<QObject*>();
            }
            else {
                qCDebug(xylitol) << "Path not found:" << path;
                object = nullptr;
            }
        }
    }

    return object;
}

void invoke(QObject& root, const QVariantList& path, const QVariantList& variantList) {
    QObject* object = objectAtPath(root, path);
    if(object) {
        const QMetaObject* metaObject = object->metaObject();

        const QString signature = path.last().toString();
        const int index = metaObject->indexOfMethod(signature.toLatin1().constData());
        if(index >= 0) {
            const QMetaMethod metaMethod = metaObject->method(index);

            QVariant gv[10];
            QGenericArgument ga[10];

            const int valueCount = variantList.count();
            if(valueCount == metaMethod.parameterCount()) {
                for(int i = 0; i < valueCount; ++i) {
                    gv[i] = fromVariant(variantList.at(i), metaMethod.parameterType(i));
                    ga[i] = QGenericArgument(metaMethod.parameterTypes().at(i), gv[i].constData());
                }
            }
            else {
                qCWarning(xylitol) << "Invalid amount of arguments for" << signature;
            }

            if(!metaMethod.invoke(object, ga[0], ga[1], ga[2], ga[3], ga[4], ga[5], ga[6], ga[7], ga[8], ga[9])) {
                qCWarning(xylitol) << "Failed to invoke" << signature << gv[0] << gv[1] << gv[2] << gv[3] << gv[4] << gv[5] << gv[6] << gv[7] << gv[8] << gv[9];
            }
        }
        else {
            qCWarning(xylitol) << "Method not found" << signature;
        }
    }
}

void update(QObject& root, const QVariantList& path, const QVariant& variant) {
    QObject* object = objectAtPath(root, path);
    if(object) {
        const QMetaObject* metaObject = object->metaObject();

        const QString name = path.last().toString();
        const int index = metaObject->indexOfProperty(name.toLatin1().constData());
        if(index >= 0) {
            const QMetaProperty metaProperty = metaObject->property(index);

            // Only stored && non-constant properties are updated
            if(metaProperty.isStored() && !metaProperty.isConstant()) {
                // If property is pointer type, delete previous value
                const QVariant value = metaProperty.read(object);
                const QMetaType metaType(metaProperty.userType());

                if(metaType.flags().testFlag(QMetaType::PointerToQObject)) {
                    delete value.value<QObject*>();
                }
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
                else if(metaType.flags().testFlag(QMetaType::PointerToGadget)) {
                    metaType.destroy(value.value<void*>());
                }
#endif

                Private::writeObjectProperty(*object, metaProperty, variant);
            }
        }
        else {
            qCWarning(xylitol) << "Property not found:" << name;
        }
    }
}

bool accept(Connection* connection, Socket::Action action, const QVariantList& path) {
    if(connection) {
        // Do not accept anything during initialization
        if(connection->action() == Socket::Action::ActionInitialize) {
            return false;
        }
        else {
            // Otherwise deny current path && action once
            if((connection->path() == path) && (connection->action() == action)) {
                connection->setAction(Socket::Action::ActionNone);
                connection->setPath({});
                return false;
            }
        }
    }

    return true;
}

} // namespace

Node::Node(QObject* parent)
    : QAbstractListModel(parent) {
    connect(this, &Node::targetChanged, this, [this](QObject* target) {
        delete mTargetShadow;
        mTargetShadow = nullptr;

        if(target) {
            mTargetShadow = new ShadowObject(*mTarget, this);
            connect(mTargetShadow, &ShadowObject::invoked, this, &Node::invoked);
            connect(mTargetShadow, &ShadowObject::updated, this, &Node::updated);
        }
    });
}

QObject* Node::target() const {
    return mTarget;
}

void Node::setTarget(QObject* target) {
    if(target != mTarget) {
        mTarget = target;
        emit targetChanged(target);
    }
}

bool Node::isInitialized() const {
    return mInitialized;
}

Connection* Node::parentConnection() const {
    return mParentConnection;
}

const QVector<Connection*>& Node::childConnectionContainer() const {
    return mChildConnections;
}

Connection* Node::activeConnection() const {
    return mActiveConnection;
}

void Node::setParentSocket(Socket* socket) {
    bool changed = false;

    if(mParentConnection && (&mParentConnection->socket() != socket)) {
        delete mParentConnection;
        mParentConnection = nullptr;
        changed = true;
    }

    if(!mParentConnection && socket) {
        mParentConnection = new Connection(*socket, this);
        setupConnection(*mParentConnection);
        changed = true;
    }

    if(changed) {
        setInitialized(socket == nullptr);
        emit parentConnectionChanged(mParentConnection);
    }
}

void Node::addChildSocket(Socket* socket) {
    if(socket) {
        Connection* connection = new Connection(*socket, this);
        setupConnection(*connection);

        const int index = mChildConnections.count();
        beginInsertRows(QModelIndex(), index, index);
        mChildConnections.append(connection);
        endInsertRows();

        // Automatically send initialize message
        if(mTarget) {
            emit socket->send(Socket::Action::ActionInitialize, {}, toVariant(*mTarget));
        }
    }
}

void Node::removeChildSocket(Socket* socket) {
    const auto it = std::find_if(std::begin(mChildConnections), std::end(mChildConnections), [socket](Connection* connection) {
        return &connection->socket() == socket;
    });
    if(it != std::end(mChildConnections)) {
        const int index = it - std::begin(mChildConnections);

        Connection* connection = (*it);

        beginRemoveRows(QModelIndex(), index, index);
        mChildConnections.removeOne(connection);
        endRemoveRows();

        connection->deleteLater();
    }
}

int Node::rowCount(const QModelIndex& /*parent*/) const {
    return mChildConnections.count();
}

QVariant Node::data(const QModelIndex& index, int role) const {
    if(index.isValid()) {
        switch(role) {
        case Qt::DisplayRole:
            return QVariant::fromValue(mChildConnections.at(index.row()));
        default:
            return QVariant();
        }
    }

    return QVariant();
}

void Node::setInitialized(bool initialized) {
    if(initialized != mInitialized) {
        mInitialized = initialized;
        emit initializedChanged(initialized);
    }
}

void Node::setupConnection(Connection& connection) {
    connect(&connection.socket(), &Socket::receive, this, [this, &connection](Socket::Action action, const QVariantList& path, const QVariant& data) {
        // Forward to all other connections first
        sendAll(action, path, data, &connection);

        if(mTarget) {
            // Set active connection and store path & action to it
            mActiveConnection = &connection;
            mActiveConnection->setAction(action);
            mActiveConnection->setPath(path);

            emit activeConnectionChanged(mActiveConnection);

            // Handle action
            switch(action) {
            case Socket::Action::ActionInitialize:
                fromVariant(*mTarget, data);

                // Clear active action & path before indicating initialized state.
                // Allows communication right after intialized signal.
                mActiveConnection->setAction(Socket::Action::ActionNone);
                mActiveConnection->setPath({});

                setInitialized(mTarget != nullptr);
                break;
            case Socket::Action::ActionInvoke:
                invoke(*mTarget, path, data.toList());
                break;
            case Socket::Action::ActionUpdate:
                update(*mTarget, path, data);
                break;
            default:
                qCWarning(xylitol) << "Invalid action";
                break;
            }

            // Clear active action, path & connection when done
            mActiveConnection->setAction(Socket::Action::ActionNone);
            mActiveConnection->setPath({});
            mActiveConnection = nullptr;
            emit activeConnectionChanged(mActiveConnection);
        }
        else {
            qCWarning(xylitol) << "Target not set";
        }
    });
}

void Node::sendAll(Socket::Action action, const QVariantList& path, const QVariant& data, Connection* source) {
    // Send to server Node, but skip if source
    if(mParentConnection && mParentConnection != source) {
        emit mParentConnection->socket().send(action, path, data);
    }

    // Send to all client Nodes except source
    const auto& childConnections = mChildConnections;
    for(Connection* client : childConnections) {
        if(client != source) {
            emit client->socket().send(action, path, data);
        }
    }
}

void Node::invoked(const QVariantList& path, const QVariantList& values) {
    if(accept(mActiveConnection, Socket::Action::ActionInvoke, path)) {
        QVariantList serializedValues;

        for(const QVariant& value : values) {
            serializedValues.append(toVariant(value));
        }

        sendAll(Socket::Action::ActionInvoke, path, serializedValues);
    }
}

void Node::updated(const QVariantList& path, const QVariant& value) {
    if(accept(mActiveConnection, Socket::Action::ActionUpdate, path)) {
        // Let's not convert binary property updates to allow client optimization
        sendAll(Socket::Action::ActionUpdate, path, Private::canConvertToByteArray(value) ? value : toVariant(value));
    }
}

} // namespace Xylitol
