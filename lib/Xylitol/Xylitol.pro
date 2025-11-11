TEMPLATE = lib
TARGET = $$qtLibraryTarget(Xylitol)

QT += qml
CONFIG += plugin qmltypes
DEFINES += XYLITOL_LIBRARY

QML_IMPORT_NAME = Xylitol
QML_IMPORT_MAJOR_VERSION = 1
QML_IMPORT_PATH = $$PWD

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

# Needed for qmltypes
INCLUDEPATH += $$PWD/include/Xylitol
DEPENDPATH += $$PWD/include/Xylitol

HEADERS += $$files($$PWD/include/Xylitol/*.h)
HEADERS += $$files($$PWD/src/*.h)
SOURCES += $$files($$PWD/src/*.cpp)

DISTFILES = $$PWD/qmldir

include(platform/platform.pri)
