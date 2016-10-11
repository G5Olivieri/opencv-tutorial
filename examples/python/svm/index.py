import cv2
import os
import numpy as np
from libs.svm import SVMManager
from libs.hog import HOGManager


def load_files(folder):
    files = []
    for filename in os.listdir(folder):
        files.append(filename)
    return files


def load_images(folder):
    images = []
    files = load_files(folder)
    for file in files:
        img = cv2.imread(os.path.join(folder, file), 0)
        if img is not None:
            images.append(img)
    return images


def extractFeature(pos_images, neg_images):

    hogMgr = HOGManager()
    train_data = []
    label_data = []
    for img in pos_images:
        # cv2.imshow('pos', img)
        # cv2.waitKey(1)
        posHist = hogMgr.compute(img)
        train_data.append(posHist)
        label_data.append(1)

    for img in neg_images:
        # cv2.imshow('neg', img)
        # cv2.waitKey(1)
        negHist = hogMgr.compute(img)
        train_data.append(negHist)
        label_data.append(-1)

    return train_data, label_data


class MediaProcessor:

    def __init__(self):
        self.tmp = ''

    def run(self):
        pos_images = load_images('./images/pos')
        print len(pos_images)

        neg_images = load_images('./images/neg')
        print len(neg_images)

        trainData, labelData = extractFeature(pos_images, neg_images)

        svmMgr = SVMManager()
        svmMgr.train(labelData, trainData)
        hogMgr = HOGManager()

        video = cv2.VideoCapture(0)

        while(True):
            ret, frame = video.read()

            imgshape = frame.shape
            sx = imgshape[1]/2-100
            sy = imgshape[0]/2-100
            ex = imgshape[1]/2+100
            ey = imgshape[0]/2+100

            roi = frame[sy:ey, sx:ex]
            
            grayImg = cv2.cvtColor(roi, cv2.COLOR_BGR2GRAY)
            testHist = hogMgr.compute(grayImg)
            result = svmMgr.predict(testHist)
            label = result[1][0][0]
            if label == -1.0:
                cv2.rectangle(frame, (sx, sy), (ex, ey), (0, 0, 255), 3)
            else:
                cv2.rectangle(frame, (sx, sy), (ex, ey), (0, 255, 0), 3)

            cv2.imshow('frame', frame)
            cv2.imshow('roi', roi)
            cv2.waitKey(33)

        video.release()
        cv2.destroyAllWindows()

if __name__ == '__main__':

    mediaRes = MediaProcessor()
    mediaRes.run()
