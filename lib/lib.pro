TEMPLATE = lib
TARGET = $$qtLibraryTarget(xylitol)

CONFIG += plugin
DEFINES += XYLITOL_LIBRARY

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

HEADERS += $$files($$PWD/include/xylitol/*.h, true)
HEADERS += $$files($$PWD/src/*.h, true)
SOURCES += $$files($$PWD/src/*.cpp, true)

android {
    target.path = /libs/$${ANDROID_TARGET_ARCH}
    INSTALLS += target
}

sailfish {
    target.path = /usr/share/$${HARBOUR_NAME}/lib
    INSTALLS += target
}
