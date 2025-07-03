#pragma once

#include <Xylitol/socket.h>
#include <Xylitol/xylitol_global.h>

#include <QObject>
#include <QVariantList>
#include <QtQml/qqmlregistration.h>

namespace Xylitol {

/**
 * @brief The Connection class
 */
class XYLITOL_SHARED_EXPORT Connection : public QObject {
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Cannot create Connection instance.")

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
