import cv2
import numpy as np


class SVMManager:

    def __init__(self):
        self.svm = cv2.ml.SVM_create()

    def train(self, labelData, trainData):
        labelsMat = np.array([labelData], np.int32)
        trainingDataMat = np.array(trainData, np.float32)

        self.svm.setType(cv2.ml.SVM_C_SVC)
        self.svm.setKernel(cv2.ml.SVM_LINEAR)
        # self.svm.setDegree(0.0)
        # self.svm.setGamma(0.0)
        # self.svm.setCoef0(0.0)
        # self.svm.setC(0)
        # self.svm.setNu(0.0)
        # self.svm.setP(0.0)
        # self.svm.setClassWeights(None)
        self.svm.setTermCriteria((cv2.TERM_CRITERIA_COUNT, 100, 1.e-06))
        self.svm.train(trainingDataMat, cv2.ml.ROW_SAMPLE, labelsMat)
        # self.svm.save('train.dat')

    def predict(self, testData):
        sample_data = np.array([testData], np.float32)
        result = self.svm.predict(sample_data)
        return result
