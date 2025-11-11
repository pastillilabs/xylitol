TEMPLATE = lib
TARGET = $$qtLibraryTarget(Xylitol)

CONFIG += plugin qmltypes
DEFINES += XYLITOL_LIBRARY

QML_IMPORT_NAME = Xylitol
QML_IMPORT_MAJOR_VERSION = 1

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

# Needed for qmltypes
INCLUDEPATH += $$PWD/include/Xylitol
DEPENDPATH += $$PWD/include/Xylitol

HEADERS += $$files($$PWD/include/Xylitol/*.h, true)
HEADERS += $$files($$PWD/src/*.h, true)
SOURCES += $$files($$PWD/src/*.cpp, true)

DISTFILES = qmldir

include(platform/platform.pri)
