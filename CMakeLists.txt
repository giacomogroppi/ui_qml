cmake_minimum_required(VERSION 3.16)

project(testing_qml VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.3 COMPONENTS Quick REQUIRED)

qt_add_executable(apptesting_qml
    main.cpp
    textballoon.h textballoon.cpp
    resource.qrc
)

qt_add_qml_module(apptesting_qml
    URI testing_qml
    VERSION 1.0
    QML_FILES main.qml 
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
