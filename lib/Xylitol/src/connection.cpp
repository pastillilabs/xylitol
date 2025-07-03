#include "Xylitol/connection.h"

namespace Xylitol {

Connection::Connection(Socket& socket, QObject* parent)
    : QObject(parent)
    , mSocket(socket) {}

Socket& Connection::socket() const {
    return mSocket;
}

Socket::Action Connection::action() const {
    return mAction;
}

void Connection::setAction(Socket::Action action) {
    if(action != mAction) {
        mAction = action;
        emit actionChanged(action);
    }
}

const QVariantList& Connection::path() const {
    return mPath;
}

void Connection::setPath(const QVariantList& path) {
    if(path != mPath) {
        mPath = path;
        emit pathChanged(path);
    }
}

} // namespace Xylitol
