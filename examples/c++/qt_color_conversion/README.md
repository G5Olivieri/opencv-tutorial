# Color Conversion

注意OpenCV讀取影像的影像格式是`BGR`而不是`RGB`，所以後續不管是要使用OpenCV提供的API轉換色彩空間或者自行取值運算都要特別注意。

```c++

cv::Mat srcImg = cv::imread("lena.jpg", CV_LOAD_IMAGE_COLOR);

//BGR to Gray Color Space
cv::Mat bgr2grayImg;
cv::cvtColor(srcImg, bgr2grayImg, cv::COLOR_BGR2GRAY);

//BGR to HSV Color Space
cv::Mat bgr2hsvImg, hsv2bgrImg;
cv::cvtColor(srcImg, bgr2hsvImg, cv::COLOR_BGR2HSV);

```

![](http://farm2.staticflickr.com/1509/25702533040_1e1bf601f0_b.jpg)

### `cv::imread(const string& filename, int flags=1 )`

- CV_LOAD_IMAGE_UNCHANGED (<0) loads the image as is (including the alpha channel if present)
- CV_LOAD_IMAGE_GRAYSCALE ( 0) loads the image as an intensity one
- CV_LOAD_IMAGE_COLOR (>0) loads the image in the `BGR` format

### `cv::cvtColor(InputArray src, OutputArray dst, int code, int dstCn=0 )`

- src 來源影像(8-bit unsigned, 16-bit unsigned ( CV_16UC... ), or single-precision floating-point.)
- dst 輸出影像(與來源影像同格式)
- code 欲轉換的色彩空間(參考以下常用的色彩轉換)

## 常用的色彩轉換

- COLOR_BGR2RGB
- COLOR_RGB2BGR

- COLOR_BGR2GRAY (convert between RGB to grayscale)

- COLOR_BGR2XYZ (convert BGR to CIE XYZ)
- COLOR_XYZ2BGR

- COLOR_BGR2YCrCb (convert BGR to luma-chroma)
- COLOR_YCrCb2BGR

- COLOR_BGR2HSV (convert BGR to HSV)
- COLOR_HSV2BGR

- COLOR_BGR2Lab (convert BGR to CIE Lab)
- COLOR_Lab2BGR

- COLOR_BGR2HLS (convert BGR to HLS)
- COLOR_HLS2BGR

## 色彩轉換公式

### RGB <--> GRAY
![](http://docs.opencv.org/2.4/_images/math/36b21ba24ff32d923fd71e99849a0a903311e19b.png)

### RGB <--> CIE XYZ
![](http://docs.opencv.org/2.4/_images/math/1d2bd4711fcf02fe24dd5f04477574f499c760b5.png)

### RGB <--> YCrCb
![](http://docs.opencv.org/2.4/_images/math/76c3f5fad2fceb004b65ff24934b113ed62381b7.png)
![](http://docs.opencv.org/2.4/_images/math/6b441940fbf4d16127c8dda6417fe684b74b923b.png)
![](http://docs.opencv.org/2.4/_images/math/bddc84de9cfda53191392467beb5a8e3b968d405.png)
![](http://docs.opencv.org/2.4/_images/math/785f83d75eae002bfe0f0eaab9e61c4bce453a2e.png)
![](http://docs.opencv.org/2.4/_images/math/68eb1e7879119380f2c66ac12d177ca3c0d2a4f4.png)
![](http://docs.opencv.org/2.4/_images/math/d5bc720f4370e483b317ddcf3040e11d0800b778.png)
![](http://docs.opencv.org/2.4/_images/math/d6f3970cdf54f4782f59fb96052d98df88731949.png)

### RGB <--> HSV
![](http://docs.opencv.org/2.4/_images/math/7be483aa0fb72e56fa54c7cc754c149c8c1c80b1.png)

![](http://docs.opencv.org/2.4/_images/math/75071d1d50b8ea1d3d0aa0530d5e848e5748666d.png)

![](http://docs.opencv.org/2.4/_images/math/9208f149119189c111d1250c1b628f452e68e4b2.png)

### RGB <--> HLS
![](http://docs.opencv.org/2.4/_images/math/c53957c2e14819ba58b2c36819265318560bafed.png)

![](http://docs.opencv.org/2.4/_images/math/4a775f57b71707b736edb37af1b945c7a59238a6.png)

![](http://docs.opencv.org/2.4/_images/math/2cc20c39cb81730800c53c0aee591ae1fa9c3eeb.png)

![](http://docs.opencv.org/2.4/_images/math/a9c8dafccf4d3869bf5c29be11d3da994f2cae7d.png)

![](http://docs.opencv.org/2.4/_images/math/009b2c865204c9e3a13ba53ee1e6a11f0a696623.png)

### RGB <--> CIE L*a*b*
![](http://docs.opencv.org/2.4/_images/math/0b40a48524601a0d685d08f6e99494dd2abca9cd.png)

![](http://docs.opencv.org/2.4/_images/math/f339c7a01c8c392d83d04dc3cde0627d0d5aee4e.png)

![](http://docs.opencv.org/2.4/_images/math/aa85b5b8031add20f0825aa37750dc8b8789aa7a.png)

![](http://docs.opencv.org/2.4/_images/math/45d31c15f8cc5532bd832c00bb99ff1dab790203.png)

![](http://docs.opencv.org/2.4/_images/math/3740b66fbff95aa9dfe9b005bd6ad7f28207992b.png)

![](http://docs.opencv.org/2.4/_images/math/f882025ffbd219a8826d69c8ecab6e436c5b0b44.png)

![](http://docs.opencv.org/2.4/_images/math/a15bb80fffbb76b76ea7869a4665f35ba2915461.png)

![](http://docs.opencv.org/2.4/_images/math/35fbc56624a7f26f4f1166946578f36449526b23.png)