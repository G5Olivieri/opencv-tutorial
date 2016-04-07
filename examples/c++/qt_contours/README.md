# Find Contours using OpenCV

在影像處理中，對於依靠外型當作辨識的依據的都會需要用都輪廓偵測(Contours Detection)，如手勢辨識、動作辨識或物件辨識等...

而一般在偵側輪廓之前都會先透過compare()、inRange()、threshold()、adaptiveThreshold()、Canny()..等方法找出欲偵測的輪廓候選點。

```c++
cv::Mat srcImg;
cv::Mat grayImg;
cv::cvtColor( srcImg, grayImg, cv::COLOR_BGR2GRAY );

cv::Mat cannyImg;
std::vector<std::vector<cv::Point> > contours;
std::vector<cv::Vec4i> hierarchy;

cv::Canny( grayImg, cannyImg, 50, 100, 3 );
cv::findContours( cannyImg, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );

cv::RNG rng(12345);
cv::Mat drawing = cv::Mat::zeros( cannyImg.size(), CV_8UC3 );
for( int i = 0; i< contours.size(); i++ )
{
    cv::Scalar color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
    cv::drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, cv::Point() );
}

```

#### `void findContours(InputOutputArray image, OutputArrayOfArrays contours, OutputArray hierarchy, int mode, int method, Point offset=Point())`

- image 輸入影像
- contours 輸出影像
- hierarchy 輪廓的陣列
- mode 偵測模式
- method 計算是否為同一輪廓的方法
- offset 

**hierarchy**

用編號(0~5)來標示輪廓，2及2a分別表示外部(external)和內部(internal)的輪廓。
![](http://docs.opencv.org/3.1.0/hierarchy.png)

**mode**
- RETR_EXTERNAL (只會列出外部的輪廓)
- RETR_LIST (不管外部、內部輪廓都加入陣列中，也就是列出全部的輪廓)
- RETR_CCOMP (物件的概念，一個外部(1)輪廓會搭配內部(2)輪廓組合成一個物件關係)
![](http://docs.opencv.org/3.1.0/ccomp_hierarchy.png)
- RETR_TREE (階層樹的概念，橘色是輪廓的表示數字，綠色是階層的代表數字)
![](http://docs.opencv.org/3.1.0/tree_hierarchy.png)
- RETR_FLOODFILL 

**method**
- CV_CHAIN_APPROX_NONE (儲存所有的輪廓點)
- CV_CHAIN_APPROX_SIMPLE (省略重複性垂直或水平方向的輪廓點，舉例：正四方形只儲存四個角點)
![](http://docs.opencv.org/3.1.0/none.jpg)
- CV_CHAIN_APPROX_TC89_L1 (Teh-Chin chain演算法)
- CV_CHAIN_APPROX_TC89_KCOS (Teh-Chin chain演算法)

#### `void drawContours(InputOutputArray image, InputArrayOfArrays contours, int contourIdx, const Scalar& color, int thickness=1, int lineType=8, InputArray hierarchy=noArray(), int maxLevel=INT_MAX, Point offset=Point() )`

- image 塗畫的影像
- contours 所有輪廓的儲存陣列
- contourIdx 欲塗畫的輪廓
- color 塗畫的顏色
- thickness 線條的粗細
- lineType [線條](http://docs.opencv.org/2.4/modules/core/doc/drawing_functions.html#void line(Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness, int lineType, int shift))的類別
- hierarchy 輪廓的階層資訊
- maxLevel 繪製輪廓的最大等級。如果等級為0，繪製單獨的輪廓。如果為1，繪製輪廓及在其後的相同的級別下輪廓。如果值為2，所有的輪廓。如果等級為2，繪製所有同級輪廓及所有低一級輪廓
- offset 按照給出的偏移量移動每一個輪廓點坐標.當輪廓是從某些感興趣區域(ROI)中提取的然後需要在運算中考慮ROI偏移量時，將會用到這個參數

### 更多OpenCV文章請參考：[OpenCV Tutorial (學習筆記)](http://ccw1986.blogspot.tw/2013/09/learningopencv.html)

