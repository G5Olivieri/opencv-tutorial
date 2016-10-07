import numpy as np
import cv2


class HoughCircle:

    def __init__(self):
        tmp = 0

    def process(self, frame):

        grayImg = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        grayImg = cv2.medianBlur(grayImg, 5)
        cannyImg = cv2.Canny(grayImg, threshold1=30, threshold2=90)
        cv2.imshow('cannyImg', cannyImg)
        # kernel = np.ones((3, 3), np.uint8)
        # dilateImg = cv2.dilate(cannyImg, kernel)
        # erodeImg = cv2.erode(dilateImg, kernel)
        # cv2.imshow('dilateImg', erodeImg)
        circles = cv2.HoughCircles(
            grayImg, cv2.HOUGH_GRADIENT, dp=1, minDist=50, param1=50, param2=100, minRadius=0, maxRadius=0)

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
