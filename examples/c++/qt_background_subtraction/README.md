# Background Subtraction Algorithm using OpenCV

切割背景與前景有初階的直接前景背景相減，但因為串流影像隨著時間的變化，光線會有變化，所以背景也必須不斷的學習更新才可應付大部分的環境，甚至還需要過濾不必要的風吹草動或陰影之類的雜訊。OpenCV 3版本以後提供了`MOG2`和`KNN`兩個API方便大家使用。

## MOG2 Background Subtraction (Gaussian Mixture)
- Z.Zivkovic, F. van der Heijden. "Improved adaptive Gausian mixture model for background subtraction" 2004.
- Z.Zivkovic, F. van der Heijden. “Efficient Adaptive Density Estimation per Image Pixel for the Task of Background Subtraction” 2006.

```c++
int history = 500;
double varThreshold = 16;
bool detectShadows = true ;
cv::Ptr<cv::BackgroundSubtractor> pMOG2;
pMOG2 = cv::createBackgroundSubtractorMOG2(history, varThreshold, detectShadows);

bool update_bg_model = true;
cv::Mat frame;
cv::Mat fgMOG2MaskImg, fgMOG2Img;
while(1)
{
    cap >> frame;
    if( frame.empty() ){
        break;
    }

    if( fgMOG2Img.empty() )
        fgMOG2Img.create(frame.size(), frame.type());

    //update the model
    pMOG2->apply(frame, fgMOG2MaskImg, update_bg_model ? -1 : 0);
    fgMOG2Img = cv::Scalar::all(0);
    frame.copyTo(fgMOG2Img, fgMOG2MaskImg);

    cv::Mat bgMOG2Img;
    pMOG2->getBackgroundImage(bgMOG2Img);

    cv::imshow("frame", frame);
    cv::imshow("MOG2 Foreground Mask", fgMOG2MaskImg);
    cv::imshow("MOG2 Foreground Image", fgMOG2Img);
    if(!bgMOG2Img.empty())
        cv::imshow("MOG2 Mean Background Image", bgMOG2Img );

    cv::waitKey(30);
}
```

**詳細Sample Code請參考[GitHub](https://github.com/MarcWang/opencv-tutorial/blob/master/examples/c%2B%2B/qt_background_subtraction/main.cpp)**

#### `Ptr<BackgroundSubtractorMOG2> createBackgroundSubtractorMOG2(int history=500, double varThreshold=16, bool detectShadows=true )`

- `history` 歷史參考禎數
- `varThreshold ` 更新的門檻值
- `detectShadows ` 是否要偵測陰影(如果開啟，mask的127值表示陰影)

#### `void apply(InputArray image, OutputArray fgmask, double learningRate=-1)`

- `image` 當下擷取的影像
- `fgmask` 計算後的背景影像
- `learningRate` 學習率

#### `void getBackgroundImage(OutputArray backgroundImage)`

- `backgroundImage` 取得目前建立的背景模型影像


## KNN Background Subtraction (K-nearest neigbours)


```c++
int history = 500;
double dist2Threshold = 400;
bool detectShadows = true ;
cv::Ptr<cv::BackgroundSubtractor> pKNN;
pKNN = cv::createBackgroundSubtractorKNN(history, dist2Threshold, detectShadows);


bool update_bg_model = true;
cv::Mat frame;
cv::Mat fgKNNMaskImg, fgKNNImg;
while(1)
{
    cap >> frame;
    if( frame.empty() ){
        break;
    }

    if( fgKNNImg.empty() )
        fgKNNImg.create(frame.size(), frame.type());


    //update the model
    pKNN->apply(frame, fgKNNMaskImg, update_bg_model ? -1 : 0);

    fgKNNImg = cv::Scalar::all(0);
    frame.copyTo(fgKNNImg, fgKNNMaskImg);

    cv::Mat bgKNNImg;
    pKNN->getBackgroundImage(bgKNNImg);


    cv::imshow("frame", frame);
    cv::imshow("KNN Foreground Mask", fgKNNMaskImg);
    cv::imshow("KNN Foreground Image", fgKNNImg);
    if(!fgKNNImg.empty())
        cv::imshow("KNN Mean Background Image", bgKNNImg );

    cv::waitKey(30);
}
```

**詳細Sample Code請參考[GitHub](https://github.com/MarcWang/opencv-tutorial/blob/master/examples/c%2B%2B/qt_background_subtraction/main.cpp)**

#### `Ptr<BackgroundSubtractorKNN> createBackgroundSubtractorKNN(int history=500, double dist2Threshold=400, bool detectShadows=true )`

- `history` 歷史參考禎數
- `dist2Threshold ` 更新的門檻值(平方距離)
- `detectShadows ` 是否要偵測陰影(如果開啟，mask的127值表示陰影)

#### `void apply(InputArray image, OutputArray fgmask, double learningRate=-1)`

- `image` 當下擷取的影像
- `fgmask` 計算後的背景影像
- `learningRate` 學習率

#### `void getBackgroundImage(OutputArray backgroundImage)`

- `backgroundImage` 取得目前建立的背景模型影像

**MOG**

An improved adaptive background mixture model for real-time tracking with shadow detection
 - P. KadewTraKuPong and R. Bowden in 2001

**MOG2**

Improved adaptive Gausian mixture model for background subtraction
 - Z.Zivkovic in 2004

Efficient Adaptive Density Estimation per Image Pixel for the Task of Background Subtraction
 - Z.Zivkovic in 2006


### 更多OpenCV文章請參考：[OpenCV Tutorial (學習筆記)](http://ccw1986.blogspot.tw/2013/09/learningopencv.html)

