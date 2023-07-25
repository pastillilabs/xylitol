#include "listmodel.h"
#include "object.h"

#include <xylitol/util.h>

ListModel::ListModel(QObject* parent)
    : Xylitol::ListModel(parent) {}

void ListModel::reset(const Container& container) {
    beginResetModel();
    mContainer = container;
    endResetModel();
}

void ListModel::append(const Item& item) {
    const int index = mContainer.size();

    beginInsertRows(QModelIndex(), index, index);
    mContainer.append(item);
    endInsertRows();
}

void ListModel::remove(int first, int last) {
    xylitolRemove(first, last);
}

void ListModel::move(int first, int last, int index) {
    xylitolMove(first, last, index);
}

void ListModel::set(int index, const Item& item) {
    if(index >= 0 && index < mContainer.count()) {
        mContainer.replace(index, item);
        const auto modelIndex = this->index(index);
        emit dataChanged(modelIndex, modelIndex);
    }
    else {
        qWarning() << "Invalid index" << index;
    }
}

void ListModel::setString(int index, const QString& string) {
    if(index >= 0 && index < mContainer.count()) {
        Item item = mContainer.at(index);
        item.insert(RoleString, string);

        mContainer.replace(index, item);
        const auto modelIndex = this->index(index);
        emit dataChanged(modelIndex, modelIndex, {RoleString});
    }
    else {
        qWarning() << "Invalid index" << index;
    }
}

QHash<int, QByteArray> ListModel::roleNames() const {
    static const QHash<int, QByteArray> names{
        {RoleInteger, "integer"},
        {RoleString, "string"},
        {RoleObject, "object"}
    };
    return names;
}

QHash<int, int> ListModel::roleTypes() const {
    static const QHash<int, int> types{
        {RoleInteger, qMetaTypeId<int>()},
        {RoleString, qMetaTypeId<QString>()},
        {RoleObject, qMetaTypeId<Object*>()}
    };
    return types;
}
