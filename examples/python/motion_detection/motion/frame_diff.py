import cv2


class MotionFrameDifferance:

    def __init__(self):
        self.preFrame = None

    def process(self, frame):
        if self.preFrame is not None:
            diff = cv2.absdiff(frame, self.preFrame)
            self.preFrame = frame
            return diff
        else:
            self.preFrame = frame
            return None
