cmake_minimum_required(VERSION 3.5)

project(simple-countdown-app LANGUAGES CXX)

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

find_package(Qt5 COMPONENTS Widgets Multimedia REQUIRED)

if(ANDROID)
  add_library(simple-countdown-app SHARED
    countdown_label.cpp
    countdown_label.h
    countdown_label.ui
    main.cpp
    main_window.cpp
    main_window.h
    main_window.ui
  )
else()
  add_executable(simple-countdown-app MACOSX_BUNDLE
    countdown_label.cpp
    countdown_label.h
    countdown_label.ui
    main.cpp
    main_window.cpp
    main_window.h
    main_window.ui
    resources.qrc
  )
endif()

target_link_libraries(simple-countdown-app PRIVATE Qt5::Widgets Qt5::Multimedia)

set(CMAKE_INSTALL_RPATH "@executable_path/../Frameworks")
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set_target_properties(${PROJECT_NAME} PROPERTIES
    BUNDLE TRUE
    OUTPUT_NAME SimpleCountdown
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
)
