import os
import mmap

def xor(opentext,key):
    return ''.join(
        chr(ord(opentext[i]) ^ ord(key[:1])) for i in range(len(opentext))
    )

opentext = "Bozoyan Oganes KKSO-03-20"
key = input('Enter password: ')
xor1 = xor(opentext,key)

try:
    file = os.open("boot.bin",os.O_RDWR)
    maper = mmap.mmap(file, 0)
    seek = maper.find(xor1.encode('utf-8'))
    maper[209:234] = xor1.encode('utf-8')
    os.close(file)
except Exception as err:
    print('Error', err)
else:
    print('done')