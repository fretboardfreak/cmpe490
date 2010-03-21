#!/usr/bin/python

from PIL import Image
import io

f = io.FileIO('mem4.txt', 'rb')

bytes = f.readall()

im = Image.frombuffer('L',(160,120),bytes,"raw","L",0,1)

im.save('test.jpg')

