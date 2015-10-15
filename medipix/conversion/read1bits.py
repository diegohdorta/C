from numpy import empty
from PIL import Image
from bitstring import BitStream

f = open('sol', 'rb')
b = BitStream(f)
b.read(52*8)

a = empty((256, 256))
for j in range(256):
	for i in range(256):
		a[j][i] = b.read(1).int

img = Image.fromarray(a, mode='1')
img.save('sol.tiff')

