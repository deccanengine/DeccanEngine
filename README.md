# Deccan Engine
![Deccan Engine](/resources/deccan-logo.svg?raw=true)

[![GitHub](https://img.shields.io/github/license/iddev5/DeccanEngine)](LICENSE.md)
[![Discord](https://img.shields.io/discord/681837246567022609?label=discord)](https://discord.gg/bNwnxwn)

Deccan Engine is an Open-Source Cross-Platform 2D Game Engine written in C11. Powered by SDL2.
- Lightweight and simple framework design
- Basic scene manager
- Versatile and easy-to-use Entity Component System
- Input system supporting keyboard and mouse states and events
- Asset management system
- Flexible helper structs and functions, such as Vectors, Timers etc.

## Getting Started
Clone the repository using git:
```
git clone --recursive https://www.github.com/iddev5/DeccanEngine
```

Recursively getting the repository automatically downloads the submodule dependencies.
The external dependencies are SDL2 and SDL2_ttf only which has to be installed separately from your vendor.

Then build using:
```
meson builddir
ninja -C builddir
```

For non-POSIX Windows, CMake is needed for handling dependencies as it cannot properly use pkg-config.

## Example
Currently not much is available in terms of demo/example as the project is in heavy progress, however you can check out ``sandbox`` which is automatically built when the engine is built.

## License
This software is licensed under the terms of MIT License (See [LICENSE.md](LICENSE.md)).  
Copyright 2020 Ayush Bardhan Tripathy.
