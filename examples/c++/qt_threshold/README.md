#  Thresholding using OpenCV

最簡單的影像切割方法


##### `double threshold(InputArray src, OutputArray dst, double thresh, double maxval, int type)`

- `src` 輸入影像
- `dst` 輸出影像
- `thresh` 門檻值
- `maxval` 滿足條件給予該像素點的值
- `type` 計算後輸出影像的呈現型態，型態如下：
    - THRESH_BINARY
![](http://docs.opencv.org/2.4/_images/math/21dfc802899546a3a9a51794d241330e6377f032.png)

    - THRESH_BINARY_INV
![](http://docs.opencv.org/2.4/_images/math/2858653b2a9f18e326acd861f4f23476f918e52b.png)

    - THRESH_TRUNC
![](http://docs.opencv.org/2.4/_images/math/85cd5dfea2f25f50640e7555c4019829859ff661.png)

    - THRESH_TOZERO
![](http://docs.opencv.org/2.4/_images/math/c42e93ea5c713fb2fca2605fa03ccbdf15a98d16.png)

    - THRESH_TOZERO_INV
![](http://docs.opencv.org/2.4/_images/math/6729a7b61fa189e9ad1a365aa5eb9290b70b023e.png)

```c++
cv::Mat grayImg;
cv::cvtColor(srcImg, grayImg, cv::COLOR_BGR2GRAY);

cv::Mat binImg, binInvImg, truncImg, tozeroImg, tozeroInvImg, otsuImg, trianImg;
double th = 127, maxVal = 255;
cv::threshold( grayImg, binImg, th, maxVal, cv::THRESH_BINARY );
cv::threshold( grayImg, binInvImg, th, maxVal, cv::THRESH_BINARY_INV );
cv::threshold( grayImg, truncImg, th, maxVal, cv::THRESH_TRUNC );
cv::threshold( grayImg, tozeroImg, th, maxVal, cv::THRESH_TOZERO );
cv::threshold( grayImg, tozeroInvImg, th, maxVal, cv::THRESH_TOZERO_INV );
cv::threshold( grayImg, trianImg, th, maxVal, cv::THRESH_TRIANGLE );
cv::threshold( grayImg, otsuImg, 0, maxVal, cv::THRESH_BINARY+cv::THRESH_OTSU );

```

![](http://farm2.staticflickr.com/1568/25817987034_09939280c2_b.jpg)

**詳細Sample Code請參考[GitHub]()**

##### `void adaptiveThreshold(InputArray src, OutputArray dst, double maxValue, int adaptiveMethod, int thresholdType, int blockSize, double C)`

- `src` 輸入影像(灰階)
- `dst` 輸出影像
- `maxValue` 滿足條件給予該像素點的值
- `adaptiveMethod` 自動篩選門檻值的方法
    - ADAPTIVE_THRESH_MEAN_C 平均加權
    - ADAPTIVE_THRESH_GAUSSIAN_C 高斯函數
- `thresholdType` 計算後輸出影像的呈現型態，型態如下：
    - THRESH_BINARY
![](http://docs.opencv.org/2.4/_images/math/21dfc802899546a3a9a51794d241330e6377f032.png)

    - THRESH_BINARY_INV
![](http://docs.opencv.org/2.4/_images/math/2858653b2a9f18e326acd861f4f23476f918e52b.png)

- `blockSize` 鄰近像素需要加入參考的大小
- `C` 

```c++
cv::Mat grayImg;
cv::cvtColor(srcImg, grayImg, cv::COLOR_BGR2GRAY);

cv::Mat adapMaenImg, adapGaussianImg;
double maxVal = 255;

cv::adaptiveThreshold( grayImg, adapMaenImg, maxVal, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 11, 2 );
cv::adaptiveThreshold( grayImg, adapGaussianImg, maxVal, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 11, 2 );
```

**詳細Sample Code請參考[GitHub]()**


### 更多OpenCV文章請參考：[OpenCV Tutorial (學習筆記)](http://ccw1986.blogspot.tw/2013/09/learningopencv.html)