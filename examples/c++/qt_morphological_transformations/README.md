#  Morphological Dilation and Erosion using OpenCV

**型態學常用的4個運算：**
- 膨脹(Dilation)
- 侵蝕(Erosion)
- 斷開(Opening)
- 閉合(Closing)

**運用層面：**
- 消除影像中的雜訊時 (Removing noise)
- 計算影像中的連通物件時 (Isolation of individual elements and joining disparate elements in an image.)
- 尋找影像中最大物件或最小區域時 (Finding of intensity bumps or holes in an image)

#### 膨脹(Dilation)
A是目標影像，B是結構元素，膨脹就是A⊕B

![Dilation](http://farm2.staticflickr.com/1458/25781277043_e0bbfac3a7_b.jpg)

#### 侵蝕(Erosion)
A是目標影像，B是結構元素，侵蝕就是AΘB

![Erosion](http://farm2.staticflickr.com/1555/25781277073_2fe5866835_b.jpg)

#### 斷開(Opening)
先侵蝕再膨脹，斷開就是(AΘB)⊕B

![Opening](http://farm2.staticflickr.com/1712/25781277113_0cb6110f0e_b.jpg)

#### 閉合(Closing)
先膨脹再侵蝕，閉合就是(A⊕B)ΘB

![Closing](http://farm2.staticflickr.com/1534/26317812961_56afce1be7_b.jpg)

##### `void dilate(InputArray src, OutputArray dst, InputArray kernel, Point anchor=Point(-1,-1), int iterations=1, int borderType=BORDER_CONSTANT, const Scalar& borderValue=morphologyDefaultBorderValue() )`

- `src` 輸入影像 (CV_8U、CV_16U、CV_16S、CV_32F或CV_64F)
- `dst` 輸出影像
- `kernel` 膨脹結構元素
- `anchor` 結構元素的原點
- `iterations` 膨脹次數
- `borderType`
- `borderValue`

```c++
cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
cv::Mat dilateImg;
cv::dilate(srcImg, dilateImg, element, cv::Point(-1,-1), 1);
```

##### `void erode(InputArray src, OutputArray dst, InputArray kernel, Point anchor=Point(-1,-1), int iterations=1, int borderType=BORDER_CONSTANT, const Scalar& borderValue=morphologyDefaultBorderValue() )`

- `src` 輸入影像 (CV_8U、CV_16U、CV_16S、CV_32F或CV_64F)
- `dst` 輸出影像
- `kernel` 侵蝕結構元素
- `anchor` 結構元素的原點
- `iterations` 侵蝕次數
- `borderType`
- `borderValue`

```
cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
cv::Mat erodeImg;
cv::erode(srcImg, erodeImg, element, cv::Point(-1,-1), 1);
```

##### `cv::Mat getStructuringElement(int shape, Size ksize, Point anchor = Point(-1,-1))`

- `shape`  MORPH_RECT、MORPH_CROSS、MORPH_ELLIPSE
- `ksize` 結構元素的大小
- `anchor` 結構元素的原點

##### `void morphologyEx(InputArray src, OutputArray dst, int op, InputArray kernel, Point anchor=Point(-1,-1), int iterations=1, int borderType=BORDER_CONSTANT, const Scalar& borderValue=morphologyDefaultBorderValue() )`

- `src` 輸入影像 (CV_8U、CV_16U、CV_16S、CV_32F或CV_64F)
- `dst` 輸出影像
- `kernel` 侵蝕結構元素
- `op` 型態學的類別
1. MORPH_OPEN 
2. MORPH_CLOSE 
3. MORPH_GRADIENT
4. MORPH_TOPHAT
5. MORPH_BLACKHAT
6. MORPH_HITMISS
- `iterations` 膨脹或侵蝕次數
- `borderType`
- `borderValue`

```c++
cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
cv::Mat closeImg;
cv::morphologyEx( srcImg, closeImg, cv::MORPH_CLOSE, element);

cv::Mat openImg;
cv::morphologyEx( srcImg, openImg, cv::MORPH_OPEN, element);
```

**各種方法的結果**

![](http://farm2.staticflickr.com/1611/25782706073_88b3da8047_b.jpg)

**詳細Sample Code請參考[GitHub]()**

### 更多OpenCV文章請參考：[OpenCV Tutorial (學習筆記)](http://ccw1986.blogspot.tw/2013/09/learningopencv.html)

