import cv2

if __name__ == '__main__':

    video = cv2.VideoCapture(0)

    print "OpenCV Version : {0}".format(cv2.__version__)

    while(True):
        ret, frame = video.read()

        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        cv2.imshow('image', frame)
        cv2.imshow('gray', gray)
        cv2.waitKey(33)

    video.release()
    cv2.destroyAllWindows()
