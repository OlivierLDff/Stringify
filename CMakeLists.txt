#
#   Stringify CMake build script
#
#   Copyright Olivier Le Doeuff 2019
#

# ┌──────────────────────────────────────────────────────────────────┐
# │                       CMAKE PROPERTIES                           │
# └──────────────────────────────────────────────────────────────────┘

cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

# DEPENDENCIES

set(QSUPERMACROS_REPOSITORY "https://github.com/OlivierLDff/QSuperMacros" CACHE STRING "Repository of QSuperMacros")
set(QSUPERMACROS_TAG "master" CACHE STRING "Git tag/branch of QSuperMacros")

set(GTEST_REPOSITORY "https://github.com/google/googletest" CACHE STRING "Repository of googletest")
set(GTEST_TAG "master" CACHE STRING "Git tag/branch of googletest")

# ┌──────────────────────────────────────────────────────────────────┐
# │                       PROJECT SETTINGS                           │
# └──────────────────────────────────────────────────────────────────┘

# OPTIONS

set(STRINGIFY_VERSION_MAJOR 1)
set(STRINGIFY_VERSION_MINOR 0)
set(STRINGIFY_VERSION_PATCH 0)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.git")
    EXECUTE_PROCESS(
        COMMAND git describe --always
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_VARIABLE STRINGIFY_VERSION_TAG
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
endif()
if(NOT STRINGIFY_VERSION_TAG)
    set(STRINGIFY_VERSION_TAG 00000000)
endif(NOT STRINGIFY_VERSION_TAG)
set(STRINGIFY_VERSION_TAG_HEX 0x${STRINGIFY_VERSION_TAG})
set(STRINGIFY_VERSION ${STRINGIFY_VERSION_MAJOR}.${STRINGIFY_VERSION_MINOR}.${STRINGIFY_VERSION_PATCH} CACHE STRING "" FORCE)

# General
set(STRINGIFY_PROJECT "Stringify" CACHE STRING "Project Name")
set(STRINGIFY_TARGET ${STRINGIFY_PROJECT} CACHE STRING "Stringify library name")
set(STRINGIFY_VERSION ${STRINGIFY_VERSION_MAJOR}.${STRINGIFY_VERSION_MINOR}.${STRINGIFY_VERSION_PATCH} CACHE STRING "Stringify current version, this is only decorative and will not configure any files" FORCE)

set(STRINGIFY_BUILD_SHARED OFF CACHE BOOL "Build as a shared library (ON) or as static (OFF)")
set(STRINGIFY_FOLDER_PREFIX ${STRINGIFY_PROJECT} CACHE STRING "Prefix folder for all Stringify generated targets in generated project (only decorative)")
set(STRINGIFY_ENABLE_FLATBUFFERS ON CACHE BOOL "Enable Flatbuffers support")
set(STRINGIFY_ENABLE_FLATC OFF CACHE BOOL "Generate C++ headers using flatc (require STRINGIFY_ENABLE_FLATBUFFERS)")

set(STRINGIFY_USE_NAMESPACE ON CACHE BOOL "Should we use namespace")
set(STRINGIFY_NAMESPACE ${STRINGIFY_PROJECT} CACHE STRING "Namespace for the library")

# Tests
set(STRINGIFY_ENABLE_TESTS ON CACHE BOOL "Create or not a target for test (compatible with CTests)")
set(STRINGIFY_TESTS_PREFIX ${STRINGIFY_PROJECT} CACHE STRING "Prefix for all Stringify tests")

# Install
set(STRINGIFY_ENABLE_INSTALL OFF CACHE BOOL "Create or not a target for install")
set(STRINGIFY_INSTALL_PREFIX ${STRINGIFY_PROJECT} CACHE STRING "Prefix for all Stringify headers in the install folder")

# CREATE PROJECT

project(${STRINGIFY_PROJECT} VERSION ${STRINGIFY_VERSION} LANGUAGES C CXX)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 11)

# LOG OPTIONS

message("---------------- STRINGIFY OPTIONS. ----------------")

#General
message(STATUS "STRINGIFY_PROJECT            : " ${STRINGIFY_PROJECT})
message(STATUS "STRINGIFY_TARGET             : " ${STRINGIFY_TARGET})
message(STATUS "STRINGIFY_VERSION            : " ${STRINGIFY_VERSION})
message(STATUS "STRINGIFY_VERSION_TAG        : " ${STRINGIFY_VERSION_TAG})
message(STATUS "STRINGIFY_BUILD_SHARED       : " ${STRINGIFY_BUILD_SHARED})
message(STATUS "STRINGIFY_FOLDER_PREFIX      : " ${STRINGIFY_FOLDER_PREFIX})
message(STATUS "STRINGIFY_ENABLE_FLATBUFFERS : " ${STRINGIFY_ENABLE_FLATBUFFERS})
message(STATUS "STRINGIFY_ENABLE_FLATC       : " ${STRINGIFY_ENABLE_FLATC})

# Tests
message(STATUS "STRINGIFY_ENABLE_TESTS       : " ${STRINGIFY_ENABLE_TESTS})
if(STRINGIFY_ENABLE_TESTS)
message(STATUS "STRINGIFY_TESTS_PREFIX       : " ${STRINGIFY_TESTS_PREFIX})
endif(STRINGIFY_ENABLE_TESTS)

# Install
message(STATUS "STRINGIFY_ENABLE_INSTALL     : " ${STRINGIFY_ENABLE_INSTALL})
if(STRINGIFY_ENABLE_INSTALL)
message(STATUS "STRINGIFY_INSTALL_PREFIX     : " ${STRINGIFY_INSTALL_PREFIX})
endif(STRINGIFY_ENABLE_INSTALL)

message("---------------- DONE WITH OPTIONS. -----------------")
message("                                                     ")

# ┌──────────────────────────────────────────────────────────────────┐
# │                         QT5 CMAKE                                │
# └──────────────────────────────────────────────────────────────────┘

find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Quick CONFIG REQUIRED)
find_package(Qt5QuickCompiler CONFIG REQUIRED)

# ┌──────────────────────────────────────────────────────────────────┐
# │                       DEPENDENCIES                               │
# └──────────────────────────────────────────────────────────────────┘

include(FetchContent)

# QSuperMacros
FetchContent_Declare(
    QSuperMacros
    GIT_REPOSITORY ${QSUPERMACROS_REPOSITORY}
    GIT_TAG        ${QSUPERMACROS_TAG}
)

# googletest
FetchContent_Declare(
    googletest
    GIT_REPOSITORY ${GTEST_REPOSITORY}
    GIT_TAG        ${GTEST_TAG}
)

set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
set(FETCHCONTENT_QUIET ON)

FetchContent_MakeAvailable(QSuperMacros)

# ┌──────────────────────────────────────────────────────────────────┐
# │                          STRINGIFY                               │
# └──────────────────────────────────────────────────────────────────┘

# Add qml to the qtquick compiler
qtquick_compiler_add_resources(STRINGIFY_QML_RES ${CMAKE_CURRENT_SOURCE_DIR}/qml/Stringify.qrc)

# Dont Run Moc on cpp file generated from cpp
foreach(STRINGIFY_QML_FILE ${STRINGIFY_QML_RES})
    set_property(SOURCE ${STRINGIFY_QML_FILE} PROPERTY SKIP_AUTOMOC ON)
    source_group( "QmlMoc Files" FILES ${STRINGIFY_QML_FILE} )
endforeach()

# We use every qml file inside the IDE.
file(GLOB_RECURSE STRINGIFY_QML_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/qml/*.qml)

# Set file in folder, good for visualization inside IDE
foreach(_source IN ITEMS ${STRINGIFY_QML_SRCS})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel ${CMAKE_CURRENT_SOURCE_DIR}/qml "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("Qml Files\\${_group_path}" FILES "${_source}")
endforeach()

set(STRINGIFY_SRCS_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(STRINGIFY_INCS_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/src/include)
set(STRINGIFY_PRIVATE_INCS_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/src/include/Stringify)

# STRINGIFY SOURCES
set(STRINGIFY_UTILS_SRCS
    ${STRINGIFY_SRCS_FOLDER}/Utils.cpp
    ${STRINGIFY_SRCS_FOLDER}/Version.cpp
)

set(STRINGIFY_API_SRCS
    ${STRINGIFY_SRCS_FOLDER}/VersionRegex.cpp
    ${STRINGIFY_SRCS_FOLDER}/AddressRegex.cpp
)

set(STRINGIFY_SRCS ${STRINGIFY_UTILS_SRCS}
    ${STRINGIFY_API_SRCS}
    ${STRINGIFY_QML_RES}
    ${STRINGIFY_QML_SRCS}
)

set(STRINGIFY_UTILS_INCS
    ${STRINGIFY_INCS_FOLDER}/Stringify.hpp
    ${STRINGIFY_PRIVATE_INCS_FOLDER}/Export.hpp
    ${STRINGIFY_PRIVATE_INCS_FOLDER}/Utils.hpp
    ${STRINGIFY_PRIVATE_INCS_FOLDER}/Version.hpp
)

set(STRINGIFY_API_INCS
    ${STRINGIFY_PRIVATE_INCS_FOLDER}/VersionRegex.hpp
    ${STRINGIFY_PRIVATE_INCS_FOLDER}/AddressRegex.hpp
)

set(STRINGIFY_INCS ${STRINGIFY_UTILS_INCS}
    ${STRINGIFY_API_INCS}
)

source_group("Utils" FILES ${STRINGIFY_UTILS_INCS})
source_group("Utils" FILES ${STRINGIFY_UTILS_SRCS})
source_group("Api" FILES ${STRINGIFY_API_SRCS})
source_group("Api" FILES ${STRINGIFY_API_INCS})
source_group("Qml" FILES ${STRINGIFY_QML_SRCS})

# STRINGIFY TARGET
if(STRINGIFY_BUILD_SHARED)

    add_library(${STRINGIFY_TARGET} SHARED ${STRINGIFY_SRCS} ${STRINGIFY_INCS})
    target_compile_definitions(${STRINGIFY_TARGET} PRIVATE "-DSTRINGIFY_DLL_EXPORT")

else(STRINGIFY_BUILD_SHARED)

    add_library(${STRINGIFY_TARGET} STATIC  ${STRINGIFY_SRCS} ${STRINGIFY_INCS})
    target_compile_definitions(${STRINGIFY_TARGET} PUBLIC "-DSTRINGIFY_STATIC")

endif(STRINGIFY_BUILD_SHARED)

# Set include directory
target_include_directories(${STRINGIFY_TARGET} PUBLIC $<BUILD_INTERFACE:${STRINGIFY_INCS_FOLDER}> $<INSTALL_INTERFACE:${STRINGIFY_INSTALL_PREFIX}>)

# Avoid libstringify on darwin for example.
set_target_properties(${STRINGIFY_TARGET} PROPERTIES PREFIX "")

# Link libraries
target_link_libraries(${STRINGIFY_TARGET} ${QSUPERMACROS_TARGET})

set_target_properties(${STRINGIFY_TARGET} PROPERTIES AUTOMOC TRUE)
set_target_properties(${STRINGIFY_TARGET} PROPERTIES AUTORCC TRUE)
qt5_use_modules(${STRINGIFY_TARGET} Core Quick)

set_target_properties(${STRINGIFY_TARGET} PROPERTIES FOLDER ${STRINGIFY_FOLDER_PREFIX})

# Version
target_compile_definitions(${STRINGIFY_TARGET} PRIVATE -DSTRINGIFY_VERSION_MAJOR=${STRINGIFY_VERSION_MAJOR})
target_compile_definitions(${STRINGIFY_TARGET} PRIVATE -DSTRINGIFY_VERSION_MINOR=${STRINGIFY_VERSION_MINOR})
target_compile_definitions(${STRINGIFY_TARGET} PRIVATE -DSTRINGIFY_VERSION_PATCH=${STRINGIFY_VERSION_PATCH})
target_compile_definitions(${STRINGIFY_TARGET} PRIVATE -DSTRINGIFY_VERSION_TAG=${STRINGIFY_VERSION_TAG})
target_compile_definitions(${STRINGIFY_TARGET} PRIVATE -DSTRINGIFY_VERSION_TAG_HEX=${STRINGIFY_VERSION_TAG_HEX})

if(STRINGIFY_USE_NAMESPACE)
    target_compile_definitions(${STRINGIFY_TARGET} PUBLIC -DSTRINGIFY_USE_NAMESPACE)
    target_compile_definitions(${STRINGIFY_TARGET} PUBLIC -DSTRINGIFY_NAMESPACE=${STRINGIFY_NAMESPACE})
endif(STRINGIFY_USE_NAMESPACE)

# ┌──────────────────────────────────────────────────────────────────┐
# │                           TESTS                                  │
# └──────────────────────────────────────────────────────────────────┘

if(STRINGIFY_ENABLE_TESTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/CTestLists.txt)
endif(STRINGIFY_ENABLE_TESTS)

# ┌──────────────────────────────────────────────────────────────────┐
# │                         INSTALL                                  │
# └──────────────────────────────────────────────────────────────────┘

if(STRINGIFY_ENABLE_INSTALL)
    include(${CMAKE_CURRENT_SOURCE_DIR}/CInstallLists.txt)
endif(STRINGIFY_ENABLE_INSTALL)