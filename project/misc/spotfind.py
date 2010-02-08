#!/usr/bin/python
#test of range finding, the two provided jpgs look at a light source 1.9m away

import math, os, sys
from PIL import Image

#findBlob takes an array of RGB pixels and returns the 
#centroid of the bright spot
def findBlob(pix):
    numPix = 0
    xMag = 0
    highPass = 750

    for x in range(640):
        for y in range(480):
            pixel = pix[x,y]
            light = pixel[0]+pixel[1]+pixel[2]
            if light >= highPass:
                xMag = xMag + x
                numPix = numPix + 1
    xCentre = xMag/numPix
    
    return xCentre

#findRange takes two x coordinates and uses simple
#triangulation to find the distance to the light source
def findRange(x1, x2):
    camWidth = 0.275  #distance between cameras
    degPerPix = 0.12  #degrees per pixel on the image

    dev1 = getDev(x1)
    dev2 = getDev(x2)
    
    alpha = math.radians(90 - dev1 * degPerPix)
    beta = math.radians(90 - dev2 * degPerPix)
    
    range = camWidth / ((1 / math.tan(alpha)) + (1 / math.tan(beta)))
    return range

#getDev is a helper that correctly finds the deviation
#from the centre of the image
def getDev(x):
    if x > 320:
        dev = x - 320
    else:
        dev = 320 - x
    return dev


if __name__ == '__main__':
    im1 = Image.open("test1.jpg")
    im2 = Image.open("test2.jpg")
    pix1 = im1.load()
    pix2 = im2.load()
    print findRange(findBlob(pix1), findBlob(pix2))
