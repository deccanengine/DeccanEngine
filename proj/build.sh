mkdir bin
gcc -g -o bin/test ../main.c ../src/core/input.c ../src/core/asset.c ../src/core/core.c ../src/renderer/renderer.c ../src/utils/timer.c -I/usr/include/SDL2 -D_REENTRANT -lSDL2_ttf -lSDL2_image -lSDL2 
./bin/test