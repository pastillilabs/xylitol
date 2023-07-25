TEMPLATE = subdirs

CONFIG += xylitol_tests

SUBDIRS = \
    lib \
    plugin \

plugin.depends = lib

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
