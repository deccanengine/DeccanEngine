gcc -Wall -Wextra -Wno-unused-value -Wno-unused-parameter -Wno-implicit-fallthrough -g -o bin\test ..\sandbox\main.c ..\sandbox\player.c ..\corelib\Asset\*.c ..\corelib\Behaviour\Physics\*.c ..\corelib\Input\*.c ..\corelib\Renderer\*.c ..\corelib\Scene\*.c ..\corelib\Scene\Components\*.c ..\corelib\*.c -D_REENTRANT -DDECCAN_REPORTS_ENABLED -DDECCAN_RENDERER_SDL -lSDL2_ttf -lmingw32 -lSDL2main -lSDL2 -lgdi32 -lwinmm -lm
cd bin 
test
cd ..