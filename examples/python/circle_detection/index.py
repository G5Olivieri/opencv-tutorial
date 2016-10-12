import numpy as np
import cv2


class HoughCircle:

    def __init__(self):
        tmp = 0

    def process(self, frame):

        grayImg = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        # grayImg = cv2.medianBlur(grayImg, 5)
        threshold = 50
        cannyImg = cv2.Canny(grayImg, threshold1=threshold, threshold2=threshold*2)
        cv2.imshow('cannyImg', cannyImg)
        circles = cv2.HoughCircles(
            grayImg, cv2.HOUGH_GRADIENT, dp=1, minDist=50, param1=threshold*2, param2=30, minRadius=50, maxRadius=100)

        if circles is not None:
            circles = np.uint16(np.around(circles))
            for i in circles[0, :]:
                cv2.circle(frame, (i[0], i[1]), i[2], (0, 255, 0), 2)
                cv2.circle(frame, (i[0], i[1]), 2, (0, 0, 255), 3)


class MediaProcessor:

    def __init__(self, detector):
        self.detector = detector

    def run(self):
        video = cv2.VideoCapture('C:/Users/user/Desktop/test/3_2016-10-07_16-24-43.mp4')

        while(True):
            ret, frame = video.read()
            frame = cv2.resize(frame, (640,480))

            srcImg = self.detector.process(frame)

            cv2.imshow('frame', frame)
            cv2.waitKey(100)

        video.release()
        cv2.destroyAllWindows()

if __name__ == '__main__':

    detector = HoughCircle()
    mediaRes = MediaProcessor(detector)
    mediaRes.run()
