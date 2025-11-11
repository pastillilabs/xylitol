TARGET = xylitoltests

QT += quick testlib

TEMPLATE = app

INCLUDEPATH += $$PWD/../../lib/Xylitol/include

HEADERS += $$files($$PWD/*.h, true)
SOURCES += $$files($$PWD/*.cpp, true)

include(platform/platform.pri)
