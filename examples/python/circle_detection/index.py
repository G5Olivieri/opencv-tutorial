import numpy as np
import cv2


class HoughCircle:

    def __init__(self):
        tmp = 0

    def process(self, frame):

        grayImg = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        param1 = 50
        param2 = 30
        minRadius = 0
        maxRadius = 0
        grayImg = cv2.medianBlur(grayImg, 5)
        circles = cv2.HoughCircles(
            grayImg, cv2.HOUGH_GRADIENT, 1, 20)

        if circles is not None:
            circles = np.uint16(np.around(circles))
            for i in circles[0, :]:
                cv2.circle(frame, (i[0], i[1]), i[2], (0, 255, 0), 2)
                cv2.circle(frame, (i[0], i[1]), 2, (0, 0, 255), 3)

        return frame


class MediaProcessor:

    def __init__(self, detector):
        self.detector = detector

    def run(self):
        video = cv2.VideoCapture(0)

        while(True):
            ret, frame = video.read()

            srcImg = self.detector.process(frame)
            
            cv2.imshow('frame', frame)
            cv2.imshow('srcImg', srcImg)
            cv2.waitKey(33)

        video.release()
        cv2.destroyAllWindows()

if __name__ == '__main__':

    detector = HoughCircle()
    mediaRes = MediaProcessor(detector)
    mediaRes.run()
