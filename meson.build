project('deccan-engine', ['c', 'cpp'], license: 'mit')

cc = meson.get_compiler('c')
m_dep  = cc.find_library('m')
dl_dep = cc.find_library('dl')

ig_src = [
    'depends/deimgui/cimgui.cpp',
    'depends/deimgui/imgui.cpp',
    'depends/deimgui/imgui_draw.cpp',
    'depends/deimgui/imgui_demo.cpp',
    'depends/deimgui/imgui_tables.cpp',
    'depends/deimgui/imgui_widgets.cpp',
    'depends/deimgui/imgui_impl_sdl.cpp'
]

ig_lib = static_library('imgui', ig_src,
    dependencies: dependency('SDL2'),
)

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
    'corelib/Core/SDLHelper.c',
    'corelib/Core/Asset/AssetManager.c',
    'corelib/Core/Input/Input.c',
    'corelib/Core/Module/Module.c',
    'corelib/Core/FileSys.c',
    'corelib/Core/Timer.c',
    'corelib/Core/Variable.c',
    'corelib/Core/Array.c',
    'corelib/Core/Handle.c',
    'corelib/Core/String.c',
    'corelib/Core/Utils.c',

    'corelib/Modules/Physics/Collision.c',
    'corelib/Modules/Imgui/Imgui.c',

    'corelib/Renderer/GenericPipeline.c',
    'corelib/Renderer/PrimitiveGeometry.c',
    'corelib/Renderer/Renderer.c',
    'corelib/Renderer/Texture.c',
    
    'corelib/Scene/Object.c',
    'corelib/Scene/Scene.c',
    
    'corelib/World/Camera.c',
    'corelib/World/Flecs.c',
    'corelib/World/Components.c',
    'corelib/World/Components/Collider.c',
    'corelib/World/Components/Transform.c',
    'corelib/World/Components/Drawable.c',
    'corelib/World/Components/DrawableGeometry.c',

    'corelib/Main/Main.c',
    'corelib/Main/Sources.c',
]

de_lib = shared_library('deccancore', src,
    name_prefix: '',
    dependencies: deps,
    include_directories: dep_incdir,
    link_with: ig_lib,
    c_args: [
        '-D_REENTRANT',
        '-DLOG_USE_COLOR',
        '-DDE_DEBUG',
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
    link_with: [de_lib, ig_lib],
    dependencies: deps,
)
