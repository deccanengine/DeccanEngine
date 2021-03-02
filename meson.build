project('deccan-engine', 'c', license: 'mit')

cc = meson.get_compiler('c')
m_dep  = cc.find_library('m')
dl_dep = cc.find_library('dl')

dep_incdir = [
    include_directories('proj'),
    include_directories('depends/sx/include'),
    include_directories('depends/glad/include')
]
deps = [
    dependency('SDL2'), 
    dependency('SDL2_ttf'), 
    m_dep,
    dl_dep
]

src = [
    'corelib/Core/Core.c',
    'corelib/Core/Asset/AssetManager.c',
    'corelib/Core/Input/Input.c',
    'corelib/Core/FileSys.c',
    'corelib/Core/Timer.c',
    'corelib/Core/Variable.c',
    'corelib/Core/String.c',
    'corelib/Core/Utils.c',

    'corelib/Modules/Physics/Collision.c',

    'corelib/Renderer/Camera.c',
    'corelib/Renderer/GenericPipeline.c',
    'corelib/Renderer/PrimitiveGeometry.c',
    'corelib/Renderer/Renderer.c',
    'corelib/Renderer/Texture.c',

    'corelib/Scene/Flecs.c',
    'corelib/Scene/Object.c',
    'corelib/Scene/Scene.c',
    'corelib/Scene/Components.c',
    'corelib/Scene/Components/Collider.c',
    'corelib/Scene/Components/State2D.c',

    'corelib/Main/Main.c',
    'corelib/Main/Sources.c',
]

de_lib = shared_library('deccancore', src,
    name_prefix: '',
    dependencies: deps,
    include_directories: dep_incdir,
    c_args: [
        '-D_REENTRANT',
        '-DLOG_USE_COLOR',
        '-DDE_DEBUG',
#        '-DDE_RENDERER_SDL'
    ]
)

de_dep = declare_dependency(
    link_with: de_lib,
    include_directories: 'corelib'
)

demo_src = [
    'sandbox/main.c',
    'sandbox/player.c',
    'sandbox/Texture.c'
]

executable('demo', demo_src, 
    link_with: de_lib, 
    dependencies: deps
)
