import cv2
import numpy as np


class MotionEnergyImage:

    def __init__(self, threshold=70, frameCount=10):
        self.threshold = threshold
        self.frameCount = frameCount
        self.dilateKernel = 7
        self.preFrame = None
        self.listFrame = []

    def process(self, frame):
        if self.preFrame is not None:
            diffImg = cv2.absdiff(frame, self.preFrame)

            ret, thImg = cv2.threshold(
                diffImg, self.threshold, 255, cv2.THRESH_BINARY)

            kernel = np.ones((self.dilateKernel, self.dilateKernel), np.uint8)
            dilateImg = cv2.dilate(thImg, kernel)

            self.preFrame = frame
            self.listFrame.append(dilateImg)

            currFrameCount = len(self.listFrame)

            if currFrameCount > 1:
                energyImages = None
                if currFrameCount > self.frameCount:
                    self.listFrame.pop(0)

                for img in self.listFrame:
                    if energyImages is not None:
                        energyImages = energyImages + img
                    else:
                        energyImages = img

                return energyImages

            return diffImg
        else:
            self.preFrame = frame
            return None
