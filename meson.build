####################################################
# Deccan Engine
####################################################

project('deccan-engine', ['c', 'cpp'], license: 'mit')

CC = meson.get_compiler('c')

src = []        # Sources of deccancore.so
demo_src = []   # Sources of demo (sandbox application)

####################################################
# Dependencies
####################################################

m_dep  = CC.find_library('m')   # libm
dl_dep = CC.find_library('dl')  # libdl

deps_incdir = [
    include_directories('depends/glad/include')
]

deps = [
    m_dep,
    dl_dep
]

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
