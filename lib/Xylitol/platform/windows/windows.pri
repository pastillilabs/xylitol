CONFIG(debug, debug|release) {
    # Copy qml to output directory
    copy_qml.files =$$PWD/../../qmldir
    copy_qml.path = $$OUT_PWD/debug
}

CONFIG(release, debug|release) {
    # Copy qml to output directory
    copy_qml.files =$$PWD/../../qmldir
    copy_qml.path = $$OUT_PWD/release
}

COPIES += copy_qml
