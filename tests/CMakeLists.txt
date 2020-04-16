#
#   Stringify CTest script
#
#   Copyright Olivier Le Doeuff 2019
#


set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set_target_properties(gtest gtest_main gmock gmock_main
    PROPERTIES FOLDER Dependencies/gtest)

set(STRINGIFY_TEST_TARGET ${STRINGIFY_TESTS_PREFIX}Tests)

set(STRINGIFY_TEST_TARGET_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(STRINGIFY_TEST_SRCS  ${STRINGIFY_TEST_TARGET_DIR}/Tests.cpp
    )

message(STATUS "Add Test: ${STRINGIFY_TEST_TARGET}")

# Create the executable
add_executable(${STRINGIFY_TEST_TARGET} ${STRINGIFY_TEST_SRCS})
set_target_properties(${STRINGIFY_TEST_TARGET} PROPERTIES AUTOMOC TRUE)
target_link_libraries(${STRINGIFY_TEST_TARGET} ${STRINGIFY_TARGET})
target_link_libraries(${STRINGIFY_TEST_TARGET} gtest gmock)
set_target_properties(${STRINGIFY_TEST_TARGET} PROPERTIES FOLDER ${STRINGIFY_FOLDER_PREFIX}/Tests)

# Register the test
add_test(NAME ${STRINGIFY_TEST_TARGET} COMMAND ${STRINGIFY_TEST_TARGET})