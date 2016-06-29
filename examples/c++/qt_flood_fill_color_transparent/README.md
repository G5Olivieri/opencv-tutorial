# Edge Detection Algorithm using OpenCV

**評估演算法的依據**
- 雜訊誤判為邊緣(Edge)
- 沒找出真正邊緣(Edge)

**各種邊緣偵測方式**
- Soble
- Laplacian
- Canny
- Prewitt
- Scharr


## Sobel Edge Detection (索貝爾運算元邊緣偵測)

依照對於水平方向或垂直方向的重要程度調整邊緣偵測的權重。

1. 計算水平方向變化

![](http://docs.opencv.org/3.0-beta/_images/math/42c8a258fd1418ea1caf81d3c5e2374b50b3abd2.png)

2. 計算垂直方向變化

![](http://docs.opencv.org/3.0-beta/_images/math/68c90e66d591588078f34bc1cd8516b76e2da730.png)

3. 合併兩個方向的變化，計算邊緣方向強度

![](http://docs.opencv.org/3.0-beta/_images/math/142fea0dc71faf5e430d35e1d2b8ba2262e784c7.png)

![](http://docs.opencv.org/3.0-beta/_images/math/0fb3e1afe9bd5e73d7df44e7aadefcdbbd0682a3.png)

```c++

cv::Mat srcImg, grayImg;
srcImg = cv::imread( "lena.jpg", cv::IMREAD_COLOR );
cv::cvtColor( srcImg, grayImg, cv::COLOR_BGR2GRAY );

cv::Mat sobelImg;
cv::Mat grad, grad_x, grad_y;
cv::Mat abs_grad_x, abs_grad_y;
int scale = 1;
int delta = 0;
int ddepth = CV_16S;

cv::Sobel( grayImg, grad_x, ddepth, 1, 0, 3, scale, delta, cv::BORDER_DEFAULT );
cv::convertScaleAbs( grad_x, abs_grad_x );

cv::Sobel( grayImg, grad_y, ddepth, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT );
cv::convertScaleAbs( grad_y, abs_grad_y );

cv::addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );
cv::threshold( grad, sobelImg, 100, 255, cv::THRESH_BINARY );
```

**詳細Sample Code請參考[GitHub](https://github.com/MarcWang/opencv-tutorial/blob/master/examples/c%2B%2B/qt_edge_detection/main.cpp)**

#### `void Sobel(InputArray src, OutputArray dst, int ddepth, int dx, int dy, int ksize=3, double scale=1, double delta=0, int borderType=BORDER_DEFAULT )`

- `src` 輸入影像
- `dst` 輸出影像
- `ddepth` 輸出圖的深度 (CV_8U、CV_16U/CV_16S、CV_32F、CV_64F)
- `xorder` x方向的微分階數
- `yorder` y方向的微分階數
- `ksize` Sobel kernel( 1, 3, 5..)
- `scale` 縮放值
- `delta` 偏移量
- `borderType` pixel extrapolation method (see borderInterpolate for details).

## Laplacian Edge Detection (拉普拉斯算子邊緣偵測)

![](http://docs.opencv.org/3.0-beta/_images/math/db37f7e4af1f7d8446b820f9d37bcfb89492d752.png)


```c++

cv::Mat srcImg, grayImg;
srcImg = cv::imread( "lena.jpg", cv::IMREAD_COLOR );
cv::cvtColor( srcImg, grayImg, cv::COLOR_BGR2GRAY );

cv::Mat laplacianImg, grad_16S;
cv::Laplacian( grayImg, grad_16S, CV_16S, 3, 1, 0, cv::BORDER_DEFAULT);
cv::convertScaleAbs( grad_16S, laplacianImg );
```


**詳細Sample Code請參考[GitHub](https://github.com/MarcWang/opencv-tutorial/blob/master/examples/c%2B%2B/qt_edge_detection/main.cpp)**


#### `void Laplacian(InputArray src, OutputArray dst, int ddepth, int ksize=1, double scale=1, double delta=0, int borderType=BORDER_DEFAULT )`

- `src` 輸入影像
- `dst` 輸出影像
- `ddepth` 輸出圖的深度
- `ksize` 二階導數的濾波器大小( 1, 3, 5..)
- `scale` 縮放值
- `delta` 偏移量
- `borderType` Pixel extrapolation method. See borderInterpolate for details.

## Canny Edge Detection (坎尼邊界偵測)
- 作者 Canny, J.F., A computational approach to edge detection. Nov 1986.

1. 去雜訊、模糊化 (Noise Reduction) ==> 5x5 Gaussian filter

![](http://dasl.mem.drexel.edu/alumni/bGreen/www.pages.drexel.edu/_weg22/gauss_mask.jpg)

2. 計算梯度方向與強度 (Finding Intensity Gradient) ==> Sobel kernel

![](http://dasl.mem.drexel.edu/alumni/bGreen/www.pages.drexel.edu/_weg22/mask_s.jpg)

3. 非最大抑制過濾誤判 (Non-maximum Suppression)

![](http://docs.opencv.org/3.0-beta/_images/nms.jpg)

4. 用雙門檻值過濾邊緣 (Hysteresis Thresholding)

![](http://docs.opencv.org/3.0-beta/_images/hysteresis.jpg)

```c++

double minThreshold = 50;
double maxThreshold = 150;
int apertureSize = 3;
bool L2gradient = false;

cv::Mat srcImg, grayImg, cannyImg;
srcImg = cv::imread( "lena.jpg", cv::IMREAD_COLOR );
cv::cvtColor( srcImg, grayImg, cv::COLOR_BGR2GRAY );
cv::Canny( grayImg, cannyImg, minThreshold, maxThreshold, apertureSize, L2gradient );

```


**詳細Sample Code請參考[GitHub](https://github.com/MarcWang/opencv-tutorial/blob/master/examples/c%2B%2B/qt_edge_detection/main.cpp)**


####  `void Canny(InputArray image, OutputArray edges, double threshold1, double threshold2, int apertureSize=3, bool L2gradient=false )`

- `image` 輸入影像( 8-bit )
- `edges` 輸出影像( 8-bit )
- `threshold1` 第一個門檻值(超過此門檻則視為候選者，須參考是否有連結`sure-edge`)
- `threshold2` 第二個門檻值(超過此門檻則視為`sure-edge`)
- `apertureSize` Sobel的aperture size
- `L2gradient` true(L2)、false(L1)


### 更多OpenCV文章請參考：[OpenCV Tutorial (學習筆記)](http://ccw1986.blogspot.tw/2013/09/learningopencv.html)

