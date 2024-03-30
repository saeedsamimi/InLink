cmake_minimum_required(VERSION 3.5)

project(InLink VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(DEFINED $ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
elseif(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    message(FATAL_ERROR "Please specify the CMAKE_TOOLCHAIN_FILE for the vcpkg.cmake file")
endif()

find_package(Qt6 REQUIRED COMPONENTS Gui Core Widgets LinguistTools)

set(COMPONENTS_DIR Components)
set(TS_FILES InLink_en_US.ts)
set(RESOURCE_FILES resource.qrc icon.rc)

file(GLOB COMPONENTS_FILES ${COMPONENTS_DIR}/*.h ${COMPONENTS_DIR}/*.cpp ${COMPONENTS_DIR}/*.ui)
file(GLOB QSS_FILES qss/*.qss)

set(TEST_FILES test/test_captcha.cpp test/test_captcha.h test/test_captcha.ui)

set(PROJECT_MAIN_FILES
    main.cpp
    mainwindow.cpp mainwindow.h mainwindow.ui
    loginsignin.cpp loginsignin.h loginsignin.ui
)

file(GLOB UTILS_FILES utils/*.h utils/*.cpp)

qt6_add_executable(InLink
    MANUAL_FINALIZATION
    ${COMPONENTS_FILES}
    ${PROJECT_MAIN_FILES}
    ${RESOURCE_FILES}
    ${TEST_FILES}
    ${QSS_FILES}
    ${UTILS_FILES}
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

target_link_libraries(InLink PRIVATE
    Qt6::Widgets Qt6::Core Qt6::Gui)

target_include_directories(InLink PRIVATE ${CMAKE_SOURCE_DIR})

include(GNUInstallDirs)
install(TARGETS InLink
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

add_custom_command(OUTPUT ${TS_FILES}
    PRE_BUILD
    COMMAND lupdate.exe . -ts "${TS_FILES}"
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMENT "Updating translations.."
)

qt_finalize_executable(InLink)
