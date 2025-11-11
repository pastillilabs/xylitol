DESTDIR = qml/Xylitol

LIBS += -L$$OUT_PWD/../lib/Xylitol -lXylitol
QMAKE_LFLAGS += -Wl,-rpath,../../../../..:$$OUT_PWD/../lib

qmldir.files = $$PWD/../lib/Xylitol/qmldir
qmldir.path = /usr/share/$${HARBOUR_NAME}/$${DESTDIR}
target.path = /usr/share/$${HARBOUR_NAME}/$${DESTDIR}
INSTALLS += qmldir target
