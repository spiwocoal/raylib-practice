cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -Wextra -Wpedantic -Weffc++ -g -fdiagnostics-color=always)

project(spiwocoal-raylib-practice)

option(BUILD_SNAKE "Builds the snake game" ON)
option(BUILD_LIFE "Builds the life game" ON)

# raylib
find_package(raylib QUIET)
if (NOT raylib_FOUND)       # If raylib is not installed in our system
  include (FetchContent)    # We fetch it from its git repo in order to
  FetchContent_Declare(     # build our program
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5f2bc20191fecabc0bd50ed80a3d33d170ffd916
    )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
    set(BUILD_TESTING  OFF CACHE BOOL "" FORCE)
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

# raylib-cpp
find_package(raylib-cpp QUIET)
if (NOT raylib-cpp_FOUND)   # If raylib-cpp is not installed in our system
    include(FetchContent)   # We fetch it from its git repo in order to
    FetchContent_Declare(   # build our program
        raylib-cpp
        URL https://github.com/RobLoach/raylib-cpp/archive/master.tar.gz
    )
    FetchContent_GetProperties(raylib-cpp)
    if (NOT raylib-cpp_POPULATED) # Have we downloaded raylib-cpp yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib-cpp)
        set(BUILD_RAYLIB_CPP_EXAMPLES OFF CACHE BOOL "" FORCE)
        set(BUILD_TESTING             OFF CACHE BOOL "" FORCE)
        add_subdirectory(${raylib-cpp_SOURCE_DIR} ${raylib-cpp_BINARY_DIR})
    endif()
endif()

if (BUILD_SNAKE)
  add_subdirectory(snake)
endif()
if (BUILD_LIFE)
  add_subdirectory(life)
endif()
