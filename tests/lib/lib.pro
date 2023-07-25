TARGET = xylitoltests

QT += testlib

TEMPLATE = app

INCLUDEPATH += \
    $$PWD/../../lib/include

HEADERS += $$files($$PWD/*.h, true)
SOURCES += $$files($$PWD/*.cpp, true)

android {
    LIBS += -L$$OUT_PWD/../../lib -lxylitol_$${QT_ARCH}
}

unix:!android: {
    LIBS += -L$$OUT_PWD/../../lib -lxylitol
    QMAKE_LFLAGS += -Wl,-rpath,$$OUT_PWD/../../lib
}

win32 {
    CONFIG(debug, debug|release) {
        LIBS += -L$$OUT_PWD/../../lib/debug -lxylitold
        PRE_TARGETDEPS += $$OUT_PWD/../../lib/debug/xylitold.lib
    }
    CONFIG(release, debug|release) {
        LIBS += -L$$OUT_PWD/../../lib/release -lxylitol
        PRE_TARGETDEPS += $$OUT_PWD/../../lib/release/xylitol.lib
    }
}
