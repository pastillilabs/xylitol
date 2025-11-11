DESTDIR = $$OUT_PWD/../lib/Xylitol

LIBS += -L$$OUT_PWD/../lib/Xylitol -lXylitol
QMAKE_LFLAGS += -Wl,-rpath,../../../../..:$$OUT_PWD/../lib/Xylitol
