@echo off

mkdir temp
nuget install sdl2.nuget -ExcludeVersion -NonInteractive -OutputDirectory temp\
nuget install sdl2_ttf.nuget -ExcludeVersion -NonInteractive -OutputDirectory temp\

robocopy temp\sdl2.nuget\build\native\include\ depends\SDL
robocopy temp\sdl2_ttf.nuget\build\native\include\ depends\SDL_ttf

robocopy temp\sdl2.nuget\build\native\lib\x64\dynamic\ depends\SDL
robocopy temp\sdl2_ttf.nuget\build\native\lib\x64\dynamic\ depends\SDL_ttf

robocopy temp\sdl2.nuget.redist\build\native\bin\x64\dynamic\ depends\SDL
robocopy temp\sdl2_ttf.nuget.redist\build\native\bin\x64\dynamic\ depends\SDL_ttf
