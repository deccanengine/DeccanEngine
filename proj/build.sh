mkdir bin
gcc -g -o bin/test ../sandbox/main.c ../sandbox/player.c -I../include/ \
    ../src/Core/Input.c ../src/Core/Asset.c \
    ../src/Physics/Collision.c ../src/Core/ECSystem.c ../src/Core/Object.c ../src/Core/Camera.c ../src/Core/Core.c \
    ../src/Core/Scene.c ../src/Renderer/Draw.c ../src/Renderer/Texture.c ../src/Renderer/Font.c \
    ../src/Renderer/Renderer.c ../src/Utils/Timer.c ../src/Utils/Message.c -I/usr/include/SDL2 \
    -D_REENTRANT -DDECCAN_REPORTS_ENABLED -DDECCAN_RENDERER_SDL -lSDL2_ttf -lSDL2_image -lSDL2 -lm
./bin/test