# Skin Color Detection using OpenCV

本文提供HSV與YCrCb兩種顏色空間的膚色偵測流程

### 膚色偵測的應用：
- Face Detection and Tracking
- Hand Detection and Tracking
- Pornographic Filter


### RGB -> YCrCb
Y  = 0.299R + 0.587G + 0.114B

Cr = (R-Y)*0.713 + 128

Cb = (B-Y)*0.564 + 128

**YCrCb膚色範圍**

135 < Cr < 180

85  < Cb < 135

80  < Y


### RGB -> HSV
色相（H）是色彩的基本屬性，就是平常所說的顏色名稱，如紅色、黃色等。

飽和度（S）是指色彩的純度，越高色彩越純，低則逐漸變灰，取0-100%的數值。

明度（V），亮度（L），取0-100%。

**HSV膚色範圍**

0    < H < 50

0.23 < S < 0.68

```c++

cv::Mat bgr2hsvImg, hsv2skinImg;
cv::cvtColor(srcImg, bgr2hsvImg, cv::COLOR_BGR2HSV);
cv::inRange(bgr2hsvImg, cv::Scalar(0,58,40), cv::Scalar(35,174,255), hsv2skinImg);

cv::Mat bgr2ycrcbImg, ycrcb2skinImg;
cv::cvtColor( srcImg, bgr2ycrcbImg, cv::COLOR_BGR2YCrCb );
cv::inRange( bgr2ycrcbImg, cv::Scalar(80, 135, 85), cv::Scalar(255, 180, 135), ycrcb2skinImg );


```

詳細Sample Code請參考[GitHub](https://github.com/MarcWang/opencv-tutorial/tree/master/examples/c%2B%2B/qt_skin_detection)

#### `void inRange(InputArray src, InputArray lowerb, InputArray upperb, OutputArray dst)`
- src – 輸入影像
- lowerb – 範圍下限
- upperb – 範圍上限
- dst – 輸出影像(CV_8U)

### 更多OpenCV文章請參考：[OpenCV Tutorial (學習筆記)](http://ccw1986.blogspot.tw/2013/09/learningopencv.html)

