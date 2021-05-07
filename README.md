# Deccan Engine
![Deccan Engine](/resources/deccan-logo.svg?raw=true)

[![License](https://img.shields.io/github/license/deccanengine/deccanengine?color=00e500)](LICENSE.md)
[![Discord](https://img.shields.io/discord/681837246567022609?label=discord)](https://discord.gg/bNwnxwn)
[![Twitter](https://img.shields.io/twitter/follow/iddev5?color=0080ff&label=twitter&style=plastic)](https://twitter.com/iddev5)
[![Wiki](https://img.shields.io/badge/github-wiki-ff7000)](https://github.com/deccanengine/deccanengine/wiki)

Deccan Engine is an Open-Source Cross-Platform 2D Game Engine written in C11. Powered by SDL2.
- Written in pure C11 with a simple API
- ImGui enabled for sandbox and editor (*upcoming!*)
- Entity Component System using [flecs](https://github.com/sandermertens/flecs)
- OpenGL based renderer using state-independent [sokol-gfx](https://github.com/floooh/sokol)
- Extendable and clean design with least amount of cross-wirings

## Status
Platform | Status
---------|--------------
Linux    | [![Linux](https://github.com/deccanengine/DeccanEngine/workflows/Linux%20Build/badge.svg)](https://github.com/deccanengine/deccanengine/actions)
MacOS    | [![MacOS](https://github.com/deccanengine/deccanengine/workflows/MacOS%20Build/badge.svg)](https://github.com/deccanengine/deccanengine/actions)
Windows  | [![Windows](https://github.com/deccanengine/DeccanEngine/workflows/Windows%20Build/badge.svg)](https://github.com/deccanengine/deccanengine/actions)


## Getting Started
The [wiki](https://github.com/deccanengine/deccanengine/wiki) has detailed instructions on getting the source, configuring the environment and compiling the engine.  
Currently not much is available in terms of demo/example as the project is in heavy progress, however you can check out ``src/sandbox`` which is automatically built when the engine is built.

## License
This software is licensed under the terms of MIT License (See [LICENSE.md](LICENSE.md)).  
Copyright 2020 Ayush Bardhan Tripathy.
