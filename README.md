![Deccan Engine](/resources/deccan-light.png?raw=true)

# Deccan Game Engine
Cross-platform 2D Game Engine written in C11. Powered by SDL2.  

![GitHub](https://img.shields.io/github/license/iddev5/DeccanEngine)
![Discord](https://img.shields.io/discord/681837246567022609?label=discord)  

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

For Windows, download and install MinGW and compile with main.c example. You can refer to build.sh for linking info.
Make sure that the path of gcc is added to %PATH%

## License
This software is license under the terms of MIT License(See LICENSE.md)  
Copyright 2020 Ayush Bardhan Tripathy
