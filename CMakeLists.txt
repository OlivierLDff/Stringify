#
#   Stringify CMake build script
#
#   Copyright Olivier Le Doeuff 2019
#

# ┌──────────────────────────────────────────────────────────────────┐
# │                       CMAKE PROPERTIES                           │
# └──────────────────────────────────────────────────────────────────┘

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# ┌──────────────────────────────────────────────────────────────────┐
# │                       PROJECT SETTINGS                           │
# └──────────────────────────────────────────────────────────────────┘

# OPTIONS

set(STRINGIFY_VERSION_MAJOR 1)
set(STRINGIFY_VERSION_MINOR 2)
set(STRINGIFY_VERSION_PATCH 0)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.git")
    EXECUTE_PROCESS(
        COMMAND git rev-parse --short HEAD
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
set(STRINGIFY_ENABLE_PCH ON CACHE BOOL
 "Enable precompile headers support for 'Qaterial'. \"
 Only work if CMake support 'target_precompile_headers'. \"
 This can speed up compilation time.")
set(STRINGIFY_ENABLE_QML ON CACHE STRING "Build Support for Qml. Stringify.Validitor & Stringify.Formatter")

set(STRINGIFY_BUILD_SHARED OFF CACHE BOOL "Build as a shared library (ON) or as static (OFF)")
set(STRINGIFY_FOLDER_PREFIX ${STRINGIFY_PROJECT} CACHE STRING "Prefix folder for all Stringify generated targets in generated project (only decorative)")

# Tests
set(STRINGIFY_ENABLE_TESTS OFF CACHE BOOL "Create or not a target for test (compatible with CTests)")
set(STRINGIFY_TESTS_PREFIX ${STRINGIFY_PROJECT} CACHE STRING "Prefix for all Stringify tests")

# CREATE PROJECT

project(${STRINGIFY_PROJECT} VERSION ${STRINGIFY_VERSION} LANGUAGES C CXX)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# LOG OPTIONS

message(STATUS "---------------- STRINGIFY OPTIONS. ----------------")

#General
message(STATUS "STRINGIFY_PROJECT            : " ${STRINGIFY_PROJECT})
message(STATUS "STRINGIFY_TARGET             : " ${STRINGIFY_TARGET})
message(STATUS "STRINGIFY_VERSION            : " ${STRINGIFY_VERSION})
message(STATUS "STRINGIFY_VERSION_TAG        : " ${STRINGIFY_VERSION_TAG})
message(STATUS "STRINGIFY_BUILD_SHARED       : " ${STRINGIFY_BUILD_SHARED})
message(STATUS "STRINGIFY_FOLDER_PREFIX      : " ${STRINGIFY_FOLDER_PREFIX})
message(STATUS "STRINGIFY_ENABLE_PCH         : " ${STRINGIFY_ENABLE_PCH})

# Tests
message(STATUS "STRINGIFY_ENABLE_TESTS       : " ${STRINGIFY_ENABLE_TESTS})
if(STRINGIFY_ENABLE_TESTS)
message(STATUS "STRINGIFY_TESTS_PREFIX       : " ${STRINGIFY_TESTS_PREFIX})
endif(STRINGIFY_ENABLE_TESTS)

message(STATUS "---------------- DONE WITH OPTIONS. -----------------")

# ┌──────────────────────────────────────────────────────────────────┐
# │                       DEPENDENCIES                               │
# └──────────────────────────────────────────────────────────────────┘

find_package(Qt5 REQUIRED COMPONENTS
  Core
  Qml
)

if(STRINGIFY_ENABLE_QML)
  find_package(Qt5 REQUIRED COMPONENTS
    Qml
    Quick
    QuickControls2
    QuickCompiler
  )
endif()

include(cmake/FetchSpdlog.cmake)

# ┌──────────────────────────────────────────────────────────────────┐
# │                          STRINGIFY                               │
# └──────────────────────────────────────────────────────────────────┘

if(STRINGIFY_ENABLE_QML)

  file(GLOB_RECURSE STRINGIFY_QML_SRCS qml/*.qml)

  foreach(SOURCE IN ITEMS ${STRINGIFY_QML_SRCS})
      get_filename_component(SOURCE_PATH "${SOURCE}" PATH)
      file(RELATIVE_PATH SOURCE_PATH_REL ${CMAKE_CURRENT_SOURCE_DIR}/qml "${SOURCE_PATH}")
      string(REPLACE "/" "\\" GROUP_PATH "${SOURCE_PATH_REL}")
      source_group("Qml\\${GROUP_PATH}" FILES "${SOURCE}")
  endforeach()

  # Add qml to the qtquick compiler
  qtquick_compiler_add_resources(STRINGIFY_QML_RES ${CMAKE_CURRENT_SOURCE_DIR}/qml/Stringify.qrc)

  # Trick to rerun cmake each time Stringify.qrc is updated
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/qml/Stringify.qrc
    ${CMAKE_CURRENT_BINARY_DIR}/Stringify.qrc.junk
  )

  # Dont Run Moc on cpp file generated from qml
  foreach(STRINGIFY_CURRENT_QML_FILE ${STRINGIFY_QML_RES})
      set_property(SOURCE ${STRINGIFY_CURRENT_QML_FILE} PROPERTY SKIP_AUTOMOC ON)
      source_group("Qml\\QtQuickCompiler Files" FILES ${STRINGIFY_CURRENT_QML_FILE})
  endforeach()

endif()

set(STRINGIFY_SRCS_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(STRINGIFY_INCS_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(STRINGIFY_PRIVATE_INCS_FOLDER ${STRINGIFY_INCS_FOLDER}/Stringify)

# STRINGIFY SOURCES
set(STRINGIFY_UTILS_SRCS
    ${STRINGIFY_SRCS_FOLDER}/Utils.cpp
    ${STRINGIFY_SRCS_FOLDER}/Version.cpp
    ${STRINGIFY_SRCS_FOLDER}/Logger.cpp
)

set(STRINGIFY_API_SRCS
    ${STRINGIFY_SRCS_FOLDER}/VersionRegex.cpp
    ${STRINGIFY_SRCS_FOLDER}/Network.cpp
)

set(STRINGIFY_SRCS ${STRINGIFY_UTILS_SRCS}
    ${STRINGIFY_API_SRCS}
    ${STRINGIFY_QML_RES}
    ${STRINGIFY_QML_SRCS}
)

set(STRINGIFY_UTILS_INCS
    ${STRINGIFY_PRIVATE_INCS_FOLDER}/Stringify.hpp
    ${STRINGIFY_PRIVATE_INCS_FOLDER}/Export.hpp
    ${STRINGIFY_PRIVATE_INCS_FOLDER}/Utils.hpp
    ${STRINGIFY_PRIVATE_INCS_FOLDER}/Version.hpp
    ${STRINGIFY_PRIVATE_INCS_FOLDER}/Logger.hpp
)

set(STRINGIFY_API_INCS
    ${STRINGIFY_PRIVATE_INCS_FOLDER}/VersionRegex.hpp
    ${STRINGIFY_PRIVATE_INCS_FOLDER}/Network.hpp
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

target_compile_features(${STRINGIFY_TARGET} PUBLIC cxx_std_11)

# Set include directory
target_include_directories(${STRINGIFY_TARGET} PUBLIC $<BUILD_INTERFACE:${STRINGIFY_INCS_FOLDER}> $<INSTALL_INTERFACE:${STRINGIFY_INSTALL_PREFIX}>)

# Link libraries
if(STRINGIFY_ENABLE_PCH AND COMMAND target_precompile_headers)
  target_precompile_headers(${STRINGIFY_TARGET} PRIVATE include/Stringify/Pch/Pch.hpp)
endif()
target_link_libraries(${STRINGIFY_TARGET} PUBLIC spdlog Qt::Core Qt::Qml)
set_target_properties(${STRINGIFY_TARGET} PROPERTIES AUTOMOC TRUE)

if(STRINGIFY_ENABLE_QML)
  target_link_libraries(${STRINGIFY_TARGET} PUBLIC Qt::Gui Qt::Quick)
  set_target_properties(${STRINGIFY_TARGET} PROPERTIES AUTORCC TRUE)
  target_compile_definitions(${STRINGIFY_TARGET} PRIVATE -DSTRINGIFY_ENABLE_QML)
endif()

set_target_properties(${STRINGIFY_TARGET} PROPERTIES FOLDER ${STRINGIFY_FOLDER_PREFIX})

# Version
target_compile_definitions(${STRINGIFY_TARGET} PRIVATE -DSTRINGIFY_VERSION_MAJOR=${STRINGIFY_VERSION_MAJOR})
target_compile_definitions(${STRINGIFY_TARGET} PRIVATE -DSTRINGIFY_VERSION_MINOR=${STRINGIFY_VERSION_MINOR})
target_compile_definitions(${STRINGIFY_TARGET} PRIVATE -DSTRINGIFY_VERSION_PATCH=${STRINGIFY_VERSION_PATCH})
target_compile_definitions(${STRINGIFY_TARGET} PRIVATE -DSTRINGIFY_VERSION_TAG=${STRINGIFY_VERSION_TAG})
target_compile_definitions(${STRINGIFY_TARGET} PRIVATE -DSTRINGIFY_VERSION_TAG_HEX=${STRINGIFY_VERSION_TAG_HEX})

# ┌──────────────────────────────────────────────────────────────────┐
# │                           TESTS                                  │
# └──────────────────────────────────────────────────────────────────┘

if(STRINGIFY_ENABLE_TESTS)
    include(cmake/FetchGTest.cmake)
    enable_testing()
    add_subdirectory(tests)
endif()
