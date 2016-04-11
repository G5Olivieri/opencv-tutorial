# Hough Transform using OpenCV

一般在偵測霍夫線前會有前處理動作`邊緣偵測`，而霍夫圓不用，因為該API已包含此功能。


要計算線可使用卡迪爾座標系統(Cartesian coordinate system)及極座標系統(Polar coordinate system)


卡迪爾座標的線公式 = `y = kx + b`

![](http://docs.opencv.org/3.0-beta/_images/Hough_Lines_Tutorial_Theory_0.jpg)

© from OpenCV

極座標的線公式 = `r = xcosθ + ysinθ`

**OpenCV提供兩個API供開發者使用：**
- The Standard Hough Transform `HoughLines`
- The Probabilistic Hough Line Transform `HoughLinesP`

兩者之間的差別在於

![](http://docs.opencv.org/3.1.0/houghlines4.png)

© from OpenCV

#### `void HoughLines(InputArray image, OutputArray lines, double rho, double theta, int threshold, double srn=0, double stn=0 )`

- `image` 輸入影像
- `lines` 輸出結果(r，θ)，r是代表到原點的距離(影像的左上角為原點)，θ是角度
- `rho` 極坐標中極徑r的最小單位 
- `theta` 極坐標中極角Ɵ的最小單位
- `threshold` 門檻值
- `srn` 多尺度霍夫轉換rho的分母
- `stn` 多尺度霍夫轉換theta的分母

```c++
cv::Mat grayImg, cannyImg;
cv::cvtColor( srcImg, grayImg, cv::COLOR_BGR2GRAY );
cv::Canny(grayImg, cannyImg, 50, 150, 3);

cv::Mat houghImg;
std::vector<cv::Vec2f> lines;
cv::cvtColor( cannyImg, houghImg, cv::COLOR_GRAY2BGR );
cv::HoughLines(cannyImg, lines, 1, CV_PI/180, 250, 0, 0 );

for( size_t i = 0; i < lines.size(); i++ )
{
    float rho = lines[i][0], theta = lines[i][1];
    cv::Point pt1, pt2;
    double a = std::cos(theta), b = std::sin(theta);
    double x0 = a*rho, y0 = b*rho;
    pt1.x = cvRound(x0 + 1000*(-b));
    pt1.y = cvRound(y0 + 1000*(a));
    pt2.x = cvRound(x0 - 1000*(-b));
    pt2.y = cvRound(y0 - 1000*(a));
    cv::line( houghImg, pt1, pt2, cv::Scalar(0,0,255), 3, cv::LINE_AA);
}

```

#### `void HoughLinesP(InputArray image, OutputArray lines, double rho, double theta, int threshold, double minLineLength=0, double maxLineGap=0 )`

- `image` 輸入影像
- `lines` 輸出結果(x_1, y_1, x_2, y_2)，(x_1,y_1)及(x_2, y_2)來表示線的兩端點
- `rho` 極坐標中極徑r的最小單位
- `theta` 極坐標中極角Ɵ的最小單位
- `threshold` 門檻值
- `minLineLength` 線小於此門檻值將不列入考慮
- `maxLineGap` 線與線之間的間隔不得超過此門檻值

```c++
cv::Mat grayImg, cannyImg;
cv::cvtColor( srcImg, grayImg, cv::COLOR_BGR2GRAY );
cv::Canny(grayImg, cannyImg, 50, 150, 3);

cv::Mat houghImg;
std::vector<cv::Vec2f> lines;
cv::cvtColor( cannyImg, houghImg, cv::COLOR_GRAY2BGR );
cv::HoughLines(cannyImg, lines, 1, CV_PI/180, 250, 0, 0 );

std::vector<cv::Vec4i> linesP;
cv::HoughLinesP(cannyImg, linesP, 1, CV_PI/180, 50, 100, 5 );
for( size_t i = 0; i < linesP.size(); i++ )
{
    cv::Vec4i l = linesP[i];
    cv::line( houghImg, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(255,0,0), 3, CV_AA);
}

```

#### `void HoughCircles(InputArray image, OutputArray circles, int method, double dp, double minDist, double param1=100, double param2=100, int minRadius=0, int maxRadius=0 )`

- `image` 輸入影像
- `circles` 輸出結果 (x, y, radius)
- `method` 目前支援CV_HOUGH_GRADIENT
- `dp` 累加器圖像的解析度
- `minDist` 兩個圓之間的距離(值太小可能會產生很多鄰近的圓出現，反之，太大則有可能會沒偵測到某些圓)
- `param1` cv::Canny()的參數，此值代表上限門檻，而下限則為上限的一半
- `param2` 累加器的門檻值
- `minRadius` 最小圓半徑
- `maxRadius` 最大圓半徑

```c++
cv::Mat grayImg, cannyImg;
cv::cvtColor( srcImg, grayImg, cv::COLOR_BGR2GRAY );
cv::Mat houghImg;
cv::cvtColor( cannyImg, houghImg, cv::COLOR_GRAY2BGR );

std::vector<cv::Vec3f> circles;
cv::HoughCircles(grayImg, circles, cv::HOUGH_GRADIENT, 2, grayImg.rows/4, 200, 100 );
for( size_t i = 0; i < circles.size(); i++ )
{
    cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
    int radius = cvRound(circles[i][2]);
    circle( houghImg, center, 3, cv::Scalar(0,255,0), -1, 8, 0 );
    circle( houghImg, center, radius, cv::Scalar(0,0,255), 3, 8, 0 );
}

```

**偵測結果如下：**

**原圖**

![](http://farm2.staticflickr.com/1604/25762790283_94481c645f_b.jpg)

**HoughLines**

![](http://farm2.staticflickr.com/1502/25762790203_4e3f514023_b.jpg)

**HoughLinesP**

![](http://farm2.staticflickr.com/1478/26092679610_a82208c022_b.jpg)

**HoughCircles**

![](http://farm2.staticflickr.com/1463/25760696034_6955294329_b.jpg)


**詳細Sample Code請參考[GitHub](https://github.com/MarcWang/opencv-tutorial/blob/master/examples/c%2B%2B/qt_hough_transform/main.cpp)**

### 更多OpenCV文章請參考：[OpenCV Tutorial (學習筆記)](http://ccw1986.blogspot.tw/2013/09/learningopencv.html)

