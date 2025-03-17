project(frameless)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

file(GLOB_RECURSE SOURCE *.h *.cpp)

find_package(QWindowKit REQUIRED)
if (TARGET QWindowKit::Core)
    get_filename_component(QWindowKit_ROOT_DIR ${QWindowKit_DIR} DIRECTORY)
    get_filename_component(QWindowKit_ROOT_DIR ${QWindowKit_ROOT_DIR} DIRECTORY)
    get_filename_component(QWindowKit_ROOT_DIR ${QWindowKit_ROOT_DIR} DIRECTORY)
    message(STATUS "QWindowKit root directory: ${QWindowKit_ROOT_DIR}")
endif ()

add_library(${PROJECT_NAME} STATIC)

qm_configure_target(${PROJECT_NAME}
        FEATURES cxx_std_17
        SOURCES ${SOURCE}
        QT_LINKS Core Gui Widgets
        LINKS QWindowKit::Core QWindowKit::Widgets
)

target_include_directories(${PROJECT_NAME} PUBLIC . ..)
target_include_directories(${PROJECT_NAME} PRIVATE
        ${QWindowKit_ROOT_DIR}/include/QWindowKit
)