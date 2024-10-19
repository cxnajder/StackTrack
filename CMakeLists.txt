cmake_minimum_required(VERSION 3.10)
project(StackTrack VERSION 1.0)

option(TEST_LIB "Test the library" ON)

add_library(StackTrackLib SHARED StackTrack.cpp)
target_include_directories(StackTrackLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if (TEST_LIB)
    add_executable(StackTracLib.test StackTrack.test.cpp)

target_include_directories (StackTracLib.test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries (StackTracLib.test PUBLIC StackTrackLib)

endif()