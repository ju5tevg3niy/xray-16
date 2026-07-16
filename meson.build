project(
    'openxray',
    'c',
    'cpp',
    version: '0.1',
    meson_version: '>= 1.3.0',
    default_options: [
        'warning_level=0',
        'cpp_std=c++17',
    ],
)

subproject('tracy')

jpeg = dependency('libjpeg')
lzo = dependency('lzo2')
sdl = dependency('sdl2')
tracy = dependency('tracy')

buildtype = get_option('buildtype')

if buildtype == 'debug'
    add_project_arguments('-DDEBUG', language: ['c', 'cpp'])
elif buildtype == 'release'
    add_project_arguments('-DNDEBUG', language: ['c', 'cpp'])
endif

subdir('src')
