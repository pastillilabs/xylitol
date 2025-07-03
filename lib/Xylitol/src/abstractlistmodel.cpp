#include "Xylitol/abstractlistmodel.h"

namespace Xylitol {

AbstractListModel::AbstractListModel(QObject* parent)
    : QAbstractListModel(parent) {}

void AbstractListModel::xylitolInsert(int /*first*/, const QVariantList& /*variantList*/, const QVariantList& /*roles*/) {}

void AbstractListModel::xylitolRemove(int /*first*/, int /*last*/) {}

void AbstractListModel::xylitolMove(int /*first*/, int /*last*/, int /*index*/) {}

void AbstractListModel::xylitolSet(int /*first*/, const QVariantList& /*variantList*/, const QVariantList& /*roles*/) {}

} // namespace Xylitol
