# pystribog
Stribog (GOST R 34.11-2012 ) hash python library 

[![Build Status](https://travis-ci.com/ddulesov/pystribog.svg?branch=master)](https://travis-ci.com/ddulesov/pystribog) 

## Features
- python 3.x and python 2.7 support
- use fast C(sse4.1) Stribog [ degtyarev implementaion](https://github.com/adegtyarev/streebog.git)
- Linux , OSx supported

## Issues
- only PEM encoding CMS and certificate supported 

## Requirements
- python 2.7 or python 3.6+ 

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

h = _pystribog.StribogHash( _pystribog.Hash512 )
h.update(b"12345")
res = h.digest()
print( "hex512(b'12345')=", binascii.hexlify(res) ) 

```
