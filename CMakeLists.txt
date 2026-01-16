cmake_minimum_required(VERSION 3.16)

project(Classroom VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 【关键修改】在 find_package 中添加 Network
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network LinguistTools Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network LinguistTools Sql)

# 【关键修改】将所有源文件都列在这里
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        idatabase.cpp
        idatabase.h
        networkmanager.cpp
        networkmanager.h
        worker.cpp
        worker.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Classroom
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Classroom SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Classroom
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# 【关键修改】在链接库中添加 Network
target_link_libraries(Classroom PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Sql
)

set_target_properties(Classroom PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Classroom)
endif()
