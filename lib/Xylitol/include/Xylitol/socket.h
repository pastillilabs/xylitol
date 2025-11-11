#pragma once

#include <Xylitol/xylitol_global.h>

#include <QObject>
#include <QVariantMap>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QtQml/qqmlregistration.h>
#else
#define QML_ELEMENT
#endif

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
