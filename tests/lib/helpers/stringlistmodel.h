#pragma once

#include <xylitol/abstractlistmodel.h>

/**
 * @brief The StringListModel class
 */
class StringListModel : public Xylitol::AbstractListModel {
    Q_OBJECT

public:
    explicit StringListModel(QObject* parent = nullptr);

    void reset(const QStringList& stringList);
    void append(const QString& string);
    void remove(int first, int last);
    void move(int first, int last, int index);
    void set(int index, const QString& string);

    const QStringList& container() const;

public: // From Xylitol::AbstractListModel
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    QVariantList xylitolToVariantList(int first, int last, const QVariantList& roles) const override;
    void xylitolFromVariantList(const QVariantList& variantList, const QVariantList& roles) override;

protected: // From Xylitol::AbstractListModel
    void xylitolInsert(int first, const QVariantList& variantList, const QVariantList& roles) override;
    void xylitolRemove(int first, int last) override;
    void xylitolMove(int first, int last, int index) override;
    void xylitolSet(int first, const QVariantList& variantList, const QVariantList& roles) override;

private:
    QStringList mContainer;
};
