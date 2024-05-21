project(xyitol-root LANGUAGES CXX)

add_subdirectory(lib)
add_subdirectory(tests)

add_custom_target(${PROJECT_NAME}
    SOURCES
        .gitignore
        AUTHORS
        LICENSE
        README.md
)
