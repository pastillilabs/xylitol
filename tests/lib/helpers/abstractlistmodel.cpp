#include "abstractlistmodel.h"

#include <xylitol/util.h>
#include <xylitol/templates.h>

#include <QDebug>

namespace {

void fromVariantMap(AbstractListModel::Item& item, const QVariantMap& variantMap, QObject* parent) {
    const QVariant stringValue = variantMap.value(QLatin1String("string"));
    const QVariant enumValue = variantMap.value(QLatin1String("enum"));
    const QVariant objectValue = variantMap.value(QLatin1String("object"));

    delete item.mObject;
    item.mObject = nullptr;

    item.mString = stringValue.isNull() ? item.mString : stringValue.toString();
    item.mEnum = enumValue.isNull() ? item.mEnum : static_cast<AbstractListModel::Enum>(enumValue.toInt());

    if(!objectValue.isNull()) {
        item.mObject = new Object(parent);
        Xylitol::fromVariant(*item.mObject, objectValue);
    }
}

QVariantMap toVariantMap(const AbstractListModel::Item& item) {
    QVariantMap variantMap;
    variantMap.insert(QLatin1String("string"), item.mString);
    variantMap.insert(QLatin1String("enum"), static_cast<int>(item.mEnum));
    variantMap.insert(QLatin1String("object"), item.mObject ? Xylitol::toVariant(*item.mObject) : QVariant());

    return variantMap;
}

} // namespace

AbstractListModel::Item::Item() {}

AbstractListModel::Item::Item(const QString& string, Enum enumeration, Object* object)
    : mString(string)
    , mEnum(enumeration)
    , mObject(object) {}

bool AbstractListModel::Item::operator==(const Item& other) const {
    return (mString == other.mString) &&
           (mEnum == other.mEnum) &&
           (Xylitol::toVariant(QVariant::fromValue(mObject)) == Xylitol::toVariant(QVariant::fromValue(other.mObject)));
}

AbstractListModel::AbstractListModel(QObject* parent)
    : Xylitol::AbstractListModel(parent) {}

AbstractListModel::~AbstractListModel() {
    const auto& container = mContainer;
    for(const Item& item : container) {
        delete item.mObject;
    }
}

void AbstractListModel::reset(const QVector<Item>& items) {
    beginResetModel();
    mContainer = items;
    endResetModel();
}

void AbstractListModel::append(const Item& item) {
    const int index = mContainer.size();

    beginInsertRows(QModelIndex(), index, index);
    mContainer.append(item);
    endInsertRows();
}

void AbstractListModel::remove(int first, int last) {
    xylitolRemove(first, last);
}

void AbstractListModel::move(int first, int last, int index) {
    xylitolMove(first, last, index);
}

void AbstractListModel::set(int index, const Item& item) {
    if(index >= 0 && index < mContainer.count()) {
        mContainer.replace(index, item);
        const auto modelIndex = this->index(index);
        emit dataChanged(modelIndex, modelIndex);
    }
    else {
        qWarning() << "Invalid index" << index;
    }
}

const QVector<AbstractListModel::Item>& AbstractListModel::container() const {
    return mContainer;
}

int AbstractListModel::rowCount(const QModelIndex& /*parent*/) const {
    return mContainer.count();
}

QVariant AbstractListModel::data(const QModelIndex& index, int role) const {
    if(index.isValid()) {
        const Item& item = mContainer.at(index.row());

        switch(role) {
        case RoleString:
            return item.mString;
        case RoleEnum:
            return static_cast<int>(item.mEnum);
        case RoleObject:
            return QVariant::fromValue(item.mObject);
        default:
            return QVariant();
        }
    }

    return QVariant();
}

QHash<int, QByteArray> AbstractListModel::roleNames() const {
    static const QHash<int, QByteArray> names{
        {RoleString, "string"},
        {RoleEnum, "enum"},
        {RoleObject, "object"}
    };
    return names;
}

QVariantList AbstractListModel::xylitolToVariantList(int first, int last, const QVariantList& /*roles*/) const {
    QVariantList variantList;

    for(int index = first; index <= last; ++index) {
        const QModelIndex modelIndex = this->index(index);
        if(modelIndex.isValid()) {
            variantList.append(toVariantMap(mContainer.at(index)));
        }
        else {
            qWarning() << "Invalid index" << index << "in range" << first << last;
        }
    }

    return variantList;
}
void AbstractListModel::xylitolFromVariantList(const QVariantList& variantList, const QVariantList& roles) {
    beginResetModel();

    for(int i = 0; i < mContainer.count(); ++i) {
        for(const QVariant& roleVariant : roles) {
            delete data(index(i), roleVariant.toInt()).value<QObject*>();
        }
    }
    mContainer.clear();

    for(const QVariant& variant : variantList) {
        Item item;
        fromVariantMap(item, variant.toMap(), this);
        mContainer.append(item);
    }

    endResetModel();
}

void AbstractListModel::xylitolInsert(int first, const QVariantList& variantList, const QVariantList& /*roles*/) {
    const int last = first + variantList.count() - 1;
    if((first >= 0) && (first <= mContainer.count())) {
        beginInsertRows(QModelIndex(), first, last);

        for(int i = first; i <= last; ++i) {
            Item item;
            fromVariantMap(item, variantList.at(i - first).toMap(), this);
            mContainer.insert(i, item);
        }

        endInsertRows();
    }
    else {
        qWarning() << "Invalid range" << first << last;
    }
}

void AbstractListModel::xylitolRemove(int first, int last) {
    if((first >= 0) && (first < mContainer.count()) &&
        (last >= 0 && last < mContainer.count())) {
        beginRemoveRows(QModelIndex(), first, last);

        while(last >= first) {
            mContainer.removeAt(last);
            --last;
        }

        endRemoveRows();
    }
    else {
        qWarning() << "Invalid range" << first << last;
    }
}

void AbstractListModel::xylitolMove(int first, int last, int index) {
    if((first >= 0) && (first < mContainer.count()) &&
        (last >= 0) && (last < mContainer.count()) &&
        (index >= 0) && (index <= mContainer.count()) &&
        ((index < first) || (index > last))) {
        const int count = last - first + 1;
        const bool after = index > last;

        beginMoveRows(QModelIndex(), first, last, QModelIndex(), index);

        // Extract items from the array
        QVector<Item> moving;
        while(last >= first) {
            moving.append(mContainer.takeAt(first));
            --last;
        }

        // Move index if placing items after previous position
        if(after) {
            index -= count;
        }

        // Insert items to new position
        while(moving.count()) {
            mContainer.insert(index, moving.takeFirst());
            ++index;
        }

        endMoveRows();
    }
    else {
        qWarning() << "Invalid range" << first << last << index;
    }
}

void AbstractListModel::xylitolSet(int first, const QVariantList& variantList, const QVariantList& roles) {
    const int last = first + variantList.count() - 1;
    if((first >= 0) && (first < mContainer.count()) &&
       (last >= 0) && (last < mContainer.count())) {
        for(int i = first; i <= last; ++i) {
            Item item = mContainer.at(i);
            fromVariantMap(item, variantList.at(i - first).toMap(), this);
            mContainer.replace(i, item);
        }

        QList<int> roleList;
        for(const auto& item : roles) {
            roleList.append(item.toInt());
        }

        emit dataChanged(index(first), index(last), Xylitol::toContainer<QVector<int>>(roles));
    }
    else {
        qWarning() << "Invalid range" << first << last;
    }
}
