cmake_minimum_required(VERSION 3.27)

project(xylitol-test LANGUAGES CXX)

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
        xylitol
)

add_test(
    NAME
        ${PROJECT_NAME}
    COMMAND
        ${PROJECT_NAME}
)
