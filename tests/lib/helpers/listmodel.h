#pragma once

#include <xylitol/listmodel.h>

#include <QVector>

/**
 * @brief The ListModel class
 */
class ListModel : public Xylitol::ListModel {
    Q_OBJECT

public:
    enum Role {
        RoleInteger = Qt::UserRole,
        RoleString,
        RoleObject
    };

public:
    explicit ListModel(QObject* parent = nullptr);

    void reset(const Container& container);
    void append(const Item& item);
    void remove(int first, int last);
    void move(int first, int last, int index);
    void set(int index, const Item& item);

    void setString(int index, const QString& string);

public: // From Xylitol::ListModel
    QHash<int, QByteArray> roleNames() const override;
    QHash<int, int> roleTypes() const override;
};
