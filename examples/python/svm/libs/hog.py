import cv2
import numpy as np


class HOGManager:

    def __init__(self):
        winSize = (64, 64)
        blockSize = (16, 16)
        blockStride = (8, 8)
        cellSize = (8, 8)
        nbins = 9
        self.hog = cv2.HOGDescriptor(winSize, blockSize, blockStride, cellSize, nbins)

    def compute(self, img):
        size = 64
        resizeImg = cv2.resize(img, (size, size))
        hist = self.hog.compute(resizeImg)
        return hist
