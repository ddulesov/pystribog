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

extra_compile_args=[]
extra_link_args=[]

if sys.platform == "linux" or sys.platform == "linux2":
    extra_compile_args.append("-msse4.1")
elif sys.platform == "cygwin":
    extra_compile_args.append("-msse4.1")
    extra_link_args.append("-Wl,--enable-runtime-pseudo-reloc")
elif sys.platform == "darwin":
    extra_link_args.append("-shared-libgcc")


define_macros = [('_FILE_OFFSET_BITS', '64'),('__GOST3411_HAS_SSE41__','1')]

module_ex = Extension('_pystribog',
                    define_macros = define_macros ,
                    extra_compile_args=extra_compile_args,
                    extra_link_args = extra_link_args,
                    sources = [
                        'src/gost3411-2012-core.c',
                        'src/module.c',
                        'src/hash.c' 
                    ])

                                       	
setup (name = 'pyStribog',
       version = '0.3',
       description = 'GOST 34.11-2012 cryptography (streebog) hash 256/512 function',
       author = "Dmitry Dulesov",
       author_email = "dmitry.dulesov@gmail.com",
       url = "https://github.com/ddulesov/pystribog",

       ext_modules = [ module_ex ])