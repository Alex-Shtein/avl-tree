cmake_minimum_required(VERSION 3.14)

project(mp_HW04)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_library(mp_HW04Lib SHARED ../Task4/src/main.cpp)

add_executable(mp_HW04Tests ../Task4.Tests/AVLTree.tests.cpp)

target_link_libraries(mp_HW04Tests mp_HW04Lib gtest gtest_main pthread)