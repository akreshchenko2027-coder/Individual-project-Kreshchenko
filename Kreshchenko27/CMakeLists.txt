cmake_minimum_required(VERSION 3.16)

project(MemoryTraining22 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(MemoryTraining22
    main.cpp
    mainwindow.h
    mainwindow.cpp
    gamewidget.h
    gamewidget.cpp
    gamelogic.h
    gamelogic.cpp
    mainmenuwidget.h
    mainmenuwidget.cpp
    statswidget.h
    statswidget.cpp
    gamerepository.h
    gamerepository.cpp
    style.qss
    resources.qrc
    README.md

)

target_link_libraries(MemoryTraining22 PRIVATE Qt6::Widgets)
