# pystribog
Streebog hash (GOST R 34.11-2012 )  python library 

[![Build Status](https://travis-ci.org/ddulesov/pystribog.svg?branch=master)](https://travis-ci.org/ddulesov/pystribog)
[![Build Status](https://dev.azure.com/dmitrydulesov/dmitrydulesov/_apis/build/status/ddulesov.pystribog?branchName=master)](https://dev.azure.com/dmitrydulesov/dmitrydulesov/_build/latest?definitionId=1&branchName=master)

## Features
- python 3.x and python 2.7 support
- use fast C(sse4.1/sse2) streebog hash function implementation based on degtyarev  [library](https://github.com/adegtyarev/streebog.git)
- Linux ,  Windows (probably OSx but not tested) supported

## Requirements
- python 2.7 or python 3.8+ 
- gcc 7.x+ or  msvc compatible with used Python version 
- sse4.1 capable CPU 

## Building and Installation
```console
#run in development host
#sudo apt-get install -y build-essential python3 python3-dev
git clone --depth 1  https://github.com/ddulesov/pystribog.git

cd pystribog
python3 setup.py build install

#run tests

python3 module_tests.py

#optionaly create dist
python3 setup.py bdist
```

## Quickstart
```python
import _pystribog
import binascii
h = _pystribog.StribogHash( _pystribog.Hash512 )
h.update(b"12345")
res = h.digest()
print( "hex512(b'12345')=", binascii.hexlify(res) ) 
```
