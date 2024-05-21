#pragma once

#include <xylitol/socket.h>
#include <xylitol/xylitol_global.h>

#include <QObject>
#if(QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
#include <QtQml/qqmlregistration.h>
#endif
#include <QVariantList>

namespace Xylitol {

/**
 * @brief The Connection class
 */
class XYLITOL_EXPORT Connection : public QObject {
    Q_OBJECT
#if(QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    QML_UNCREATABLE("Cannot create Connection instance.")
#endif

public:
    explicit Connection(Socket& socket, QObject* parent = nullptr);

    Socket& socket() const;

    Socket::Action action() const;
    void setAction(Socket::Action action);

    const QVariantList& path() const;
    void setPath(const QVariantList& path);

signals:
    void actionChanged(Socket::Action action);
    void pathChanged(const QVariantList& path);

private:
    Socket& mSocket;

    Socket::Action mAction = Socket::Action::ActionNone;
    QVariantList mPath = {};
};

} // namespace Xylitol
