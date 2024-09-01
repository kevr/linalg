project('linalg', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++23'])
linalg_incdir = include_directories('src')
linalg_dep = declare_dependency(
  include_directories : [linalg_incdir])
subdir('src')
