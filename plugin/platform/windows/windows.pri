CONFIG(debug, debug|release) {
    DESTDIR = $$OUT_PWD/../lib/Xylitol/debug

    LIBS += -L$$OUT_PWD/../lib/Xylitol/debug -lXylitold
}
CONFIG(release, debug|release) {
    DESTDIR = $$OUT_PWD/../lib/Xylitol/release

    LIBS += -L$$OUT_PWD/../lib/Xylitol/release -lXylitol
}
