####################################################
# Deccan Engine
####################################################
cmake_minimum_required(VERSION 3.16)

project(DeccanEngine
    VERSION 0.1
    LANGUAGES C CXX
)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/proj/cmake")

if (WIN32)
    set(SDL2_PATH "depends/SDL")
    # set(SDL2_TTF_PATH "depends/SDL_ttf")
endif (WIN32)

find_package(SDL2 REQUIRED)
# find_package(SDL2_ttf REQUIRED)

####################################################
# Core dependencies
####################################################

file(GLOB_RECURSE flecs_sources "depends/flecs/src/*.c")
file(GLOB_RECURSE flecs_headers "depends/flecs/include/*.h")

add_library(dep_flecs STATIC
    ${flecs_sources}
    ${flecs_headers}
)

target_include_directories(dep_flecs SYSTEM PUBLIC "depends/flecs/include")

file(GLOB_RECURSE glad_sources "depends/glad/src/*.c")
file(GLOB_RECURSE glad_headers "depends/glad/include/*.h")

add_library(dep_glad STATIC
    ${glad_sources}
    ${glad_headers}
)

target_include_directories(dep_glad SYSTEM PUBLIC "depends/glad/include")

file(GLOB_RECURSE cm2d_sources "depends/Chipmunk2D/src/*.c")
file(GLOB_RECURSE cm2d_headers "depends/Chipmunk2D/include/*.h")

add_library(dep_cm2d STATIC
    ${cm2d_sources}
    ${cm2d_headers}
)

target_include_directories(dep_cm2d SYSTEM PUBLIC "depends/Chipmunk2D/include")

####################################################
# Deccan Core
####################################################

file(GLOB_RECURSE de_sources "src/deccanengine/*.c")
file(GLOB_RECURSE de_headers "include/deccanengine/*.h")

add_library(deccanengine
    SHARED
    ${de_sources}
    ${de_headers}
)

if (WIN32)
    set_target_properties(deccanengine PROPERTIES
        LINKER_LANGUAGE C
        DEFINE_SYMBOL DE_LIBRARY_EXPORT
    )
else (WIN32)
    set_target_properties(deccanengine PROPERTIES LINKER_LANGUAGE C)
endif (WIN32)

target_include_directories(deccanengine SYSTEM PUBLIC
    "."
    "include/"
    "depends/zpl/code"
    "depends/log.c/src"
    "depends/cglm/include"
    "depends/"
    ${SDL2_INCLUDE_DIR}
    # ${SDL2_TTF_INCLUDE_DIR}
)

target_link_libraries(deccanengine PUBLIC m dep_flecs dep_glad dep_cm2d ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARIES})
target_compile_definitions(deccanengine PUBLIC _REENTRANT=1)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(deccanengine PUBLIC LOG_USE_COLOR=1 DE_DEBUG=1)
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")

if (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(deccanengine PRIVATE /W4)
else (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(deccanengine PRIVATE -Wall -Wextra -Wno-missing-field-initializers -pedantic)
endif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")

####################################################
# Editor
####################################################

# find_package(Vala REQUIRED)
# include(proj/cmake/ValaPrecompile.cmake)
#
# file(GLOB_RECURSE EDITOR_VALA_SRC "src/editor_vala/*.vala")
#
# vala_precompile(EDITOR_SRC sceneeditor
#     ${EDITOR_VALA_SRC}
#     PACKAGES gtk+-3.0
#     DIRECTORY "src/editor_vala"
# )
#
# find_package(PkgConfig REQUIRED)
# pkg_check_modules(GTK REQUIRED IMPORTED_TARGET gtk+-3.0)
#
# add_executable(sceneeditor ${EDITOR_SRC})
# target_link_libraries(sceneeditor PUBLIC PkgConfig::GTK)
#
# add_custom_command(TARGET sceneeditor POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#             ${CMAKE_SOURCE_DIR}/src/editor_vala/resources/
#             ${CMAKE_CURRENT_BINARY_DIR}/resources/
# )

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
target_link_libraries(demo PUBLIC deccanengine)

if (WIN32)
    target_compile_definitions(demo PUBLIC SDL_MAIN_HANDLED=1)
endif(WIN32)

####################################################
# Install
####################################################

install(TARGETS deccanengine DESTINATION "lib")
install(DIRECTORY "${CMAKE_SOURCE_DIR}/include/deccanengine" DESTINATION "include")
