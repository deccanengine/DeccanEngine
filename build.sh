mkdir bin
gcc -o bin/test main.c core.c renderer.c timer.c -I/usr/include/SDL2 -D_REENTRANT -lSDL2_ttf -lSDL2 
./bin/test