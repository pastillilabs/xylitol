#include "plugin.h"

#include <Xylitol/abstractlistmodel.h>
#include <Xylitol/connection.h>
#include <Xylitol/node.h>
#include <Xylitol/socket.h>

#include <qqml.h>

void Plugin::registerTypes([[maybe_unused]] const char* uri) {
    // @uri Xylitol
#if QT_VERSION >= QT_VERSION_CHECK(5, 9, 0)
    qmlRegisterModule(uri, 1, 0);
#endif
    qmlRegisterType<Xylitol::Node>(uri, 1, 0, "Node");
    qmlRegisterType<Xylitol::Socket>(uri, 1, 0, "Socket");
    qmlRegisterUncreatableType<Xylitol::AbstractListModel>(uri, 1, 0, "AbstractListModel", QLatin1String("Cannot create AbstractListModel instance."));
    qmlRegisterUncreatableType<Xylitol::Connection>(uri, 1, 0, "Connection", QLatin1String("Cannot create Connection instance."));

    qRegisterMetaType<Xylitol::AbstractListModel*>();
}
