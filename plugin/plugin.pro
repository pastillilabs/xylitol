uri = Xylitol

TEMPLATE = lib

TARGET = $$qtLibraryTarget(XylitolPlugin)

QT += qml quick
CONFIG += plugin

QML_IMPORT_PATH += $$OUT_PWD/qml

INCLUDEPATH += $$PWD/../lib/Xylitol/include
DEPENDPATH += $$PWD/../lib/Xylitol/include

HEADERS += $$files($$PWD/src/*.h)
SOURCES += $$files($$PWD/src/*.cpp)

include(platform/platform.pri)

# Copy qml to output directory
copy_qml.files =  $$PWD/../lib/Xylitol/qmldir
copy_qml.path = $$DESTDIR
COPIES += copy_qml
