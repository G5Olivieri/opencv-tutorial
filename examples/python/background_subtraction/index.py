import numpy as np
import cv2

class MediaProcessor:

    def __init__(self, detector):
        self.detector = detector

    def run(self):
        video = cv2.VideoCapture(0)

        while(True):
            ret, frame = video.read()

            fgmask = self.detector.apply(frame)

            cv2.imshow('fgmask', fgmask)
            cv2.imshow('image', frame)
            cv2.waitKey(33)

        video.release()
        cv2.destroyAllWindows()


if __name__ == '__main__':

    fgbg = cv2.createBackgroundSubtractorMOG2(False)
    mediaRes = MediaProcessor(fgbg)

    mediaRes.run()
