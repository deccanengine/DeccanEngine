mkdir bin
gcc -g -o bin/test ../main.c ../src/input.c ../src/asset.c ../src/core.c ../src/renderer.c ../src/utils/timer.c -I/usr/include/SDL2 -D_REENTRANT -lSDL2_ttf -lSDL2_image -lSDL2 
./bin/test