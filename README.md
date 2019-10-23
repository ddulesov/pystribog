# pystribog
Stribog (GOST R 34.11-2012 ) hash python library 

[![Build Status](https://travis-ci.org/ddulesov/pystribog.svg?branch=master)](https://travis-ci.org/ddulesov/pystribog)

## Features
- python 3.x and python 2.7 support
- use fast C(sse4.1/sse2) degtyarev  [Stribog implementaion](https://github.com/adegtyarev/streebog.git)
- Linux ,  Windows supported


## Requirements
- python 2.7 or python 3.6+ 
- gcc 7.x+, msvc

## Building and Installation
```console
#development host
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
