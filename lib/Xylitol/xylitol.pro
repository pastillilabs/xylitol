TEMPLATE = lib
TARGET = $$qtLibraryTarget(Xylitol)

CONFIG += plugin
greaterThan(QT_MAJOR_VERSION, 5) {
    CONFIG += qmltypes
}
DEFINES += XYLITOL_LIBRARY

greaterThan(QT_MAJOR_VERSION, 5) {
    QML_IMPORT_NAME = Xylitol
    QML_IMPORT_MAJOR_VERSION = 1
}

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

greaterThan(QT_MAJOR_VERSION, 5) {
    # Needed for moc
    INCLUDEPATH += $$PWD/include/Xylitol
    DEPENDPATH += $$PWD/include/Xylitol
}

HEADERS += $$files($$PWD/include/Xylitol/*.h, true)
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
