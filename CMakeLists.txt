cmake_minimum_required(VERSION 3.14)

set(A_NAME_TARGET testing_qml)
set(A_DIR_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(A_DIR_MODULES_BINARY_LIBRARIES "${CMAKE_CURRENT_BINARY_DIR}/${A_NAME_TARGET}_libraries")

project(${A_NAME_TARGET} LANGUAGES CXX)

option(A_OPTION_USING_PCH "${A_NAME_TARGET} using PCH support" ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "$ENV{HOME}/Qt/6.4.2/macos/lib/cmake")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "$ENV{HOME}/Qt/6.5.0/gcc_64/lib/cmake")

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
    enable_language(OBJCXX OBJC)

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

add_definitions(-DVERSION_STRING="TESTING")

set(A_QT_MODULES
	${A_QT_MODULES}
	Core
        Gui
	Quick
        Multimedia
        Test
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
        Qt${QT_VERSION_MAJOR}::Gui
		Qt${QT_VERSION_MAJOR}::Quick
        Qt${QT_VERSION_MAJOR}::Multimedia
        Qt${QT_VERSION_MAJOR}::Test
)

include_directories(${A_DIR_ROOT}/src/)
include_directories(src/model/)

set(A_SOURCES_RESOURCES
	${A_SOURCES_RESOURCES}
	${A_DIR_ROOT}/resource.qrc
)

file(GLOB_RECURSE
    PROJECT_SOURCES_WRITERNOTE

    ${A_DIR_ROOT}/src/model/*.cpp
    ${A_DIR_ROOT}/src/model/*.h
)

set(PROJECT_SOURCES_WRITERNOTE
    ${PROJECT_SOURCES_WRITERNOTE}
    ${A_DIR_ROOT}/src/model/core/WZip.cpp
    ${A_DIR_ROOT}/src/model/core/WList.cpp
    ${A_DIR_ROOT}/src/model/core/multiarray.cpp
    ${A_DIR_ROOT}/src/model/core/WFile.cpp
    ${A_DIR_ROOT}/src/model/core/core.cpp
    ${A_DIR_ROOT}/src/model/core/WImage.cpp
    ${A_DIR_ROOT}/src/model/core/WListThreadSafe.cpp
    ${A_DIR_ROOT}/src/model/core/WPixmap.cpp
    ${A_DIR_ROOT}/src/model/core/WDir.cpp
    ${A_DIR_ROOT}/src/model/core/WZipWriter.cpp
    ${A_DIR_ROOT}/src/model/core/WPair.cpp
    ${A_DIR_ROOT}/src/model/core/WSemaphore.cpp
    ${A_DIR_ROOT}/src/model/core/WZipCommon.cpp
    ${A_DIR_ROOT}/src/model/core/WZipWriterMulti.cpp
    ${A_DIR_ROOT}/src/model/core/WLine.cpp
    ${A_DIR_ROOT}/src/model/core/WMutexLocker.cpp
    ${A_DIR_ROOT}/src/model/core/WZipWriterSingle.cpp
    ${A_DIR_ROOT}/src/model/core/AtomicSafe.cpp
    ${A_DIR_ROOT}/src/model/core/WZipReaderSingle.cpp
    ${A_DIR_ROOT}/src/model/core/WMultipleMutex.cpp
    ${A_DIR_ROOT}/src/model/core/WPainter/WPainter.cpp
    ${A_DIR_ROOT}/src/model/core/WReadZip.cpp
    ${A_DIR_ROOT}/src/model/file/FileManager.cpp
    ${A_DIR_ROOT}/src/model/file/Directory.cpp
    ${A_DIR_ROOT}/src/model/file/File.cpp
    ${A_DIR_ROOT}/src/model/audioplay/audioplay.cpp
    ${A_DIR_ROOT}/src/model/touch/object_finder/ObjectFinder.cpp
    ${A_DIR_ROOT}/src/model/touch/object_finder/model_finder/model_finder.cpp
    ${A_DIR_ROOT}/src/model/touch/tools/InsertTools.cpp
    ${A_DIR_ROOT}/src/model/touch/tools/Scrollable.cpp
    ${A_DIR_ROOT}/src/model/touch/tools/Tools.cpp
    ${A_DIR_ROOT}/src/model/touch/TabletUtils.cpp
    ${A_DIR_ROOT}/src/model/touch/TabletPenMethod.cpp
    ${A_DIR_ROOT}/src/model/touch/dataTouch/page/Page.cpp
    ${A_DIR_ROOT}/src/model/touch/dataTouch/page/PageFile.cpp
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/StrokeNormalFile.cpp
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/stroke_file.cpp
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/StrokeProp.cpp
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/StrokeLineGenerator.cpp
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/StrokePre.cpp
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/StrokeRectGenerator.cpp
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/StrokeForPage.cpp
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/StrokeCircle.cpp
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/stroke_complex_data.cpp
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/StrokeLine.cpp
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/StrokeCircleGenerator.cpp
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/StrokeNormal.cpp
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/Stroke.cpp
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/StrokeRect.cpp
    ${A_DIR_ROOT}/src/model/touch/dataTouch/datastruct/DataStruct.cpp
    ${A_DIR_ROOT}/src/model/touch/dataTouch/datastruct/utils_datastruct.cpp
    ${A_DIR_ROOT}/src/model/touch/dataTouch/datastruct/controllForRepositioning.cpp
    ${A_DIR_ROOT}/src/model/touch/dataTouch/datastruct/removePage.cpp
    ${A_DIR_ROOT}/src/model/touch/dataTouch/datastruct/changeId.cpp
    ${A_DIR_ROOT}/src/model/touch/dataTouch/datastruct/triggerNewView.cpp
    ${A_DIR_ROOT}/src/model/touch/square/Square.cpp
    ${A_DIR_ROOT}/src/model/touch/square/SquareMethod.cpp
    ${A_DIR_ROOT}/src/model/touch/rubber/RubberMethod.cpp
    ${A_DIR_ROOT}/src/model/touch/rubber/Rubber.cpp
    ${A_DIR_ROOT}/src/model/touch/TabletController.cpp
    ${A_DIR_ROOT}/src/model/touch/pen/PenMethod.cpp
    ${A_DIR_ROOT}/src/model/touch/pen/Pen.cpp
    ${A_DIR_ROOT}/src/model/touch/laser/Laser.cpp
    ${A_DIR_ROOT}/src/model/touch/laser/LaserMethod.cpp
    ${A_DIR_ROOT}/src/model/touch/multi_thread_data.cpp
    ${A_DIR_ROOT}/src/model/touch/highlighter/HighligterMethod.cpp
    ${A_DIR_ROOT}/src/model/touch/highlighter/Highligter.cpp
    ${A_DIR_ROOT}/src/model/touch/copy_cut/copy_cut_selection.cpp
    ${A_DIR_ROOT}/src/model/images/fromimage.cpp
    ${A_DIR_ROOT}/src/model/pdf/topdf.cpp
    ${A_DIR_ROOT}/src/model/pdf/translate.cpp
    ${A_DIR_ROOT}/src/model/Scheduler/WPool.cpp
    ${A_DIR_ROOT}/src/model/Scheduler/WTask.cpp
    ${A_DIR_ROOT}/src/model/Scheduler/Scheduler.cpp
    ${A_DIR_ROOT}/src/model/lastedit/redoundo.cpp
    ${A_DIR_ROOT}/src/model/utils/get_file_dir/get_file_dir.cpp
    ${A_DIR_ROOT}/src/model/utils/color/color_chooser.cpp
    ${A_DIR_ROOT}/src/model/utils/path/pathfile.cpp
    ${A_DIR_ROOT}/src/model/utils/path/get_path.cpp
    ${A_DIR_ROOT}/src/model/utils/remove_key/remove_key.cpp
    ${A_DIR_ROOT}/src/model/utils/Optional.cpp
    ${A_DIR_ROOT}/src/model/utils/threadcount.cpp
    ${A_DIR_ROOT}/src/model/utils/time/current_time.cpp
    ${A_DIR_ROOT}/src/model/utils/lastModification/lastmodification.cpp
    ${A_DIR_ROOT}/src/model/utils/removenotwriternote.cpp
    ${A_DIR_ROOT}/src/model/utils/mostra_explorer/mostra_explorer.cpp
    ${A_DIR_ROOT}/src/model/utils/checkpassword/checkpassword.cpp
    ${A_DIR_ROOT}/src/model/utils/copy_text.cpp
    ${A_DIR_ROOT}/src/model/utils/random/random.cpp
    ${A_DIR_ROOT}/src/model/utils/permission/permission.cpp
    ${A_DIR_ROOT}/src/model/utils/get_only_name/get_only_name.cpp
    ${A_DIR_ROOT}/src/model/datawrite/write/saveArray.cpp
    ${A_DIR_ROOT}/src/model/datawrite/write/savefile_savefile.cpp
    ${A_DIR_ROOT}/src/model/datawrite/write/salvabinario.cpp
    ${A_DIR_ROOT}/src/model/currenttitle/checksimilecopybook.cpp
    ${A_DIR_ROOT}/src/model/currenttitle/document.cpp
    ${A_DIR_ROOT}/src/model/currenttitle/merge_currenttitle/merge_currenttitle.cpp
    ${A_DIR_ROOT}/src/model/testing/testingcore.cpp
    ${A_DIR_ROOT}/src/model/testing/TestingComponent.cpp
    ${A_DIR_ROOT}/src/model/testing/testingzip.cpp
    ${A_DIR_ROOT}/src/model/testing/memtest.cpp
    ${A_DIR_ROOT}/src/model/audiorecord/audiorecord.cpp
    ${A_DIR_ROOT}/src/model/dataread/loadbinario.cpp
    ${A_DIR_ROOT}/src/model/dataread/readlistarray.cpp
    ${A_DIR_ROOT}/src/model/dataread/xmlstruct.cpp
    ${A_DIR_ROOT}/src/model/dataread/loadfile.cpp
    ${A_DIR_ROOT}/src/model/dataread/old_version/ver_7/load_file_ver_7.cpp
    ${A_DIR_ROOT}/src/model/dataread/old_version/ver_8/load_file_ver_8.cpp
    ${A_DIR_ROOT}/src/model/dataread/old_version/ver_6/load_file_ver_6.cpp
    ${A_DIR_ROOT}/src/model/dataread/old_version/ver_3/load_file_ver_3.cpp
    ${A_DIR_ROOT}/src/model/dataread/old_version/ver_4/load_file_ver_4.cpp
    ${A_DIR_ROOT}/src/model/dataread/old_version/ver_5/load_file_ver_5.cpp
    ${A_DIR_ROOT}/src/model/dataread/old_version/ver_2/load_file_ver_2.cpp
    ${A_DIR_ROOT}/src/model/dataread/old_loadbinario/old_version_load_binario.cpp
    ${A_DIR_ROOT}/src/model/cloud/utils/downloadfile.cpp
    ${A_DIR_ROOT}/src/model/cloud/utils/toencrypt.cpp
    ${A_DIR_ROOT}/src/model/cloud/struct_file.cpp
    ${A_DIR_ROOT}/src/model/cloud/on_select.cpp
    ${A_DIR_ROOT}/src/model/cloud/cloud_controll.cpp
    ${A_DIR_ROOT}/src/model/cloud/cloud_ui.cpp
    ${A_DIR_ROOT}/src/model/cloud/struct_user.cpp
    ${A_DIR_ROOT}/src/model/log/log_ui/log_ui.cpp
    ${A_DIR_ROOT}/src/model/preview/preview.cpp
    ${A_DIR_ROOT}/src/model/restore_file/restore_file_critic.cpp
    ${A_DIR_ROOT}/src/model/frompdf/convertimg.cpp
    ${A_DIR_ROOT}/src/model/frompdf/metadata.cpp
    ${A_DIR_ROOT}/src/model/frompdf/frompdf.cpp
    ${A_DIR_ROOT}/src/model/windows/mostra_finestra_i.cpp
    ${A_DIR_ROOT}/src/model/windows/updatecheck.cpp
    ${A_DIR_ROOT}/src/model/sheet/style_struct.cpp

    ${A_DIR_ROOT}/src/model/core/AtomicSafe.h
    ${A_DIR_ROOT}/src/model/core/WListThreadSafe.h
    ${A_DIR_ROOT}/src/model/core/WZipWriterSingle.h
    ${A_DIR_ROOT}/src/model/core/core.h
    ${A_DIR_ROOT}/src/model/core/WImage.h
    ${A_DIR_ROOT}/src/model/core/WMutexLocker.h
    ${A_DIR_ROOT}/src/model/core/WPixmap.h
    ${A_DIR_ROOT}/src/model/core/WMutex.h
    ${A_DIR_ROOT}/src/model/core/WFile.h
    ${A_DIR_ROOT}/src/model/core/WSemaphore.h
    ${A_DIR_ROOT}/src/model/core/multiarray.h
    ${A_DIR_ROOT}/src/model/core/WZipReaderSingle.h
    ${A_DIR_ROOT}/src/model/core/WList.h
    ${A_DIR_ROOT}/src/model/core/WZip.h
    ${A_DIR_ROOT}/src/model/core/WPair.h
    ${A_DIR_ROOT}/src/model/core/WReadZip.h
    ${A_DIR_ROOT}/src/model/core/WMultipleMutex.h
    ${A_DIR_ROOT}/src/model/core/WLine.h
    ${A_DIR_ROOT}/src/model/core/WZipWriter.h
    ${A_DIR_ROOT}/src/model/core/WDir.h
    ${A_DIR_ROOT}/src/model/core/WZipWriterMulti.h
    ${A_DIR_ROOT}/src/model/core/WPainter/WPainter.h
    ${A_DIR_ROOT}/src/model/core/WZipCommon.h
    ${A_DIR_ROOT}/src/model/file/FileManager.h
    ${A_DIR_ROOT}/src/model/file/File.h
    ${A_DIR_ROOT}/src/model/file/Directory.h
    ${A_DIR_ROOT}/src/model/audioplay/audioplay.h
    ${A_DIR_ROOT}/src/model/touch/object_finder/ObjectFinder.h
    ${A_DIR_ROOT}/src/model/touch/object_finder/model_finder/model_finder.h
    ${A_DIR_ROOT}/src/model/touch/tools/InsertTools.h
    ${A_DIR_ROOT}/src/model/touch/tools/Tools.h
    ${A_DIR_ROOT}/src/model/touch/tools/Scrollable.h
    ${A_DIR_ROOT}/src/model/touch/paintevent/paint.h
    ${A_DIR_ROOT}/src/model/touch/dataTouch/page/Page.h
    ${A_DIR_ROOT}/src/model/touch/dataTouch/page/PageFile.h
    ${A_DIR_ROOT}/src/model/touch/dataTouch/Point.h
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/StrokeRect.h
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/StrokeForPage.h
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/StrokeRectGenerator.h
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/StrokeLineGenerator.h
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/stroke_complex_data.h
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/StrokeLine.h
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/StrokeProp.h
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/StrokeCircle.h
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/StrokePre.h
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/Stroke.h
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/stroke_drawer.h
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/stroke_file.h
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/StrokeNormalFile.h
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/StrokeCircleGenerator.h
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/StrokeNormal.h
    ${A_DIR_ROOT}/src/model/touch/dataTouch/stroke/StrokeComplexCommon.h
    ${A_DIR_ROOT}/src/model/touch/dataTouch/datastruct/DataStruct.h
    ${A_DIR_ROOT}/src/model/touch/dataTouch/datastruct/utils_datastruct.h
    ${A_DIR_ROOT}/src/model/touch/square/Square.h
    ${A_DIR_ROOT}/src/model/touch/square/SquareMethod.h
    ${A_DIR_ROOT}/src/model/touch/rubber/Rubber.h
    ${A_DIR_ROOT}/src/model/touch/rubber/RubberMethod.h
    ${A_DIR_ROOT}/src/model/touch/multi_thread_data.h
    ${A_DIR_ROOT}/src/model/touch/TabletController.h
    ${A_DIR_ROOT}/src/model/touch/pen/PenMethod.h
    ${A_DIR_ROOT}/src/model/touch/pen/Pen.h
    ${A_DIR_ROOT}/src/model/touch/laser/LaserMethod.h
    ${A_DIR_ROOT}/src/model/touch/laser/Laser.h
    ${A_DIR_ROOT}/src/model/touch/highlighter/HighligterMethod.h
    ${A_DIR_ROOT}/src/model/touch/highlighter/Highligter.h
    ${A_DIR_ROOT}/src/model/touch/copy_cut/copy_cut_selection.h
    ${A_DIR_ROOT}/src/model/touch/TabletPenMethod.h
    ${A_DIR_ROOT}/src/model/touch/paint.h
    ${A_DIR_ROOT}/src/model/touch/TabletUtils.h
    ${A_DIR_ROOT}/src/model/images/fromimage.h
    ${A_DIR_ROOT}/src/model/pdf/topdf.h
    ${A_DIR_ROOT}/src/model/Scheduler/WTask.h
    ${A_DIR_ROOT}/src/model/Scheduler/WPool.h
    ${A_DIR_ROOT}/src/model/Scheduler/Scheduler.h
    ${A_DIR_ROOT}/src/model/lastedit/redoundo.h
    ${A_DIR_ROOT}/src/model/utils/color_define_rgb.h
    ${A_DIR_ROOT}/src/model/utils/utils.h
    ${A_DIR_ROOT}/src/model/utils/copy_text.h
    ${A_DIR_ROOT}/src/model/utils/areyousure/areyousure.h
    ${A_DIR_ROOT}/src/model/utils/get_file_dir/get_file_dir.h
    ${A_DIR_ROOT}/src/model/utils/posizione_binario.h
    ${A_DIR_ROOT}/src/model/utils/color/color_chooser.h
    ${A_DIR_ROOT}/src/model/utils/path/get_path.h
    ${A_DIR_ROOT}/src/model/utils/path/pathfile.h
    ${A_DIR_ROOT}/src/model/utils/aboutQt/aboutqt.h
    ${A_DIR_ROOT}/src/model/utils/remove_key/remove_key.h
    ${A_DIR_ROOT}/src/model/utils/changeLanguage.h
    ${A_DIR_ROOT}/src/model/utils/Optional.h
    ${A_DIR_ROOT}/src/model/utils/time/waitTime.h
    ${A_DIR_ROOT}/src/model/utils/time/current_time.h
    ${A_DIR_ROOT}/src/model/utils/common_error_definition.h
    ${A_DIR_ROOT}/src/model/utils/lastModification/lastmodification.h
    ${A_DIR_ROOT}/src/model/utils/slash/slash.h
    ${A_DIR_ROOT}/src/model/utils/mostra_explorer/mostra_explorer.h
    ${A_DIR_ROOT}/src/model/utils/checkpassword/checkpassword.h
    ${A_DIR_ROOT}/src/model/utils/WCommonScript.h
    ${A_DIR_ROOT}/src/model/utils/common_def.h
    ${A_DIR_ROOT}/src/model/utils/threadcount.h
    ${A_DIR_ROOT}/src/model/utils/random/random.h
    ${A_DIR_ROOT}/src/model/utils/get_path_application.h
    ${A_DIR_ROOT}/src/model/utils/permission/permission.h
    ${A_DIR_ROOT}/src/model/utils/platform.h
    ${A_DIR_ROOT}/src/model/utils/setting_define.h
    ${A_DIR_ROOT}/src/model/utils/removenotwriternote.h
    ${A_DIR_ROOT}/src/model/utils/get_only_name/get_only_name.h
    ${A_DIR_ROOT}/src/model/datawrite/source_read_ext.h
    ${A_DIR_ROOT}/src/model/datawrite/renamefile_f_zip.h
    ${A_DIR_ROOT}/src/model/datawrite/savefile.h
    ${A_DIR_ROOT}/src/model/currenttitle/option/modality_data.h
    ${A_DIR_ROOT}/src/model/currenttitle/document.h
    ${A_DIR_ROOT}/src/model/currenttitle/checksimilecopybook.h
    ${A_DIR_ROOT}/src/model/currenttitle/merge_currenttitle/merge_currenttitle.h
    ${A_DIR_ROOT}/src/model/testing/testingzip.h
    ${A_DIR_ROOT}/src/model/testing/memtest.h
    ${A_DIR_ROOT}/src/model/testing/testingcore.h
    ${A_DIR_ROOT}/src/model/audiorecord/audiorecord.h
    ${A_DIR_ROOT}/src/model/dataread/xmlstruct.h
    ${A_DIR_ROOT}/src/model/dataread/readlistarray.h
    ${A_DIR_ROOT}/src/model/cloud/struct_file.h
    ${A_DIR_ROOT}/src/model/cloud/error_type.h
    ${A_DIR_ROOT}/src/model/cloud/utils/downloadfile.h
    ${A_DIR_ROOT}/src/model/cloud/utils/toencrypt.h
    ${A_DIR_ROOT}/src/model/cloud/utils/shared_definition.h
    ${A_DIR_ROOT}/src/model/cloud/cloud_ui.h
    ${A_DIR_ROOT}/src/model/cloud/struct_mail.h
    ${A_DIR_ROOT}/src/model/cloud/url.h
    ${A_DIR_ROOT}/src/model/cloud/struct_user.h
    ${A_DIR_ROOT}/src/model/cloud/cloud_controll.h
    ${A_DIR_ROOT}/src/model/cloud/request_type.h
    ${A_DIR_ROOT}/src/model/log/log_ui/log_ui.h
    ${A_DIR_ROOT}/src/model/preview/preview.h
    ${A_DIR_ROOT}/src/model/restore_file/restore_file_critic.h
    ${A_DIR_ROOT}/src/model/frompdf/frompdf.h
    ${A_DIR_ROOT}/src/model/frompdf/convertImg.h
    ${A_DIR_ROOT}/src/model/windows/mostra_finestra_i.h
    ${A_DIR_ROOT}/src/model/windows/updatecheck.h
    ${A_DIR_ROOT}/src/model/sheet/style_struct.h
)

if (IOS)
    set(PROJECT_SOURCES_WRITERNOTE
        ${PROJECT_SOURCES_WRITERNOTE}
        $ENV{HOME}/writernote-qt/src/core/WPainter/WPainter_ios.mm
        $ENV{HOME}/writernote-qt/src/core/WImage.mm
    )
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUGINFO -O0")

set(A_SOURCES_CPP
    ${A_SOURCES_CPP}
    ${A_DIR_ROOT}/src/main.cpp
    ${A_DIR_ROOT}/src/controller/Controller.cpp
    ${A_DIR_ROOT}/src/controller/ControllerAudio/ControllerAudioRecorder.cpp
    ${A_DIR_ROOT}/src/controller/ControllerAudio/ControllerAudioPlayer.cpp
    ${A_DIR_ROOT}/src/controller/ControllerCanvas/ControllerCanvas.cpp
    ${A_DIR_ROOT}/src/controller/ControllerCanvas/WQMLCanvasComponent.cpp
    ${A_DIR_ROOT}/src/controller/ControllerList/ControllerList.cpp
    ${A_DIR_ROOT}/src/controller/ControllerList/WQMLItemListComponent.cpp
    ${A_DIR_ROOT}/src/controller/ControllerListFiles/ControllerListFiles.cpp
    ${A_DIR_ROOT}/src/controller/ControllerListFiles/ControllerListFilesFolder.cpp
    ${A_DIR_ROOT}/src/controller/ControllerPageCounter/ControllerPageCounter.cpp
    ${A_DIR_ROOT}/src/controller/ControllerToolBar/ControllerToolBar.cpp
    ${A_DIR_ROOT}/src/controller/ControllerToolBar/ControllerDocument.cpp
    ${A_DIR_ROOT}/src/controller/ControllerListFiles/Folder.cpp
    ${A_DIR_ROOT}/src/controller/ControllerColor/ControllerColor.cpp
    ${A_DIR_ROOT}/src/controller/ControllerCanvas/WQMLCanvasHandler.h
    ${A_DIR_ROOT}/src/controller/ControllerCanvas/WQMLCanvasHandler.cpp
    ${PROJECT_SOURCES_WRITERNOTE}
)

if (IOS)
    set(A_SOURCES_CPP
        ${A_SOURCES_CPP}
        ${A_DIR_ROOT}/src/controller/ControllerListFiles/ControllerCommonFiles.mm
    )

endif()

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

find_package(QT NAMES Qt6 COMPONENTS ${A_QT_MODULES} REQUIRED)
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

if(UNIX AND NOT APPLE AND NOT MINGW)
    set(LINUX TRUE)
endif()

if(IOS)
    message("-- Configure libzip for ios")
    include_directories(/opt/homebrew/Cellar/libzip/1.9.2/include/)
    target_link_libraries(${PROJECT_NAME} PRIVATE $ENV{HOME}/writernote-qt/3rdparty/libzip_ios.a)
elseif(MACOS_BUILD OR APPLE)
    include_directories(/opt/homebrew/Cellar/libzip/1.9.2/include/)
    target_link_libraries(${PROJECT_NAME} PRIVATE /opt/homebrew/Cellar/libzip/1.9.2/lib/libzip.dylib)
elseif(WIN)
    include_directories(${PROJECT_SOURCE_DIR}/3rdparty/libzip/install/include/)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/3rdparty/libzip/install/lib/libzip.a)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/3rdparty/zlib-ng/install/lib/libzlib.a)
else(UNIX)
    message("Set target linux")
    target_link_libraries(${PROJECT_NAME} PRIVATE /usr/lib/x86_64-linux-gnu/libzip.so)
    #target_link_libraries(${PROJECT_NAME} PRIVATE /usr/lib/libzip.so)
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
                        XCODE_ATTRIBUTE_SWIFT_VERSION "5.8"
	)
endif()


enable_testing()

function(SETUP_TESTS)
	foreach(_testname ${ARGN})
		string(REPLACE "/" ";" List_file ${_testname})
		list(LENGTH List_file len)
		list(GET List_file -1 last_item)

		add_executable(${last_item} ${_testname}.cpp )
		add_test(NAME ${last_item} COMMAND ${last_item})
		target_link_libraries(${last_item} Qt${QT_MAJOR_VERISION}::Test)
		target_link_libraries(${last_item} Qt${QT_MAJOR_VERISION}::Core)
		target_link_libraries(${last_item} Qt${QT_MAJOR_VERISION}::Gui)
		target_link_libraries(${last_item} Qt${QT_MAJOR_VERISION}::Quick)
	endforeach()
endfunction()

if (NOT IOS)
SETUP_TESTS(
		src/test/model/test_utils/test_WCommonScript
		src/test/controller/ControllerTest
                src/test/model/test_core/test_WPair
)
endif()
