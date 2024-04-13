project(
  '2048',
  'cpp',
  version: '2.0.0',
  meson_version: '>= 1.2.0',
  default_options: [
    'warning_level=3',
    'cpp_std=c++17',
    'default_library=static',
  ],
)

add_global_arguments('-Wno-unused', language: 'cpp')

incdir = include_directories('include')

sdl2_dep = dependency('sdl2')
sdl2_ttf_dep = dependency('sdl2_ttf')
sdl2_gfx_dep = dependency('sdl2_gfx')

executable(
  '2048',
  sources: [
    'src/main.cpp',
    'src/app/app.cpp',
    'src/app/app_run.cpp',
    'src/app/app_init.cpp',
    'src/app/app_update.cpp',
    'src/app/app_handle_event.cpp',
    'src/app/app_render.cpp',
    'src/app/app_clean.cpp',
    'src/canvas.cpp',
    'src/game_object.cpp',
  ],
  include_directories: incdir,
  dependencies: [sdl2_dep, sdl2_ttf_dep, sdl2_gfx_dep],
  install: true,
  win_subsystem: 'windows',
)
