TEMPLATE = lib

TARGET = $$qtLibraryTarget(Xylitolplugin)

QT += qml quick
CONFIG += plugin

QML_IMPORT_PATH += $$OUT_PWD/qml

INCLUDEPATH += $$PWD/../lib/Xylitol/include

DEPENDPATH += $$PWD/../lib/Xylitol/include

HEADERS += $$files($$PWD/src/*.h)
SOURCES += $$files($$PWD/src/*.cpp)

include(platform/platform.pri)
