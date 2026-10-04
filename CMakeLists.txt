cmake_minimum_required(VERSION 3.16)

project(AteneaEnElDorado LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(include)

add_executable(AteneaEnElDorado
    src/main.cpp
)

target_link_libraries(AteneaEnElDorado PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
