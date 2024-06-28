cmake_minimum_required(VERSION 3.5)
project(InLink VERSION 0.1 LANGUAGES CXX)
# Cmake autometeobject, autouserinterface, autoresources using
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
# cmake C++ standard using
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# find Qt6 neccessary packages and Liguisttools for translations
find_package(Qt6 REQUIRED COMPONENTS Gui Core Widgets Sql Network LinguistTools WebSockets)
find_package(OpenSSL REQUIRED)
# set main items dirs, such that Components and Database and Resources and Translations
set(COMPONENTS_DIR Components)
set(DATABASE_DIR database)
set(PAGES_DIR Pages)
set(TS_FILES InLink_en_US.ts)
set(RESOURCE_FILES resource.qrc icon.rc)
# fetch files specified by each dir by using GLOB
file(GLOB_RECURSE DATABASE_FILES ${DATABASE_DIR}/*.h ${DATABASE_DIR}/*.cpp)
file(GLOB_RECURSE COMPONENTS_FILES ${COMPONENTS_DIR}/*.h ${COMPONENTS_DIR}/*.cpp ${COMPONENTS_DIR}/*.ui)
file(GLOB_RECURSE PAGES_FILES ${PAGES_DIR}/*.h ${PAGES_DIR}/*.cpp ${PAGES_DIR}/*.ui)
file(GLOB_RECURSE QSS_FILES qss/*.qss)
file(GLOB_RECURSE UTILS_FILES utils/*.h utils/*.cpp utils/*.ui)
file(GLOB SCHEMA_FILES Schematics/*.cpp Schematics/*.h)
# project secret key configuration
# 1-first read the secret file
file(READ "${CMAKE_SOURCE_DIR}/.env" ENV_FILE_CONTENT)
# 2-second extract the secret needed data and if the data not found give error
string(REGEX MATCH "SECRET_KEY=([^\n]*)" _ ${ENV_FILE_CONTENT})
set(SECRET_KEY ${CMAKE_MATCH_1})
# Check if SECRET_KEY was found
if (NOT SECRET_KEY)
    message(FATAL_ERROR "SECRET_KEY not found in .env file")
endif()
# 3-third add the defination of the secret key into the source code!
configure_file(${CMAKE_SOURCE_DIR}/secret_key.h.in ${CMAKE_BINARY_DIR}/secret_key.h @ONLY)
# setup configuring the project using qt6_add_executable macro
# HINT: this project requires the minimum Qt 6.3
qt6_standard_project_setup()
qt6_add_executable(InLink
    MANUAL_FINALIZATION
    main.cpp main.h
    ${COMPONENTS_FILES}
    ${RESOURCE_FILES}
    ${QSS_FILES}
    ${UTILS_FILES}
    ${DATABASE_FILES}
    ${PAGES_FILES}
    ${SCHEMA_FILES}
    Schematics/person.h Schematics/person.cpp
    Schematics/company.h Schematics/company.cpp
)
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
target_link_libraries(InLink
    PUBLIC
        Qt6::Widgets
        Qt6::Core
        Qt6::Gui
        Qt6::Sql
        Qt6::Network
        Qt6::WebSockets
    PRIVATE
        OpenSSL::SSL
        OpenSSL::Crypto
)
# set master include folder for preventing the relative file path
target_include_directories(InLink PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})
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
