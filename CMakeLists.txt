cmake_minimum_required(VERSION 3.5)

project(InLink VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_TOOLCHAIN_FILE "C:/src/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

find_package(Qt6 REQUIRED COMPONENTS Gui Core Widgets LinguistTools)
find_package(bsoncxx CONFIG REQUIRED)
find_package(mongocxx CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

set(TS_FILES InLink_en_US.ts)

set(RESOURCE_FILES resource.qrc)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    Components/captcha.cpp Components/captcha.h
    Components/captchaimage.cpp Components/captchaimage.h
    Components/captchaverifier.cpp Components/captchaverifier.h
    Components/loginform.cpp Components/loginform.h Components/loginform.ui
    Components/fullexapndedtabbedwidget.cpp Components/fullexapndedtabbedwidget.h
    Components/footerimageview.cpp Components/footerimageview.h
    Components/imageviewer.cpp Components/imageviewer.h
    test/test_captcha.cpp test/test_captcha.h test/test_captcha.ui
    loginsignin.cpp loginsignin.h loginsignin.ui
    ${RESOURCE_FILES}
)

qt6_add_executable(InLink
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    icon.rc
)

qt6_add_translations(InLink
    TS_FILES ${TS_FILES}
    QM_FILES_OUTPUT_VARIABLE qm_files)
install(FILES ${qm_files} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set_target_properties(InLink PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

set_target_properties(InLink PROPERTIES FOLDER "qtc_runnable")

set(BSONCXX_LIB $<IF:$<TARGET_EXISTS:mongo::bsoncxx_static>,mongo::bsoncxx_static,mongo::bsoncxx_shared>)
set(MONGOCXX_LIB $<IF:$<TARGET_EXISTS:mongo::mongocxx_static>,mongo::mongocxx_static,mongo::mongocxx_shared>)

target_link_libraries(InLink PRIVATE
    Qt6::Widgets Qt6::Core Qt6::Gui
    ${MONGOCXX_LIB}
    ${BSONCXX_LIB}
    Database
    )

target_include_directories(InLink PRIVATE db)

include(GNUInstallDirs)
install(TARGETS InLink
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

add_custom_command(
    OUTPUT ${TS_FILES}
    COMMAND lupdate.exe . -ts "${TS_FILES}"
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMENT "Updating translations.."
)

qt_finalize_executable(InLink)
