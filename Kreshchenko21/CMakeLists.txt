cmake_minimum_required(VERSION 3.16)

project(MemoryTrainingApp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(MemoryTrainingApp
    main.cpp
    mainwindow.h
    mainwindow.cpp
    mainmenuwidget.h
    mainmenuwidget.cpp
    gamewidget.h
    gamewidget.cpp
    gamelogic.h
    gamelogic.cpp
    mainwindow.ui
)

target_link_libraries(MemoryTrainingApp PRIVATE Qt6::Widgets)
