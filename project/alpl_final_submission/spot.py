#!/usr/bin/python

from PIL import Image
import os, sys

def findBlob(pix):
    numPix = 0
    xMag = 0
    yMag = 0
    highPass = 748

    for x in range(320):
        for y in range(240):
            pixel = pix[x,y]
            light = pixel[0] + pixel[1] + pixel[2]
            if light >= highPass:
                xMag = xMag + x
                yMag = yMag + y
                numPix = numPix + 1
    xCentre = xMag/numPix
    yCentre = yMag/numPix
    
    return (xCentre,yCentre)

if __name__ == '__main__':
    im1 = Image.open("pic2.jpg")
    
    pix1 = im1.load()
    
    print findBlob(pix1)

