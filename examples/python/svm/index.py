import cv2
import numpy as np

bin_n = 16

def hog(img):
    gx = cv2.Sobel(img, cv2.CV_32F, 1, 0)
    gy = cv2.Sobel(img, cv2.CV_32F, 0, 1)
    mag, ang = cv2.cartToPolar(gx, gy)

    # quantizing binvalues in (0...16)
    bins = np.int32(bin_n * ang / (2 * np.pi))

    # Divide to 4 sub-squares
    bin_cells = bins[:10, :10], bins[10:, :10], bins[:10, 10:], bins[10:, 10:]
    mag_cells = mag[:10, :10], mag[10:, :10], mag[:10, 10:], mag[10:, 10:]
    hists = [np.bincount(b.ravel(), m.ravel(), bin_n)
             for b, m in zip(bin_cells, mag_cells)]
    hist = np.hstack(hists)
    return hist

if __name__ == '__main__':
    # Data for visual representation
    width = 512
    height = 512
    image = np.zeros((height, width, 3), np.uint8)

    # Set up training data
    labels = [1, -1, -1, -1]
    trainingData = [[501, 10], [255, 10], [501, 255], [10, 501]]
    trainingDataMat = np.array(trainingData, np.float32)
    labelsMat = np.array([labels], np.int32)

    img = cv2.imread('../../data/images/lena.jpg', 0)
    hist = hog(img)
    print hist

    # Train the SVM
    svm = cv2.ml.SVM_create()
    svm.setType(cv2.ml.SVM_C_SVC)
    svm.setKernel(cv2.ml.SVM_LINEAR)
    # svm.setDegree(0.0)
    # svm.setGamma(0.0)
    # svm.setCoef0(0.0)
    # svm.setC(0)
    # svm.setNu(0.0)
    # svm.setP(0.0)
    # svm.setClassWeights(None)
    svm.setTermCriteria((cv2.TERM_CRITERIA_COUNT, 100, 1.e-06))
    svm.train(trainingDataMat, cv2.ml.ROW_SAMPLE, labelsMat)
    svm.save('train.dat')

    # Show the decision regions given by the SVM
    green = np.array([0, 255, 0])
    blue = np.array([255, 0, 0])

    for i in xrange(image.shape[0]):
        for j in xrange(image.shape[1]):
            sampleMat = np.array([[j, i]], np.float32)
            response = svm.predict(sampleMat)

            if response[1][0, 0] == 1:
                image[i, j] = green
            else:
                image[i, j] = blue

    # Show the training data
    thickness = -1
    lineType = 8
    cv2.circle(image, (501, 10), 5, (0, 0, 0), thickness, lineType)
    cv2.circle(image, (255, 10), 5, (255, 255, 255), thickness, lineType)
    cv2.circle(image, (501, 255), 5, (255, 255, 255), thickness, lineType)
    cv2.circle(image, (10, 501), 5, (255, 255, 255), thickness, lineType)

    # Show support vectors
    thickness = 2
    lineType = 8
    sv = svm.getUncompressedSupportVectors()

    for i in xrange(sv.shape[0]):
        v = sv[i]
        cv2.circle(image, (int(v[0]), int(v[1])), 6,
                   (128, 128, 128), thickness, lineType)

    # cv2.imshow("result.png", image)         # save the image

    cv2.imshow("SVM Simple Example", image)  # show it to the user
    cv2.waitKey(0)

    cv2.destroyAllWindows()
