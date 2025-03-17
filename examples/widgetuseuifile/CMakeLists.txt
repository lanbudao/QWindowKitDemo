cmake_minimum_required(VERSION 3.19)

project(WidgetUseUiFile VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(GLOB SOURCE *.h *.cpp *.ui)

set(RESOURCE ${CMAKE_SOURCE_DIR}/frameless/resource/frameless.qrc)

add_executable(${PROJECT_NAME})

qm_configure_target(${PROJECT_NAME}
        FEATURES cxx_std_17
        SOURCES ${SOURCE} ${RESOURCE}
        QT_LINKS Core Gui Widgets
        LINKS frameless
        INCLUDE_PRIVATE .
)
