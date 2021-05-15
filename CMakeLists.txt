####################################################
# Deccan Engine
####################################################
cmake_minimum_required(VERSION 3.16)

project(DeccanEngine 
    VERSION 0.1
    LANGUAGES C CXX
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/proj/cmake")

if (WIN32)
    set(SDL2_PATH "depends/SDL")
    set(SDL2_TTF_PATH "depends/SDL_ttf")
endif (WIN32)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_subdirectory(depends/deimgui)

####################################################
# Deccan Core
####################################################

file(GLOB_RECURSE de_sources "src/corelib/*.c")
file(GLOB_RECURSE de_headers "src/corelib/*.h")

add_library(deccancore 
    SHARED
    ${de_sources}
    ${de_headers}
)

set_target_properties(deccancore PROPERTIES LINKER_LANGUAGE C)

target_include_directories(deccancore PUBLIC
    "."
    "depends/glad/include"
    "depends/zpl/code"
    "depends/log.c/src"
    "depends/cglm/include"
    "depends/flecs"
    "depends/"
    ${SDL2_INCLUDE_DIR}
    ${SDL2_TTF_INCLUDE_DIR}
)

target_link_libraries(deccancore PUBLIC deimgui ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARIES})

####################################################
# Demo
####################################################

file(GLOB demo_sources "src/sandbox/*.c")
file(GLOB demo_headers "src/sandbox/*.h")

add_executable(demo
    ${demo_sources}
    ${demo_headers}
)

set_target_properties(demo PROPERTIES LINKER_LANGUAGE C)

target_include_directories(demo PUBLIC "src")
target_link_libraries(demo PUBLIC deccancore)
