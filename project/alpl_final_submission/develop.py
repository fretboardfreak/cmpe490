#!/usr/bin/python

from PIL import Image
import io

f = io.FileIO('memcolourbigjpg.txt', 'rb')

bytes = f.readall()

im = Image.frombuffer('RGB',(320,240),bytes,"raw","RGB",0,1)

im.save('testbig.jpg')

