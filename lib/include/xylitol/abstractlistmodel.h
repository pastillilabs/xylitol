#pragma once

#include <xylitol/xylitol_global.h>

#include <QAbstractListModel>
#include <QList>
#include <QObject>
#include <QVariantList>

namespace Xylitol {

/**
 * @brief The AbstractListModel class
 */
class XYLITOL_EXPORT AbstractListModel : public QAbstractListModel {
    Q_OBJECT

public:
    explicit AbstractListModel(QObject* parent = nullptr);

    Q_INVOKABLE virtual QVariantList xylitolToVariantList(int first, int last, const QVariantList& roles) const = 0;
    Q_INVOKABLE virtual void xylitolFromVariantList(const QVariantList& variantList, const QVariantList& roles) = 0;

protected:
    Q_INVOKABLE virtual void xylitolInsert(int first, const QVariantList& variantList, const QVariantList& roles);
    Q_INVOKABLE virtual void xylitolRemove(int first, int last);
    Q_INVOKABLE virtual void xylitolMove(int first, int last, int index);
    Q_INVOKABLE virtual void xylitolSet(int first, const QVariantList& variantList, const QVariantList& roles);
};

} // namespace Xylitol
