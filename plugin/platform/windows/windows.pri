CONFIG(debug, debug|release) {
    DESTDIR = debug/qml/$$replace(uri, \., /)

    LIBS += -L$$OUT_PWD/../lib/Xylitol/debug -lXylitold
}
CONFIG(release, debug|release) {
    DESTDIR = release/qml/$$replace(uri, \., /)

    LIBS += -L$$OUT_PWD/../lib/Xylitol/release -lXylitol
}
