DESTDIR = qml/$$replace(uri, \., /)

LIBS += -L$$OUT_PWD/../lib/Xylitol -lXylitol_$${QT_ARCH}
