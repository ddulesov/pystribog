# if setuptools is detected, use it to add support for eggs
try:
    from setuptools import setup, Extension
except:
    from distutils.core import setup
    from distutils.extension import Extension

from distutils.util import get_platform
from distutils.ccompiler import get_default_compiler

import sys
import os


include_dirs = ['./src/streebog']
library_dirs = []
libraries = []

'''
import cpuinfo
cpu_flags = cpuinfo.get_cpu_info()['flags']
if 'sse41' in cpu_flags:
    define_macros = [('__GOST3411_HAS_SSE41__', '1')]
elif 'sse2' in cpu_flags:
    define_macros = [('__GOST3411_HAS_SSE2__', '1')]
elif 'mmx' in cpu_flags:
    define_macros = [('__GOST3411_HAS_MMX__', '1')]
else:
    define_macros = []
    
'''
#define_macros = [('__GOST3411_HAS_SSE2__', '1')]

module_ex = Extension('_pystribog',
                    #define_macros = define_macros ,
                    include_dirs = include_dirs,
                    libraries = libraries,
                    library_dirs = library_dirs,
                    sources = [
                        'src/streebog/gost3411-2012.c',
                        'src/streebog/gost3411-2012-core.c',
                        'src/module.c',
                        'src/hash.c' 
                     ])

                                       	
setup (name = 'PyStribog',
       version = '0.1',
       description = 'GOST cryptography stribog hash 256/512 functions',
       ext_modules = [module_ex])