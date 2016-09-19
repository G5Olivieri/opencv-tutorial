import cv2
from motion.frame_diff import MotionFrameDifferance
from motion.energy_image import MotionEnergyImage


class MediaProcessor:

    def __init__(self, detector):
        self.detector = detector

    def run(self):
        video = cv2.VideoCapture(0)

        while(True):
            ret, frame = video.read()

            gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

            dst = self.detector.process(gray)
            if dst is not None:
                cv2.imshow('dst', dst)
                im2, contours, hierarchy = cv2.findContours(
                    dst.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
                cv2.drawContours(frame, contours, -1, (0, 255, 0), 3)

            cv2.imshow('image', frame)
            cv2.waitKey(33)

        video.release()
        cv2.destroyAllWindows()


if __name__ == '__main__':

    # detector = MotionFrameDifferance()
    detector = MotionEnergyImage()
    mediaRes = MediaProcessor(detector)

    mediaRes.run()
