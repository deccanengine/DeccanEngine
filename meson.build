####################################################
# Deccan Engine
####################################################

project('deccan-engine', ['c', 'cpp'], license: 'mit')

CC = meson.get_compiler('c')

src = []        # Sources of deccancore.so
edit_src = []   # Sources of editor
demo_src = []   # Sources of demo (sandbox application)

####################################################
# Dependencies
####################################################

m_dep  = CC.find_library('m', required: false)   # libm
dl_dep = CC.find_library('dl', required: false)  # libdl

deps_incdir = [
    'depends/glad/include',
    'depends/zpl/code',
    'depends/log.c/src',
    'depends/cglm/include',
    'depends/flecs',
    'depends/',
]

sdl2_dep = dependency('SDL2', required: false)
sdl2_ttf_dep = dependency('SDL2_ttf', required: false) 

if not sdl2_dep.found()
    sdl2_warp = subproject('sdl2')
    sdl2_dep = sdl2_warp.get_variable('sdl2_dep')
endif

if not sdl2_ttf_dep.found()
    sdl2_ttf_wrap = subproject('sdl2_ttf')
    sdl2_ttf_dep = sdl2_ttf_wrap.get_variable('sdl2_ttf_dep')
endif

deps = [
    sdl2_dep, 
    sdl2_ttf_dep, 
    m_dep,
    dl_dep
]

####################################################
# Sources
####################################################

subdir('depends')
subdir('src')

####################################################
# Deccan Core
####################################################

de_lib = shared_library('deccancore', src,
    name_prefix: '',
    dependencies: deps,
    include_directories: deps_incdir,
    link_with: ig_lib,
    c_args: [
        '-D_REENTRANT',
        '-DLOG_USE_COLOR',
        '-DDE_DEBUG',
    ],
    install: true,
)

de_dep = declare_dependency(
    link_with: de_lib,
    include_directories: '.'
)

####################################################
# Editor
####################################################

executable('editor', edit_src,
    link_with: [de_lib, ig_lib],
    dependencies: deps,
    include_directories: [
        include_directories('src/'), 
        deps_incdir 
    ]
)

####################################################
# Demo
####################################################

executable('demo', demo_src, 
    link_with: [de_lib, ig_lib],
    dependencies: deps,
    include_directories: [ 
        include_directories('src/'), 
        deps_incdir 
    ]
)
