#include "xylitolplugin.h"

#include <xylitol/abstractlistmodel.h>
#include <xylitol/connection.h>
#include <xylitol/node.h>
#include <xylitol/socket.h>

#include <QDebug>
#include <qqml.h>

void XylitolPlugin::registerTypes([[maybe_unused]] const char* uri) {
#if(QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    qRegisterMetaType<Xylitol::AbstractListModel*>();

    // @uri Xylitol
#if QT_VERSION >= QT_VERSION_CHECK(5, 9, 0)
    qmlRegisterModule(uri, 1, 0);
#endif
    qmlRegisterType<Xylitol::Node>(uri, 1, 0, "Node");
    qmlRegisterType<Xylitol::Socket>(uri, 1, 0, "Socket");
    qmlRegisterUncreatableType<Xylitol::AbstractListModel>(uri, 1, 0, "AbstractListModel", QLatin1String("Cannot create AbstractListModel instance."));
    qmlRegisterUncreatableType<Xylitol::Connection>(uri, 1, 0, "Connection", QLatin1String("Cannot create Connection instance."));
#endif
}
