#pragma once

#include "object.h"

#include <Xylitol/abstractlistmodel.h>

#include <QVector>

/**
 * @brief The AbstractListModel class
 */
class AbstractListModel : public Xylitol::AbstractListModel {
    Q_OBJECT

public:
    enum Enum {
        EnumUndefined = 0,
        EnumA,
        EnumB,
        EnumC
    };
    Q_ENUM(Enum)

    enum Role {
        RoleString = Qt::UserRole,
        RoleEnum,
        RoleObject
    };

    struct Item {
        Item();
        Item(const QString& string, Enum enumeration, Object* object);

        QString mString;
        Enum mEnum{EnumUndefined};
        Object* mObject{nullptr};

        bool operator==(const Item& other) const;
    };

public:
    explicit AbstractListModel(QObject* parent = nullptr);
    ~AbstractListModel();

    void reset(const QVector<Item>& items);
    void append(const Item& item);
    void remove(int first, int last);
    void move(int first, int last, int index);
    void set(int index, const Item& item);

    const QVector<Item>& container() const;

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
    QVector<Item> mContainer;
};
