#pragma once

#include <QJsonObject>
#include <QObject>
#include <QString>

/**
 * @brief The Gadget class
 */
class Gadget  {
    Q_GADGET
    Q_PROPERTY(int a MEMBER mA)
    Q_PROPERTY(QString b MEMBER mB)
    Q_PROPERTY(quint64 c MEMBER mC)
    Q_PROPERTY(QJsonObject d MEMBER mD)

public:
    Q_INVOKABLE Gadget() = default;
    Gadget(int a, const QString& b, qint64 c, const QJsonObject& d);

    bool operator==(const Gadget& other) const;
    bool operator!=(const Gadget& other) const;
    bool operator<(const Gadget& other) const;

private:
    int mA{0};
    QString mB;
    quint64 mC{0};
    QJsonObject mD;
};
