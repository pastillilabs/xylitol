set(TARGET_NAME Xylitol)

project(${TARGET_NAME}Root LANGUAGES CXX)

add_subdirectory(lib/${TARGET_NAME})
add_subdirectory(tests)

add_custom_target(${PROJECT_NAME}
    SOURCES
        .gitignore
        AUTHORS
        LICENSE
        README.md
)
