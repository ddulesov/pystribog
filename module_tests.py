import unittest
import _pystribog
import binascii
from collections import defaultdict
import os
import re
import sys

PY3K = sys.version_info >= (3, 0)
if PY3K:
    def to_bytes(s):
        return bytes(s,'utf-8')
else:
    def to_bytes(s):
        return bytes(s)


M1=b"012345678901234567890123456789012345678901234567890123456789012"

def read_file(fname):
    with open(fname,"rb") as f:
        return f.read()

class TestModuleMethods(unittest.TestCase):
    
    def test_hash_512(self):
        h = _pystribog.StribogHash(512)
        h.update(M1)

        res = h.digest()
        
        E=b"1b54d01a4af5b9d5cc3d86d68d285462b19abc2475222f35c085122be4ba1ffa00ad30f8767b3a82384c6574f024c311e2a481332b08ef7f41797891c1646f48"

        self.assertEqual(binascii.hexlify(res), E )
        
        h.clear()
        h.update(M1)
        res = to_bytes(h.hexdigest())

        self.assertEqual(res, E )

        self.assertEqual( h.digest_size, 64 )

    def test_hash_256(self):
        h = _pystribog.StribogHash(256)
        h.update(M1)

        res = h.digest()
        
        E=b"9d151eefd8590b89daa6ba6cb74af9275dd051026bb149a452fd84e5e57b5500"

        self.assertEqual(binascii.hexlify(res), E )
        
        h.clear()
        h.update(M1)
        res = to_bytes(h.hexdigest())
        self.assertEqual(res, E )

        self.assertEqual( h.digest_size, 32 )
    
    def test_adegtyarev_lib(self):
        #load test data
        tdata = defaultdict(lambda:{"msg":None,"h256":None, "h512":None} )

        reM = re.compile("^M(\d+)$")
        reH = re.compile("^H(\d+)\.(\d+)$")

        parent = "./src/examples"
        for fname in os.listdir(parent):
            m = reM.match(fname)
            if m:
                id = m.group(1)
                tdata[id]["msg"] = read_file(os.path.join(parent,fname) )
                continue
            m = reH.match(fname)
            if m:
                id = m.group(1)
                dig = m.group(2)
                if dig=='256':
                    hash = "h256"
                elif dig=='512':
                    hash = "h512"
                else:
                    continue

                tdata[id][hash] = read_file(os.path.join(parent,fname) )


        h256 = _pystribog.StribogHash(256)
        h512 = _pystribog.StribogHash(512)

        self.assertTrue( len(tdata)>=4 )
        for k,v in tdata.items():
            #print(v)
            h256.clear()
            h256.update(v["msg"])
            hash = binascii.hexlify( h256.digest() )
            self.assertEqual(hash, v["h256"] )

            h512.clear()
            h512.update(v["msg"])
            hash = binascii.hexlify( h512.digest() )
            self.assertEqual(hash, v["h512"] )

if __name__ == '__main__':
    unittest.main()        
