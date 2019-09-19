import unittest
import _pystribog
import binascii

M1=b"012345678901234567890123456789012345678901234567890123456789012"

class TestModuleMethods(unittest.TestCase):
    
    def test_hash_512(self):
        h = _pystribog.StribogHash(512)
        h.update(M1)

        res = h.digest()
        
        E="1b54d01a4af5b9d5cc3d86d68d285462b19abc2475222f35c085122be4ba1ffa00ad30f8767b3a82384c6574f024c311e2a481332b08ef7f41797891c1646f48"

        self.assertEqual(binascii.hexlify(res), E )
        
        h.clear()
        h.update(M1)
        res = h.hexdigest()
        self.assertEqual(res, E )

    def test_hash_256(self):
        h = _pystribog.StribogHash(256)
        h.update(M1)

        res = h.digest()
        
        E="9d151eefd8590b89daa6ba6cb74af9275dd051026bb149a452fd84e5e57b5500"

        self.assertEqual(binascii.hexlify(res), E )
        
        h.clear()
        h.update(M1)
        res = h.hexdigest()
        self.assertEqual(res, E )

if __name__ == '__main__':
    unittest.main()        
