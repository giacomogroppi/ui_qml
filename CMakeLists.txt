cmake_minimum_required(VERSION 3.14)

set(A_NAME_TARGET testing_qml)
set(A_DIR_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(A_DIR_MODULES_BINARY_LIBRARIES "${CMAKE_CURRENT_BINARY_DIR}/${A_NAME_TARGET}_libraries")

project(${A_NAME_TARGET} LANGUAGES CXX)

option(A_OPTION_USING_PCH "${A_NAME_TARGET} using PCH support" ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "$ENV{HOME}/Qt/6.4.2/macos/lib/cmake")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(A_QT_MODULES)
set(A_QT_MODULE_TARGETS)

set(A_TARGET_MODULES_PUBLIC)
set(A_TARGET_MODULES_PRIVATE)
set(A_TARGET_COMPILE_DEFINITIONS_PUBLIC)
set(A_TARGET_COMPILE_DEFINITIONS_PRIVATE)
set(A_TARGET_INCLUDE_DIRECTORIES_PUBLIC)
set(A_TARGET_INCLUDE_DIRECTORIES_PRIVATE)

set(A_SOURCES_RESOURCES)
set(A_SOURCES_CPP_HEADERS)
set(A_SOURCES_CPP)
set(A_SOURCES_C_HEADERS)
set(A_SOURCES_C)
set(A_SOURCES_PRECOMPILED_HEADERS_PUBLIC)
set(A_SOURCES_PRECOMPILED_HEADERS_PRIVATE)

if(IOS)
    message("Enable build for ios")
    enable_language(OBJCXX OBJC Swift)

    set(A_SOURCES_SWIFT_OBJC_INTERFACE_HEADER_NAME "aswiftobjcinterface.h")
    set(A_SOURCES_SWIFT_OBJC_INTERFACE_HEADER_NAME)
    
    #set(A_SOURCES_SWIFT_OBJC_BRIDGING_HEADER "${A_DIR_ROOT}/aswiftobjcbridging.h")
    set(A_SOURCES_SWIFT_OBJC_BRIDGING_HEADER)

    set(A_SOURCES_OBJECTIVE_HEADERS src/ios/common.h)
    set(A_SOURCES_OBJECTIVE_CPP src/ios/common.mm)
    set(A_SOURCES_SWIFT)
endif()

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package(...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

set(A_QT_MODULES
	${A_QT_MODULES}
	Core
        Gui
	Quick
        Multimedia
        Widgets
        #PrintSupport
)

set(A_TARGET_MODULES_PUBLIC
	${A_TARGET_MODULES}
#	ALogger
#	ABackend
#	AConfig
)

set(A_QT_TARGET_MODULES
	Qt${QT_VERSION_MAJOR}::Core
	Qt${QT_VERSION_MAJOR}::Quick
        Qt${QT_VERSION_MAJOR}::Multimedia
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
)

include_directories(${A_DIR_ROOT}/src/)
include_directories($ENV{HOME}/writernote-qt/src)

set(A_SOURCES_RESOURCES
	${A_SOURCES_RESOURCES}
	${A_DIR_ROOT}/resource.qrc
)

file(GLOB_RECURSE PROJECT_SOURCES_WRITERNOTE
    $ENV{HOME}/writernote-qt/src/*.cpp
    $ENV{HOME}/writernote-qt/src/*.h
)



set(A_SOURCES_CPP
    ${A_SOURCES_CPP}
    ${A_DIR_ROOT}/src/main.cpp
    ${A_DIR_ROOT}/src/controller/controller.cpp
    ${A_DIR_ROOT}/src/controller/ControllerAudio/ControllerAudio.cpp
    ${A_DIR_ROOT}/src/controller/ControllerCanvas/ControllerCanvas.cpp
    ${A_DIR_ROOT}/src/controller/ControllerCanvas/WQMLCanvasComponent.cpp
    ${A_DIR_ROOT}/src/controller/ControllerList/ControllerList.cpp
    ${A_DIR_ROOT}/src/controller/ControllerList/WQMLItemListComponent.cpp
    ${A_DIR_ROOT}/src/controller/ControllerListFiles/ControllerListFiles.cpp
    ${A_DIR_ROOT}/src/controller/ControllerListFiles/ControllerListFilesFolder.cpp
    ${A_DIR_ROOT}/src/controller/ControllerPageCounter/ControllerPageCounter.cpp
    ${A_DIR_ROOT}/src/controller/ControllerToolBar/ControllerToolBar.cpp
    ${A_DIR_ROOT}/src/controller/ControllerListFiles/Files.cpp
    ${A_DIR_ROOT}/src/controller/ControllerListFiles/Folder.cpp
    ${A_DIR_ROOT}/src/controller/ControllerColor/ControllerColor.cpp
    ${A_DIR_ROOT}/src/controller/ControllerListFiles/ControllerCommonFiles.mm
    ${PROJECT_SOURCES_WRITERNOTE}
)



message(${A_SOURCES_CPP})

set(A_SOURCES_PRECOMPILED_HEADERS_PRIVATE
	${A_SOURCES_PRECOMPILED_HEADERS_PRIVATE}
	#${A_DIR_ROOT}/amainpch.h
    # header privati
)

foreach(I_MODULE IN LISTS A_QT_MODULES)
	set(A_QT_MODULE_TARGETS
		${A_QT_MODULE_TARGETS}
		Qt${QT_VERSION_MAJOR}::${I_MODULE}
	)
endforeach()

find_package(QT NAMES Qt6 Qt5 COMPONENTS ${A_QT_MODULES} REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS ${A_QT_MODULES} REQUIRED)

set(A_SOURCES
	${A_SOURCES}
	${A_CMAKE_APPLICATION_CONF}
	${A_CMAKE_ENVIRONMENT_CONF}
	${A_SOURCES_RESOURCES}
	${A_SOURCES_CPP_HEADERS}
	${A_SOURCES_CPP}
	${A_SOURCES_C_HEADERS}
	${A_SOURCES_C}
	${A_SOURCES_PRECOMPILED_HEADERS_PUBLIC}
	${A_SOURCES_PRECOMPILED_HEADERS_PRIVATE}
)

if(IOS)
	set(A_SOURCES
		${A_SOURCES}
		${A_SOURCES_SWIFT_OBJC_BRIDGING_HEADER}
		${A_SOURCES_OBJECTIVE_HEADERS}
		${A_SOURCES_OBJECTIVE_CPP}
		${A_SOURCES_SWIFT}
	)
endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
	qt_add_executable(${A_NAME_TARGET}
		${A_SOURCES}
	)
else()
	if(ANDROID)
		add_library(${A_NAME_TARGET}
			SHARED
				${A_SOURCES}
		)
	else()
		add_executable(${A_NAME_TARGET}
			${A_SOURCES}
		)
	endif()
endif()

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.16 AND A_OPTION_USING_PCH)
	message(STATUS "Using PCH for ${A_NAME_TARGET}")
	target_precompile_headers(${A_NAME_TARGET}
		PRIVATE ${A_SOURCES_PRECOMPILED_HEADERS_PRIVATE}
		PUBLIC ${A_SOURCES_PRECOMPILED_HEADERS_PUBLIC}
	)
	set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)
else()
	message(STATUS "No PCH for ${A_NAME_TARGET}")
endif()

SET(QT_USE_QTMULTIMEDIA TRUE)

if(MACOS_BUILD OR APPLE)
    include_directories(/opt/homebrew/Cellar/libzip/1.9.2/include/)
    target_link_libraries(${PROJECT_NAME} PRIVATE /opt/homebrew/Cellar/libzip/1.9.2/lib/libzip.dylib)
elseif(WIN)
    include_directories(${PROJECT_SOURCE_DIR}/3rdparty/libzip/install/include/)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/3rdparty/libzip/install/lib/libzip.a)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/3rdparty/zlib-ng/install/lib/libzlib.a)
endif()

set(A_TARGET_COMPILE_DEFINITIONS_PRIVATE
	${A_TARGET_COMPILE_DEFINITIONS_PRIVATE}
	$<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)

target_compile_definitions(${A_NAME_TARGET}
	PRIVATE ${A_TARGET_COMPILE_DEFINITIONS_PRIVATE}
	PUBLIC ${A_TARGET_COMPILE_DEFINITIONS_PUBLIC}
)

target_include_directories(${A_NAME_TARGET}
	PRIVATE ${A_TARGET_INCLUDE_DIRECTORIES_PRIVATE}
	PUBLIC ${A_TARGET_INCLUDE_DIRECTORIES_PUBLIC}
)

target_link_libraries(${A_NAME_TARGET}
	PRIVATE
		${A_QT_TARGET_MODULES}
		${A_TARGET_MODULES_PRIVATE}
	PUBLIC
		${A_TARGET_MODULES_PUBLIC}
)

if(IOS)
	set_target_properties(${A_NAME_TARGET}
		PROPERTIES
			XCODE_ATTRIBUTE_SWIFT_OBJC_INTERFACE_HEADER_NAME "${A_SOURCES_SWIFT_OBJC_INTERFACE_HEADER_NAME}"
			XCODE_ATTRIBUTE_SWIFT_OBJC_BRIDGING_HEADER "${A_SOURCES_SWIFT_OBJC_BRIDGING_HEADER}"
			XCODE_ATTRIBUTE_ENABLE_BITCODE "NO"
			XCODE_ATTRIBUTE_ALWAYS_EMBED_SWIFT_STANDARD_LIBRARIES "YES"
			XCODE_ATTRIBUTE_SWIFT_VERSION "5.0"
	)
endif()
