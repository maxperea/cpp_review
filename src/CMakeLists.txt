project(BASE)

cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

FetchContent_MakeAvailable(googletest)

add_library(LIB lib.hpp lib.cpp)

add_executable(BASE main.cpp)
target_link_libraries(BASE LIB)


enable_testing()
add_executable(
  tests
  tests.cpp
)
target_link_libraries(
  tests
  gtest_main
  LIB
)

include(GoogleTest)
gtest_discover_tests(tests)

