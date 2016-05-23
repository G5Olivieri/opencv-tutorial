from PIL import Image
from pylab import *
import os

pil_im = Image.open('lena.jpg')
pil_dst = pil_im.convert('L')
im = array(pil_dst)

imshow(im)
figure()
hist(im.flatten(),128)


print('Please Click 3 pts')
x = ginput(3)
print('You Click :', x)

title('Draw : "lena.jpg"')
show()

# pil_im.thumbnail((128,128)).save('modify.jpg')

# pil_dst = pil_im.thumbnail((128,128))

# pil_dst.save('modify.jpg')