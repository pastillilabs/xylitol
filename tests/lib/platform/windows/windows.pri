CONFIG(debug, debug|release) {
    LIBS += -L$$OUT_PWD/../../lib/Xylitol/debug -lXylitold
}

CONFIG(release, debug|release) {
    LIBS += -L$$OUT_PWD/../../lib/Xylitol/release -lXylitol
}
