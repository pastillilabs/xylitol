#include "Xylitol/listmodel.h"
#include "Xylitol/logging.h"
#include "Xylitol/util.h"
#include "Xylitol/templates.h"

#include <QMetaType>

namespace Xylitol {

namespace {

void fromVariantList(ListModel::Item& item, const QVariantList& variantList, const QVariantList& roles, ListModel& model, int index) {
    if(variantList.count() == roles.count()) {
        for(int i = 0; i < roles.count(); ++i) {
            const int role = roles.at(i).toInt();

            const QVariant oldValue = item.value(role);
            const QMetaType metaType(oldValue.userType());
            if(metaType.flags().testFlag(QMetaType::PointerToQObject)) {
                delete oldValue.value<QObject*>();
            }
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
            else if(metaType.flags().testFlag(QMetaType::PointerToGadget)) {
                metaType.destroy(oldValue.value<void*>());
            }
#endif

            item.insert(role, model.xylitolCreateRole(index, role, variantList.at(i)));
        }
    }
}

} // namespace

ListModel::ListModel(QObject* parent)
    : AbstractListModel(parent) {}

QHash<int, int> ListModel::roleTypes() const {
    static QHash<int, int> types = [this] {
        QHash<int, int> roleTypes;
        const QHash<int, QByteArray> roleNames = this->roleNames();
        for(QHash<int, QByteArray>::ConstIterator iter = roleNames.cbegin(); iter != roleNames.cend(); ++iter) {
            roleTypes.insert(iter.key(), QMetaType::QVariant);
        }

        return roleTypes;
    }();
    return types;
}

QVariant ListModel::xylitolCreateRole(int /*index*/, int role, const QVariant& variant) {
    return fromVariant(variant, roleTypes().value(role), this);
}

const ListModel::Container& ListModel::container() const {
    return mContainer;
}

int ListModel::rowCount(const QModelIndex& /*parent*/) const {
    return mContainer.count();
}

QVariant ListModel::data(const QModelIndex& index, int role) const {
    if(index.isValid()) {
        const Item& item = mContainer.at(index.row());
        if(item.contains(role)) {
            return item.value(role);
        }
        else {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
            return QVariant(QMetaType(roleTypes().value(role)), nullptr);
#else
            return QVariant(roleTypes().value(role), nullptr);
#endif
        }
    }

    return QVariant();
}

bool ListModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    bool success = false;

    if(index.isValid()) {
        Item item = mContainer.at(index.row());

        if(item.value(role) != value) {
            item.insert(role, value);
            mContainer.replace(index.row(), item);
            success = true;

            emit dataChanged(index, index, {role});
        }
    }

    return success;
}

QVariantList ListModel::xylitolToVariantList(int first, int last, const QVariantList& roles) const {
    QVariantList variantList;

    for(int index = first; index <= last; ++index) {
        const QModelIndex modelIndex = this->index(index);
        if(modelIndex.isValid()) {
            QVariantList values;
            for(const QVariant& roleVariant : roles) {
                values.append(toVariant(data(modelIndex, roleVariant.toInt())));
            }

            variantList.append(QVariant(values));
        }
        else {
            qCWarning(category) << "Invalid index" << index << "in range" << first << last;
        }
    }

    return variantList;
}

void ListModel::xylitolFromVariantList(const QVariantList& variantList, const QVariantList& roles) {
    beginResetModel();

    mContainer.clear();

    for(const QVariant& variant : variantList) {
        Item item;
        fromVariantList(item, variant.toList(), roles, *this, mContainer.count());
        mContainer.append(item);
    }

    endResetModel();
}

void ListModel::xylitolInsert(int first, const QVariantList& variantList, const QVariantList& roles) {
    const int last = first + variantList.count() - 1;
    if((first >= 0) && (first <= mContainer.count())) {
        beginInsertRows(QModelIndex(), first, last);

        for(int i = first; i <= last; ++i) {
            Item item;
            fromVariantList(item, variantList.at(i - first).toList(), roles, *this, i);
            mContainer.insert(i, item);
        }

        endInsertRows();
    }
    else {
        qCWarning(category) << "Invalid range" << first << last;
    }
}

void ListModel::xylitolRemove(int first, int last) {
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
        qCWarning(category) << "Invalid range" << first << last;
    }
}

void ListModel::xylitolMove(int first, int last, int index) {
    if((first >= 0) && (first < mContainer.count()) &&
        (last >= 0) && (last < mContainer.count()) &&
        (index >= 0) && (index <= mContainer.count()) &&
        ((index < first) || (index > last))) {
        const int count = last - first + 1;
        const bool after = index > last;

        if(beginMoveRows(QModelIndex(), first, last, QModelIndex(), index)) {
            // Extract items from the array
            Container moving;
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
            qCWarning(category) << "Invalid move" << first << last << index;
        }
    }
    else {
        qCWarning(category) << "Invalid range" << first << last << index;
    }
}

void ListModel::xylitolSet(int first, const QVariantList& variantList, const QVariantList& roles) {
    const int last = first + variantList.count() - 1;
    if((first >= 0) && (first < mContainer.count()) &&
        (last >= 0) && (last < mContainer.count())) {
        for(int i = first; i <= last; ++i) {
            Item item = mContainer.at(i);
            fromVariantList(item, variantList.at(i - first).toList(), roles, *this, i);
            mContainer.replace(i, item);
        }

        emit dataChanged(index(first), index(last), toContainer<QVector<int>>(roles));
    }
    else {
        qCWarning(category) << "Invalid range" << first << last;
    }
}

} // namespace Xylitol
