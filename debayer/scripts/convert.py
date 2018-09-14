#!/usr/bin/python

import cv2, cv, os
import rawpy
import imageio
import numpy as np
import time




#imagePath = '/home/diego/debayer/media/image.raw'
#imageRaw = cv2.imread(imagePath, cv2.IMREAD_GRAYSCALE | cv2.IMREAD_ANYDEPTH)

#rgb = cv2.cvtColor(imageRaw, cv2.COLOR_BAYER_BG2BGR)
#cv2.imwrite('/home/diego/debayer/media/rgb.jpeg', rgb)

#print "done!"


raw = rawpy.imread('../media/image.raw')

#rgb = raw.postprocess(no_auto_bright=True,use_auto_wb =False,gamma=None)
#imageio.imsave('process.tiff', rgb)

bayer = raw.raw_image

print bayer

print len(bayer)


imageio.imsave('bayer.png', bayer)
os.system("file bayer.png")

#time.sleep(5)


#infile = '/home/diego/debayer/scripts/media/image.raw'

#img = cv2.imread(infile,0)

#imsize = imrows*imcols

#with open(infile, "rb") as rawimage:
#    img = np.fromfile(rawimage, np.dtype('u1'), imsize).reshape((imrows, imcols))
#    colour = cv2.cvtColor(img, cv2.COLOR_BAYER_BG2BGR)



#img[:,:,0] = 0
#img[:,:,2] = 0
#img[:,:,1] = 0


#cv2.imshow("aaa", img)
#cv2.waitKey(0)





#imageio.imsave('colour.png', img)

#os.system("file colour.png")






############################
'''
raw = rawpy.imread('image.raw')
os.system("file image.raw")

rgb = raw.postprocess((no_auto_bright=True,use_auto_wb =False,gamma=None)
imageio.imsave('process.tiff', rgb)


img = cv2.imread('process.tiff', cv2.CV_LOAD_IMAGE_COLOR)
os.system("file process.tiff")

#img = cv2.cvtColor(img, cv2.COLOR_BAYER_GR2RGB)

img = np.array(img, dtype=np.uint16)

img *= 256

imageio.imsave('final.png', img)
os.system("file final.png")

bayer = raw.raw_image

print bayer

imageio.imsave('bayer.png', bayer)



gray = cv2.imread('bayer.png')

img = cv2.cvtColor(gray, 'color.png', cv.CV_GRAY2RGB)
'''

############################

#imageio.imsave('color.png', img)

#rgb = raw.postprocess()
#imageio.imsave('default.tiff', rgb)

#rgb is just an RGB numpy array, so you can use any library (not just imageio) to save it to disk.

#If you want to access the unprocessed Bayer data, then do:

#bayer = raw.raw_image






#img = cv2.imread(img, cv2.CV_LOAD_IMAGE_COLOR) # Need to be sure to have a 8-bit input

#print i

#img = np.array(i, dtype=np.uint16) # This line only change the type, not values
#img *= 256 # Now we get the good values in 16 bit format

#print img


#img = cv2.cvtColor(image, cv2.COLOR_BAYER_GR2RGB)


#cv2.imwrite("final.png", img)


#i = cv2.imread(imgNameIn, cv2.CV_LOAD_IMAGE_COLOR) # Need to be sure to have a 8-bit input
#img = np.array(i, dtype=np.uint16) # This line only change the type, not values
#img *= 256 # Now we get the good values in 16 bit format


#i#mport numpy as np
#import cv2
#import sys

# Load image as string from file/database    

#fd = open('image.raw')
#img_str = fd.read()


#f = np.fromfile(fd, dtype=np.uint8,count=640*480)



#x = np.asarray(bytearray(img_str), dtype=np.uint8)

#img = cv2.cvtColor(x, cv2.COLOR_BAYER_GR2RGB)
#img = cv2.imdecode(x, cv2.IMREAD_UNCHANGED)

#cv2.imshow('conversion', img)
#cv2.imwrite("final.tiff", img)
#cv2.waitKey(0)


#imageio.imsave('final.png', rgb)

#img = cv2.cvtColor(rgb, cv2.COLOR_BAYER_GR2RGB)

#cv2.imshow('convert', img)


#cv2.imwrite("image.jpeg", img)



# RAW files are not supported in OpenCV see imread,
# But the file can be opened with Python and parsed with Numpy

#import numpy as np

#fd = open('flight0000.raw', 'rb')

#rows = 480

#cols = 640

#f = np.fromfile(fd, dtype=np.uint8,count=rows*cols)

#im = f.reshape((rows, cols)) #notice row, column format
#
#fd.close()

# This makes a numpy array that can be directly manipulated by OpenCV

#import cv2
#cv2.imshow('', im)
#cv2.waitKey()
#cv2.destroyAllWindows()







#import cv2
#from PIL import Image
#import numpy as np
#import os

#data = open("image.raw",'rb').read()

#size = (640, 480)

#print data

#img = Image.fromstring('L', imgSize, rawData, 'raw', 'F;16')
#img.save("foo.png")

#filePath = os.path.join(root,file)
#Load the image as grayscale image


#file = 'image.raw'
#root = '/home/diego/debayer/scripts/'

#filePath = os.path.join(root,file)

#image = cv2.imread(filePath, 0)

#img = cv2.cvtColor(image, cv2.COLOR_BAYER_GR2RGB)

#print img

#cv2.imshow('convert', img)
#cv2.imwrite("image.jpeg", img)


