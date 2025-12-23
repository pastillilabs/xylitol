DISTFILES = $$PWD/qmldir

qmldir.files = $$PWD/qmldir
qmldir.path = /usr/share/$${HARBOUR_NAME}/qml/Xylitol
target.path = /usr/share/$${HARBOUR_NAME}/lib
INSTALLS += qmldir target
