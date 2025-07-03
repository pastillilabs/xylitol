TEMPLATE = subdirs

CONFIG += xylitol_tests

SUBDIRS = lib/Xylitol

lessThan(QT_MAJOR_VERSION, 6) {
    SUBDIRS += plugin

    plugin.depends = lib/Xylitol
}

xylitol_tests {
    SUBDIRS += \
        tests \

    tests.depends = lib/Xylitol
}

OTHER_FILES += \
    .gitignore \
    AUTHORS \
    LICENSE \
    README.md \
