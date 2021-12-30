set(PROJECT_NAME raylib-life)

set(PROJECT_SOURCES src/main.cpp)
set(LIBRARY_SOURCES lib/Board.cpp)

# Add symbolic link to resources folder in build
# (from https://github.com/rafaeldelboni/raylib-cpp-bullet3)
add_custom_target(resources)
file(TO_NATIVE_PATH "${PROJECT_SOURCE_DIR}/life/resources" source)
file(TO_NATIVE_PATH "${PROJECT_BINARY_DIR}/life/resources" destination)
if (WIN32)
  add_custom_command(
    TARGET resources POST_BUILD
    COMMAND mklink /D ${destination} ${source}
    DEPENDS ${destination}
    COMMENT "symbolic link resources folder from ${source} => ${destination}"
    )
else()
  add_custom_command(
    TARGET resources POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination}
    DEPENDS ${destination}
    COMMENT "symbolic link resources folder from ${source} => ${destination}"
    )
endif()

include_directories(lib/)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
add_library(${PROJECT_NAME}_lib ${LIBRARY_SOURCES})

set(raylib_VERBOSE ON)

target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_NAME}_lib raylib raylib-cpp)
