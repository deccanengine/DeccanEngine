sdl_dep = dependency('SDL2', required: false)
if not sdl_dep.found()
    message('Custom SDL2 dependency used')
    sdl_dep = declare_dependency(
        dependencies: CC.find_library('SDL2', dirs: meson.current_source_dir() + '/lib'),
        include_directories: include_directories('include')
    )
endif

deps += sdl_dep
