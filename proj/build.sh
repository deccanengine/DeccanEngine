mkdir bin
gcc -g -o bin/test ../main.c ../player.c ../src/core/input.c ../src/core/asset.c ../src/physics/collision.c ../src/core/object.c ../src/core/core.c ../src/core/scene.c ../src/renderer/renderer.c ../src/utils/timer.c -I/usr/include/SDL2 -D_REENTRANT -lSDL2_ttf -lSDL2_image -lSDL2 
./bin/test