import cv2
import os
import numpy as np
from libs.svm import SVMManager
from libs.hog import HOGManager

env = 'development'

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

        video = cv2.VideoCapture('C:/Users/user/Desktop/test/3_2016-10-07_16-24-43.mp4')

        frame_index = 0
        while(True):
            ret, frame = video.read()
            frame_index += 1
            if frame_index < 60:
                continue

            frame = cv2.resize(frame, (640,480))
            imgshape = frame.shape
            center_image_x = imgshape[1]/2
            center_image_y = imgshape[0]/2
            roi_range = 100
            search_shift = 12
            search_stride = 8
            default_shift = (search_shift/2)*search_stride
            begin_leftTop_x = center_image_x-roi_range-default_shift
            begin_leftTop_y = center_image_y-roi_range-default_shift
            begin_rightDown_x = center_image_x+roi_range-default_shift
            begin_rightDown_y = center_image_y+roi_range-default_shift
            end_leftTop_x = center_image_x-roi_range+default_shift
            end_leftTop_y = center_image_y-roi_range+default_shift
            end_rightDown_x = center_image_x+roi_range+default_shift
            end_rightDown_y = center_image_y+roi_range+default_shift

            count = 0
            for i in range(search_shift):
                for j in range(search_shift):
                    leftTop_x = begin_leftTop_x+j*search_stride
                    leftTop_y = begin_leftTop_y+i*search_stride
                    rightDown_x = begin_rightDown_x+j*search_stride
                    rightDown_y = begin_rightDown_y+i*search_stride
                    # print leftTop_x, leftTop_y, rightDown_x, rightDown_y
                    image_roi = frame[leftTop_y:rightDown_y, leftTop_x:rightDown_x]
                    image_gray = cv2.cvtColor(image_roi, cv2.COLOR_BGR2GRAY)
                    feature = hogMgr.compute(image_gray)
                    result = svmMgr.predict(feature)
                    label = result[1][0][0]
                    
                    if env is 'development':
                        image_draw = frame.copy()
                        cv2.rectangle(image_draw, (begin_leftTop_x, begin_leftTop_y), (end_rightDown_x, end_rightDown_y), (255, 0, 0), 3)
                        if label == -1.0:
                            cv2.rectangle(image_draw, (leftTop_x, leftTop_y), (rightDown_x, rightDown_y), (0, 0, 255), 3)
                        else:
                            count += 1
                            cv2.rectangle(image_draw, (leftTop_x, leftTop_y), (rightDown_x, rightDown_y), (0, 255, 0), 3)

                        cv2.imshow('search progress', image_draw)
                        cv2.waitKey(10)
                    else:
                        if label != -1.0:
                            count += 1

            print 'detect' , count
            cv2.imshow('frame', frame)
            cv2.waitKey(33)

        video.release()
        cv2.destroyAllWindows()

if __name__ == '__main__':

    mediaRes = MediaProcessor()
    mediaRes.run()
