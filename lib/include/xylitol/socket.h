#pragma once

#include <xylitol/xylitol_global.h>

#include <QObject>
#include <QVariantMap>
#include <QtQml/qqmlregistration.h>

namespace Xylitol {

/**
 * @brief The Socket class
 */
class XYLITOL_SHARED_EXPORT Socket : public QObject {
    Q_OBJECT
    QML_ELEMENT

public:
    enum class Action {
        ActionNone,
        ActionInitialize,
        ActionInvoke,
        ActionUpdate
    };
    Q_ENUM(Action);

public:
    explicit Socket(QObject* parent = nullptr);

signals:
    void receive(Xylitol::Socket::Action action, const QVariantList& path, const QVariant& data);
    void send(Xylitol::Socket::Action action, const QVariantList& path, const QVariant& data);
};

} // namespace Xylitol
