#pragma once

#include <xylitol/xylitol_global.h>

#include <QObject>

#if(QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
#include <QtQml/qqmlregistration.h>
#endif
#include <QVariantMap>

namespace Xylitol {

/**
 * @brief The Socket class
 */
class XYLITOL_EXPORT Socket : public QObject {
    Q_OBJECT
#if(QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    QML_ELEMENT
#endif

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
