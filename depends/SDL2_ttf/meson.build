sdl_ttf_dep = dependency('SDL2_ttf', required: false)
if not sdl_ttf_dep.found()
    message('Custom SDL2_ttf dependency used')
    sdl_ttf_dep = declare_dependency(
        dependencies: CC.find_library('SDL2_ttf', dirs: meson.current_source_dir() + '/lib'),
        include_directories: include_directories('include')
    )
endif

deps += sdl_ttf_dep
