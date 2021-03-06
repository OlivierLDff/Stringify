#
#   Stringify CTest script
#
#   Copyright Olivier Le Doeuff 2019
#

set(STRINGIFY_TEST_TARGET ${STRINGIFY_TESTS_PREFIX}Tests)

set(STRINGIFY_TEST_TARGET_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(STRINGIFY_TEST_SRCS
  ${STRINGIFY_TEST_TARGET_DIR}/Tests.cpp
  ${STRINGIFY_TEST_TARGET_DIR}/NetworkTests.cpp
  )

message(STATUS "Add Test: ${STRINGIFY_TEST_TARGET}")

# Create the executable
add_executable(${STRINGIFY_TEST_TARGET} ${STRINGIFY_TEST_SRCS})
set_target_properties(${STRINGIFY_TEST_TARGET} PROPERTIES AUTOMOC TRUE)
target_link_libraries(${STRINGIFY_TEST_TARGET} ${STRINGIFY_TARGET})
target_link_libraries(${STRINGIFY_TEST_TARGET} gtest gmock)
set_target_properties(${STRINGIFY_TEST_TARGET} PROPERTIES FOLDER ${STRINGIFY_FOLDER_PREFIX}/Tests)

if(STRINGIFY_ENABLE_PCH AND COMMAND target_precompile_headers)
  target_precompile_headers(${STRINGIFY_TEST_TARGET} PRIVATE ../include/Stringify/Pch/Pch.hpp)
endif()

# Register the test
add_test(NAME ${STRINGIFY_TEST_TARGET} COMMAND ${STRINGIFY_TEST_TARGET})