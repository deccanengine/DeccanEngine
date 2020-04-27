mkdir bin
gcc -g -o bin/test ../main.c ../player.c ../src/deccan.c ../src/core/input.c ../src/core/asset.c ../src/physics/collision.c ../src/core/object.c ../src/renderer/camera.c ../src/core/core.c ../src/core/scene.c ../src/renderer/draw.c ../src/renderer/texture.c ../src/renderer/renderer.c ../src/utils/timer.c -I/usr/include/SDL2 -D_REENTRANT -lSDL2_ttf -lSDL2_image -lSDL2 -lm
./bin/test