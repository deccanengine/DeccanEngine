# Deccan Game Engine
Cross-platform 2D Game Engine written in C11. Powered by SDL2.

## Features so far
- Lightweight and simple framework design
- Basic scene manager
- Input system supporting keyboard and mouse states and events
- Asset management system
- Flexible helper structs and functions, such as Vectors, Timers etc.

## Building
Clone the repository using git:
```git clone https://www.github.com/iddev5/DeccanEngine```

The dependencies are: SDL2, SDL2_image, SDL2_ttf and stb_ds.h(Included)

For Linux, run the build.sh Bash script which compiles the engine with main.c example file.

For Windows, download and install MinGW and use the command to compile with main.c example:
```gcc -g -o bin/test /main.c /src/core/input.c /src/core/asset.c /src/core/core.c /src/renderer/renderer.c /src/utils/timer.c -I/usr/include/SDL2 -D_REENTRANT -lSDL2_ttf -lSDL2_image -lSDL2 -lgdi32 -winmm
```
Make sure that the path of gcc is added to %PATH%

## License
This software is license under the terms of MIT License(See LICENSE.md)
Copyright 2020 Ayush Bardhan Tripathy