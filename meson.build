project('deccan-engine', 'c', license: 'mit')

cc = meson.get_compiler('c')
m_dep = cc.find_library('m')

dep_incdir = include_directories('proj')
deps = [dependency('SDL2'), dependency('SDL2_ttf'), m_dep]

src = [
    'corelib/Core/Asset.c',
    'corelib/Core/Core.c',
    'corelib/Core/Input/Input.c',
    'corelib/Core/Memory.c',
    'corelib/Core/Timer.c',
    'corelib/Core/Variable.c',

    'corelib/Asset/Importer.c',
    'corelib/Asset/FontAsset.c',
    'corelib/Asset/SpriteAsset.c',

    'corelib/Modules/Physics/Collision.c',

    'corelib/Renderer/Camera.c',
    'corelib/Renderer/Primitives.c',
    'corelib/Renderer/Renderer.c',
    'corelib/Renderer/TextRendering.c',
    'corelib/Renderer/Texture.c',

    'corelib/Scene/Flecs.c',
    'corelib/Scene/Object.c',
    'corelib/Scene/Scene.c',
    'corelib/Scene/Components.c',
    'corelib/Scene/Components/Collider.c',
    'corelib/Scene/Components/State2D.c',

    'corelib/Main/Main.c',

    'sandbox/main.c',
    'sandbox/player.c'
]

executable('demo', src,
    dependencies: deps,
    include_directories: dep_incdir,
    c_args: [
        '-D_REENTRANT',
        '-DLOG_USE_COLOR',
        '-DDE_DEBUG',
        '-DDECCAN_RENDERER_SDL'
    ]
)
