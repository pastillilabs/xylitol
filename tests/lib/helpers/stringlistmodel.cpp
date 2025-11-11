#include "stringlistmodel.h"

#include <Xylitol/templates.h>

#include <QDebug>

StringListModel::StringListModel(QObject* parent)
    : Xylitol::AbstractListModel(parent) {}

void StringListModel::reset(const QStringList& stringList) {
    beginResetModel();
    mContainer = stringList;
    endResetModel();
}

void StringListModel::append(const QString& string) {
    const int index = mContainer.size();

    beginInsertRows(QModelIndex(), index, index);
    mContainer.append(string);
    endInsertRows();
}

void StringListModel::remove(int first, int last) {
    xylitolRemove(first, last);
}

void StringListModel::move(int first, int last, int index) {
    xylitolMove(first, last, index);
}

void StringListModel::set(int index, const QString& string) {
    if(index >= 0 && index < mContainer.count()) {
        mContainer.replace(index, string);
        const auto modelIndex = this->index(index);
        emit dataChanged(modelIndex, modelIndex);
    }
    else {
        qWarning() << "Invalid index" << index;
    }
}

const QStringList& StringListModel::container() const {
    return mContainer;
}

int StringListModel::rowCount(const QModelIndex& /*parent*/) const {
    return mContainer.count();
}

QVariant StringListModel::data(const QModelIndex& index, int role) const {
    if(index.isValid()) {
        switch(role) {
        case Qt::DisplayRole:
            return mContainer.at(index.row());
        default:
            return QVariant();
        }
    }

    return QVariant();
}

QHash<int, QByteArray> StringListModel::roleNames() const {
    static const QHash<int, QByteArray> names{
        {Qt::DisplayRole, "string"}
    };
    return names;
}

QVariantList StringListModel::xylitolToVariantList(int first, int last, const QVariantList& /*roles*/) const {
    QVariantList variantList;

    for(int index = first; index <= last; ++index) {
        const QModelIndex modelIndex = this->index(index);
        if(modelIndex.isValid()) {
            variantList.append(mContainer.at(index));
        }
        else {
            qWarning() << "Invalid index" << index << "in range" << first << last;
        }
    }

    return variantList;
}

void StringListModel::xylitolFromVariantList(const QVariantList& variantList, const QVariantList& /*roles*/) {
    beginResetModel();

    mContainer.clear();

    for(const QVariant& item : variantList) {
        mContainer.append(item.toString());
    }

    endResetModel();
}

void StringListModel::xylitolInsert(int first, const QVariantList& variantList, const QVariantList& /*roles*/) {
    const int last = first + variantList.count() - 1;
    if((first >= 0) && (first <= mContainer.count())) {
        beginInsertRows(QModelIndex(), first, last);

        for(int i = first; i <= last; ++i) {
            mContainer.insert(i, variantList.at(i - first).toString());
        }

        endInsertRows();
    }
    else {
        qWarning() << "Invalid range" << first << last;
    }
}

void StringListModel::xylitolRemove(int first, int last) {
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

void StringListModel::xylitolMove(int first, int last, int index) {
    if((first >= 0) && (first < mContainer.count()) &&
        (last >= 0) && (last < mContainer.count()) &&
        (index >= 0) && (index <= mContainer.count()) &&
        ((index < first) || (index > last))) {
        const int count = last - first + 1;
        const bool after = index > last;

        beginMoveRows(QModelIndex(), first, last, QModelIndex(), index);

        // Extract items from the list
        QStringList moveList;
        while(last >= first) {
            moveList.append(mContainer.takeAt(first));
            --last;
        }

        // Move index if placing items after previous position
        if(after) {
            index -= count;
        }

        // Insert items to new position
        while(moveList.count()) {
            mContainer.insert(index, moveList.takeFirst());
            ++index;
        }

        endMoveRows();
    }
    else {
        qWarning() << "Invalid range" << first << last << index;
    }
}

void StringListModel::xylitolSet(int first, const QVariantList& variantList, const QVariantList& roles) {
    const int last = first + variantList.count() - 1;
    if((first >= 0) && (first < mContainer.count()) &&
       (last >= 0) && (last < mContainer.count())) {
        for(int i = first; i <= last; ++i) {
            mContainer.replace(i, variantList.at(i - first).toString());
        }

        emit dataChanged(index(first), index(last), Xylitol::toContainer<QVector<int>>(roles));
    }
    else {
        qWarning() << "Invalid range" << first << last;
    }
}
