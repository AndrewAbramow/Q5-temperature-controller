cmake_minimum_required(VERSION 3.5)

project(BMP085CMake LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Core Gui Widgets Charts Sql SerialPort Concurrent Network REQUIRED)


if(ANDROID)
  add_library(BMP085CMake SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
  )
else()
  add_executable(BMP085CMake
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    database.cpp
    database.h
    database.ui
    graph.cpp
    graph.h
    graph.ui
    fortuneserver.cpp
    fortuneserver.h
    fortunethread.cpp
    fortunethread.h
    dialog.cpp
    dialog.h
  )
endif()

target_link_libraries(BMP085CMake PRIVATE
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
    Qt5::Charts
    Qt5::Sql
    Qt5::Concurrent
    Qt5::Network
    Qt5::SerialPort)
