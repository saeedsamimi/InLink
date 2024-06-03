cmake_minimum_required(VERSION 3.5)
project(InLink VERSION 0.1 LANGUAGES CXX)
# Cmake autometeobject, autouserinterface, autoresources using
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
# cmake C++ standard using
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# find Qt6 neccessary packages and Liguisttools for translations
find_package(Qt6 REQUIRED COMPONENTS Gui Core Widgets Sql LinguistTools)
# set main items dirs, such that Components and Database and Resources and Translations
set(COMPONENTS_DIR Components)
set(DATABASE_DIR database)
set(PAGES_DIR Pages)
set(TS_FILES InLink_en_US.ts)
set(RESOURCE_FILES resource.qrc icon.rc)
# fetch files specified by each dir by using GLOB
file(GLOB DATABASE_FILES ${DATABASE_DIR}/*.h ${DATABASE_DIR}/*.cpp)
file(GLOB COMPONENTS_FILES ${COMPONENTS_DIR}/*.h ${COMPONENTS_DIR}/*.cpp ${COMPONENTS_DIR}/*.ui)
file(GLOB PAGES_FILES ${PAGES_DIR}/*.h ${PAGES_DIR}/*.cpp ${PAGES_DIR}/*.ui)
file(GLOB QSS_FILES qss/*.qss)
file(GLOB UTILS_FILES utils/*.h utils/*.cpp utils/*.ui)
# setting test files
set(TEST_FILES
    test/test_captcha.cpp test/test_captcha.h test/test_captcha.ui # test files for Captcha
)
# Project main runners files
set(PROJECT_MAIN_FILES
    main.cpp
    splashscreen.cpp splashscreen.h splashscreen.ui
    loginsignin.cpp loginsignin.h loginsignin.ui)

qt6_standard_project_setup()
qt6_add_executable(InLink
    MANUAL_FINALIZATION
    ${COMPONENTS_FILES}
    ${PROJECT_MAIN_FILES}
    ${RESOURCE_FILES}
    ${TEST_FILES}
    ${QSS_FILES}
    ${UTILS_FILES}
    ${DATABASE_FILES}
    ${PAGES_FILES}
    Components/Textboxes/codeverifyedit.h Components/Textboxes/codeverifyedit.cpp
    Components/Textboxes/codeverifierlayout.h Components/Textboxes/codeverifierlayout.cpp
    database/models/usermodel.h database/models/usermodel.cpp
    Components/App/mecomponent.h Components/App/mecomponent.cpp Components/App/mecomponent.ui
    Components/App/homecomponent.h Components/App/homecomponent.cpp Components/App/homecomponent.ui
    Components/App/usernetworkcomponent.h Components/App/usernetworkcomponent.cpp Components/App/usernetworkcomponent.ui
    Components/App/chatcomponent.h Components/App/chatcomponent.cpp Components/App/chatcomponent.ui
    Components/App/jobscomponent.h Components/App/jobscomponent.cpp Components/App/jobscomponent.ui
    Components/Dialogs/selectabilitiesdialog.cpp Components/Dialogs/selectabilitiesdialog.h Components/Dialogs/selectabilitiesdialog.ui

    Components/Delegates/postwidget.h Components/Delegates/postwidget.cpp Components/Delegates/postwidget.ui
    database/models/postmodel.h database/models/postmodel.cpp)
# set translations and then install the .qm file into CURRENT_BIN_DIR
qt6_add_translations(InLink
    TS_FILES ${TS_FILES}
    QM_FILES_OUTPUT_VARIABLE qm_files)
install(FILES ${qm_files} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
# set bundle properties and Win32 runnable
set_target_properties(InLink PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
set_target_properties(InLink PROPERTIES FOLDER "qtc_runnable")
# link Qt6 libraries with the project
target_link_libraries(InLink PRIVATE
    Qt6::Widgets Qt6::Core Qt6::Gui Qt6::Sql)
# set master include folder for preventing the relative file path
target_include_directories(InLink PRIVATE ${CMAKE_SOURCE_DIR})
# set GNU install dirs for the install time dirs
include(GNUInstallDirs)
install(TARGETS InLink
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
# configure deployement for windows
if(WIN32)
    add_custom_command(TARGET InLink POST_BUILD
        COMMAND "${WINDEPLOYQT_EXECUTABLE}" . --no-translations --pdb
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        COMMENT "The windeploqt is running now!")
endif()
# finalize the project
qt_finalize_executable(InLink)
