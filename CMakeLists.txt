####################################################
# Deccan Engine
####################################################
cmake_minimum_required(VERSION 3.16)

project(DeccanEngine 
    VERSION 0.1
    LANGUAGES C CXX
)

set(SDL_INCLUDE_DIR "depends/SDL/include")
set(TTF_INCLUDE_DIR "depends/SDL_ttf")

add_subdirectory(depends/SDL)
add_subdirectory(depends/SDL_ttf)
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
    "src"
    "depends/glad/include/"
    ${SDL_INCLUDE_DIR}
    ${TTF_INCLUDE_DIR}
)

target_link_libraries(deccancore PUBLIC deimgui SDL2 SDL2_ttf)

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

target_link_libraries(demo PUBLIC deccancore)
