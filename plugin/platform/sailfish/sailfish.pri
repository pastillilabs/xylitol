DESTDIR = qml/Xylitol

LIBS += -L$$OUT_PWD/../lib/Xylitol -lXylitol
QMAKE_LFLAGS += -Wl,-rpath,../../../../..:$$OUT_PWD/../lib

target.path = /usr/share/$${HARBOUR_NAME}/$${DESTDIR}
INSTALLS += target
