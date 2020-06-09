mkdir bin
gcc -g -o bin/test ../sandbox/main.c ../sandbox/player.c \
    ../corelib/Asset/*.c \
    ../corelib/Behaviour/Physics/*.c \
    ../corelib/Input/*.c \
    ../corelib/Renderer/*.c \
    ../corelib/Scene/*.c \
    ../corelib/Scene/Components/*.c \
    ../corelib/*.c \
    -D_REENTRANT -DDECCAN_REPORTS_ENABLED -DDECCAN_RENDERER_SDL -lSDL2_ttf -lSDL2_image -lSDL2 -lm
./bin/test