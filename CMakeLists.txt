cmake_minimum_required(VERSION 3.14)

project(AoC VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOLUTION_SOURCES "src/solutions/*.cpp")
add_executable(aoc src/main.cpp ${SOLUTION_SOURCES})
target_compile_definitions(aoc PRIVATE PROJECT_ROOT="${CMAKE_SOURCE_DIR}")

install(TARGETS aoc DESTINATION bin)

include(FetchContent)

# FTXUI
FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
  GIT_TAG v6.1.9)

FetchContent_MakeAvailable(ftxui)

target_link_libraries(
  aoc
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component)
