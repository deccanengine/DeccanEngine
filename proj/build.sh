#!/bin/sh
gcc -Wall -Wextra -Wno-unused-value -Wno-unused-parameter -Wno-implicit-fallthrough -g -o \
    bin/test ../sandbox/*.c \
    ../corelib/Core/*.c \
    ../corelib/Asset/*.c \
    ../corelib/Modules/Physics/*.c \
    ../corelib/Core/Input/*.c \
    ../corelib/Renderer/*.c \
    ../corelib/Scene/*.c \
    ../corelib/Scene/Components/*.c \
    ../corelib/*.c \
    ../depends/flecs/flecs.c ../depends/log.c/src/*.c \
    -D_REENTRANT -DLOG_USE_COLOR -DDE_DEBUG -DDECCAN_RENDERER_SDL \
    -lSDL2_ttf -lSDL2 -lm
cd bin
./test
