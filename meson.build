project('alif-key', 'cpp', version: '1.0', default_options: ['cpp_std=c++20', 'optimization=3'])

core_src = [
  'src/AlifKeyCore/ArabicModel.cpp',
  'src/AlifKeyCore/ArabicModel.hpp'
]

alifkey_src = [
  'src/alif-key.cpp'
]

cppc = meson.get_compiler('cpp')

executable('alif-key',
           core_src + alifkey_src,
)

