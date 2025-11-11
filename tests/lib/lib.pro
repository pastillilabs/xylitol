TARGET = xylitoltests

QT += quick testlib

TEMPLATE = app

INCLUDEPATH += $$PWD/../../lib/Xylitol/include

HEADERS += $$files($$PWD/*.h, true)
SOURCES += $$files($$PWD/*.cpp, true)

LIBS += -L$$OUT_PWD/../../lib/Xylitol -lXylitol
QMAKE_LFLAGS += -Wl,-rpath,$$OUT_PWD/../../lib
