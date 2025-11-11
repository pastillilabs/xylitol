TEMPLATE = subdirs

CONFIG += xylitol_tests

SUBDIRS = lib/Xylitol
SUBDIRS += plugin

plugin.depends = lib/Xylitol

xylitol_tests {
    SUBDIRS += \
        tests \

    tests.depends = lib/Xylitol
}

OTHER_FILES += \
    .gitignore \
    CMakeLists.txt \
    AUTHORS \
    LICENSE \
    README.md \
