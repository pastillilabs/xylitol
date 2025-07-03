cmake_minimum_required(VERSION 3.27)

set(MODULE_NAME Test)

project(${TARGET_NAME}${MODULE_NAME} VERSION 0.1 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Gui Test)

qt_standard_project_setup(
    REQUIRES 6.8
)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.cpp *.h)
qt_add_executable(${PROJECT_NAME}
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Test
        Xylitol
)

add_test(
    NAME
        ${PROJECT_NAME}
    COMMAND
        ${PROJECT_NAME}
)
