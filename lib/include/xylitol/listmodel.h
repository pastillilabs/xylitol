#pragma once

#include <xylitol/abstractlistmodel.h>
#include <xylitol/xylitol_global.h>

#include <QHash>
#include <QList>
#include <QModelIndex>
#include <QObject>
#include <QVariant>
#include <QVariantList>
#include <QVector>

namespace Xylitol {

/**
 * @brief The ListModel class
 */
class XYLITOL_EXPORT ListModel : public AbstractListModel {
    Q_OBJECT

public:
    typedef QHash<int,QVariant> Item;
    typedef QVector<Item> Container;

public:
    explicit ListModel(QObject* parent = nullptr);

    virtual QHash<int, int> roleTypes() const;
    virtual QVariant xylitolCreateRole(int index, int role, const QVariant& variant);

    const Container& container() const;

public: // From AbstractListModel
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    QVariantList xylitolToVariantList(int first, int last, const QVariantList& roles) const override;
    void xylitolFromVariantList(const QVariantList& variantList, const QVariantList& roles) override;

protected: // From AbstractListModel
    void xylitolInsert(int first, const QVariantList& variantList, const QVariantList& roles) override;
    void xylitolRemove(int first, int last) override;
    void xylitolMove(int first, int last, int index) override;
    void xylitolSet(int first, const QVariantList& variantList, const QVariantList& roles) override;

protected:
    Container mContainer;
};

} // namespace Xylitol
