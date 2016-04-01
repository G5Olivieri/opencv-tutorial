# Human Detection using OpenCV

OpenCV在人形偵測上提供兩種不同的特徵(HOG, Haar)，個人認為HOG比較準，畢竟提出HOG特徵的作者本來就是拿來做人形偵測使用的。對於新版的OpenCV，使用HOG可以直接Call `cv::HOGDescriptor::getDefaultPeopleDetector()`就可以直接讀取訓練好XML檔，而要使用Harr特徵還是必須按照`cv::CascadeClassifier`的讀取方式，有提供`haarcascade_fullbody.xml`、`haarcascade_upperbody.xml`、`haarcascade_lowerbody.xml`可以使用，分別是全身、上半身及下半身的偵測。

## 方向梯度直方圖（Histogram of Oriented Gradient, HOG）

- [Histograms of Oriented Gradients for Human Detection](https://lear.inrialpes.fr/people/triggs/pubs/Dalal-cvpr05.pdf)

![](http://farm2.staticflickr.com/1676/25893785220_aa843ef888_b.jpg)

1. Gamma/Colour Normalization

使用Gamma方法校正色彩(RGB、LAB)影像，可有效降低光照的變化影響，如果影像已經為灰階影像可略過此步驟。

2. Gradient Computation

計算每一像素點的方向與強度

3. Spatial/Orientation Binning

以Cell為一個單位計算區塊中的像素(6x6)方向強度，當作此Cell的描述值(Descriptor)

4. Normalization and Descriptor Blocks

以Block為一個單位計算區塊中的Cells(3x3)描述。可防止光線的變化與前景背景的邊界被當作重要特徵。

5. Detector Window and Context

被偵測的前景物件視窗大小(64x128)

6. Classifier

將特徵丟進SVM訓練

![](http://farm2.staticflickr.com/1543/25564005813_306f88fd15_b.jpg)

![](http://farm2.staticflickr.com/1485/25561880304_30877d6314_b.jpg)

#### `cv::HOGDescriptor(Size _winSize, Size _blockSize, Size _blockStride, Size _cellSize, int _nbins, int _derivAperture=1, double _winSigma=-1, int _histogramNormType=HOGDescriptor::L2Hys, double _L2HysThreshold=0.2, bool _gammaCorrection=false, int _nlevels=HOGDescriptor::DEFAULT_NLEVELS, bool _signedGradient=false)`

- `_winSize` 偵測目標的大小
- `_blockSize` Block的像素大小(16x16)
- `_blockStride` Block位移的像素(8x8)
- `_cellSize` Cell的像素大小(8x8)
- `_nbins` Cell的分成幾種方向類(9)
- `_derivAperture`
- `_win_sigma` 平滑化的參數
- `_histogramNormType` 正規化的方法
- `_L2HysThreshold` 正規化的參數
- `_gammaCorrection` 要不要使用Gamma校正
- `_nlevels` Maximum number of detection window increases.
- `_signedGradient` 

### 更多OpenCV文章請參考：[OpenCV Tutorial (學習筆記)](http://ccw1986.blogspot.tw/2013/09/learningopencv.html)

