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
extra_compile_args=["-O3"]

with open('./src/streebog/auto/Makefile') as f:
    for l in f:
        if l.startswith("CFLAGS+="):
            extra_compile_args.append( l.strip()[8:] )

define_macros = [('_FILE_OFFSET_BITS', '64')]

module_ex = Extension('_pystribog',
                    define_macros = define_macros ,
                    extra_compile_args=extra_compile_args,
                    include_dirs = include_dirs,
                    libraries = libraries,
                    library_dirs = library_dirs,
                    sources = [
                        'src/streebog/gost3411-2012-core.c',
                        'src/module.c',
                        'src/hash.c' 
                     ])

                                       	
setup (name = 'PyStribog',
       version = '0.1',
       description = 'GOST cryptography stribog hash 256/512 functions',
       ext_modules = [module_ex])