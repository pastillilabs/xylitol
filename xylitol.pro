TEMPLATE = subdirs

CONFIG += xylitol_tests

SUBDIRS = lib

lessThan(QT_MAJOR_VERSION, 6) {
    SUBDIRS += plugin

    plugin.depends = lib
}

xylitol_tests {
    SUBDIRS += \
        tests \

    tests.depends = lib
}

OTHER_FILES += \
    .gitignore \
    AUTHORS \
    LICENSE \
    README.md \
