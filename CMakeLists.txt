cmake_minimum_required(VERSION 3.16)

project(testing_qml VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE cpp_file
    *.cpp
    *.h
)

file(GLOB_RECURSE PROJECT_MOC
    *.qrc
)

if(UNIX AND NOT APPLE AND NOT MINGW)
    set(LINUX TRUE)
endif()

if(LINUX)
    if(NOT "$ENV{QT_VER_WRITERNOTE}" STREQUAL "")
        message("-- QT_VER_WRITERNOTE set")
        set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "~/Qt/$ENV{QT_VER_WRITERNOTE}/gcc_64/lib/cmake")
    else()
        set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "~/Qt/6.4.0/gcc_64/lib/cmake")
    endif()

    message("-- search qt in " ${CMAKE_PREFIX_PATH})
endif()

find_package(Qt6 6.3 COMPONENTS Quick REQUIRED)

qt_add_executable(apptesting_qml
    ${cpp_file}
    ${PROJECT_MOC}
)

qt_add_qml_module(apptesting_qml
    URI testing_qml
    VERSION 1.0
    QML_FILES
        main.qml
        ui/pageCanvas/StatusBar.qml
        ui/pageCanvas/CanvasSurface.qml
        ui/pageCanvas/ButtonToolInstruments.qml
        ui/pageCanvas/ListPreview.qml
        ui/pageCanvas/MainWindow.qml
        Prova.qml
)

set_target_properties(apptesting_qml PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(apptesting_qml
    PRIVATE Qt6::Quick)

install(TARGETS apptesting_qml
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
