uri = Xylitol

TEMPLATE = lib
TARGET = $$qtLibraryTarget(xylitolplugin)

QT += qml quick
CONFIG += plugin

QML_IMPORT_PATH += $$PWD

INCLUDEPATH += $$PWD/../lib/include
DEPENDPATH += $$PWD/../lib/include

HEADERS += $$files($$PWD/*.h)
SOURCES += $$files($$PWD/*.cpp)

DISTFILES = qmldir

android {
    DESTDIR = qml/$$replace(uri, \., /)

    LIBS += -L$$OUT_PWD/../lib -lxylitol_$${QT_ARCH}
}

sailfish {
    DESTDIR = qml/$$replace(uri, \., /)

    LIBS += -L$$OUT_PWD/../lib -lxylitol
    QMAKE_LFLAGS += -Wl,-rpath,../../../..:$$OUT_PWD/../lib

    qmldir.files = qmldir
    qmldir.path = /usr/share/$${HARBOUR_NAME}/$${DESTDIR}
    target.path = /usr/share/$${HARBOUR_NAME}/$${DESTDIR}
    INSTALLS += qmldir target
}

linux:!android:!sailfish {
    DESTDIR = qml/$$replace(uri, \., /)

    LIBS += -L$$OUT_PWD/../lib -lxylitol
    QMAKE_LFLAGS += -Wl,-rpath,../../../..:$$OUT_PWD/../lib
}

win32 {
    CONFIG(debug, debug|release) {
        DESTDIR = debug/qml/$$replace(uri, \., /)

        LIBS += -L$$OUT_PWD/../lib/debug -lxylitold
    }
    CONFIG(release, debug|release) {
        DESTDIR = release/qml/$$replace(uri, \., /)

        LIBS += -L$$OUT_PWD/../lib/release -lxylitol
    }
}
