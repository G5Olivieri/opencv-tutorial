
```c++
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace cv::ml;

const std::string keys =
        "{help      |           | print this message    }"
        "{@image    |lena       | load image            }"
        "{lena      |lena.jpg   | lena image            }"
        ;

int main(int argc, char *argv[])
{
    cv::CommandLineParser parser( argc, argv, keys);
    parser.about("Load image and display");
    if (parser.has("help")){
        parser.printMessage();
        return 0;
    }

    // Data for visual representation
    int width = 150, height = 200;
    Mat image = Mat::zeros(height, width, CV_8UC3);

    // Set up training data
    int labels[33] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    float trainingData[33][2] = {{30,155},{42,157},{32,159},{32,163},{48,163},{32,166},{45,167},{37,172},{53,172},{67,173},{45,174},{60,176},{50,177},{63,177},{58,180},{75,180},{58,183},{70,183},{63,156},{75,157},{68,160},{82,163},{70,165},{85,167},{92,169},{105,169},{80,172},{95,174},{90,176},{100,177},{105,180},{95,181},{113,184}};

    Mat trainingDataMat(33, 2, CV_32FC1, trainingData);
    Mat labelsMat(33, 1, CV_32SC1, labels);


    // Train the SVM
    Ptr<SVM> svm = SVM::create();
    svm->setType(SVM::C_SVC);
    svm->setKernel(SVM::LINEAR);
    svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
    svm->train(trainingDataMat, ROW_SAMPLE, labelsMat);

    // Show the decision regions given by the SVM
    Vec3b green(0,255,0), blue (255,0,0);
    for (int i = 0; i < image.rows; ++i)
        for (int j = 0; j < image.cols; ++j)
        {
            Mat sampleMat = (Mat_<float>(1,2) << j,i);
            float response = svm->predict(sampleMat);

            if (response == 1)
                image.at<Vec3b>(i,j)  = green;
            else if (response == -1)
                image.at<Vec3b>(i,j)  = blue;
        }

    // Show the training data
    int thickness = -1;
    int lineType = 8;
    for (int i = 0; i < trainingDataMat.rows; ++i){
        int x = (int)trainingDataMat.at<float>(i,0);
        int y = (int)trainingDataMat.at<float>(i,1);
        if( i >= 18 ){
            circle( image, Point(x,y), 2, Scalar(  0,   0,   0), thickness, lineType );
        }else{
            circle( image, Point(x,y), 2, Scalar(  255,   255,   255), thickness, lineType );
        }

    }

    cv::Mat dstImg;
    cv::resize(image, dstImg, cv::Size(450,600));
    cv::flip( dstImg, dstImg, 0);

    imwrite("result.png", dstImg);
    imshow("SVM Simple Example", dstImg);
    waitKey(0);

    return 0;
}

```

# SVM (Support Vector Machine)

機器學習(Machine Learning)
監督式學習(Supervised Learning)

分類(Classification)
回歸(Regression)



### 範例：

今天學校校長突然看到學生的體型越來越福泰，於是他找來3年2班的老師，以他們班的學生用校長自己的眼光判斷哪些人是胖是瘦(雖然現在有BMI依據)，班上同學有33個人，總共被分為2群(胖、不胖)。校長又找來資訊科的主任叫他寫出一個軟體，讓其他班級的老師輸入同學的身高、體重。希望電腦可以輸出結果顯示哪些同學在校長眼中是屬於胖的。

18位同學在校長眼中屬於不胖的，15同學是屬於胖的。

![](http://farm2.staticflickr.com/1707/25954134116_f643a7216a_b.jpg)

簡單來說就是希望找出可以切出2群資料的超平面(hyperplane)，一般來說可以找到多個，但哪一個才是最佳的超平面呢?

超平面應與兩群資料的邊界(margin)距離越大越好。

![](http://farm2.staticflickr.com/1475/25679483150_aa3c8f9312_b.jpg)

### train data

CV_32FC1 浮點數型態


### svmType

- SVM::C_SVC (100)
- SVM::NU_SVC (101)
- SVM::ONE_CLASS (102)
- SVM::EPS_SVR (103)
- SVM::NU_SVR (104)

SVC代表分類(Classification)，SVR代表回歸(Regression)

#### SVM::C_SVC

(C-Support Vector Classification)
n-class classification
C表示懲罰因子，C越大表示對錯誤分類的懲罰
C類支持向量分類機。 n類分組  (n >= 2)，允許用異常值懲罰因子C進行不完全分類。

C = (1~)

#### SVM::NU_SVC

(nu-Support Vector Classification) 
nu類支持向量分類機。n類似然不完全分類的分類器，参數为nu 取代C（其值在區間【0，1】中，nu越大，决策邊界越平滑）。

C = (0~1)

#### SVM::ONE_CLASS

(Distribution Estimation) 

單分類器，所有的訓練數據提取自同一個類裏，然後SVM建立了一個分界線以分割該類在特征空間中所占區域和其它類在特征空間中所占區域。

#### SVM::EPS_SVR

(epsilon-Support Vector Regression) 
epsilon類支持向量回歸機。訓練集中的特征向量和擬合出來的超平面的距離需要小於p。異常值懲罰因子C被采用。

`p`這個參數必須大於0 ，可透過`SVM::setP(value)`設定，否則會出現`The parameter p must be positive`的錯誤訊息。

#### SVM::NU_SVR

(nu-Support Vector Regression)
nu類支持向量回歸機。 nu代替了p。



### KernelTypes 

- SVM::CUSTOM (-1)
- SVM::LINEAR (0)
- SVM::POLY (1)
- SVM::RBF (2)
- SVM::SIGMOID (3)
- SVM::CHI2 (4)
- SVM::INTER (5)


#### SVM::LINEAR

線性內核。沒有任何向映射至高維空間，線性區分（或回歸）在原始特征空間中被完成
d(x,y) = x•y == (x,y)

#### SVM::POLY

多項式內核 
d(x,y) = (gamma*(x•y)+coef0)degree

#### SVM::RBF

Radial basis function (RBF), a good choice in most cases
基於徑向的函數，對於大多數情況都是一個較好的選擇
d(x,y) = exp(-gamma*|x-y|2)

#### SVM::SIGMOID

Sigmoid函數內核
d(x,y) = tanh(gamma*(x•y)+coef0)

#### SVM::CHI2


### degree

內核函數 (default 0) (POLY)

### gamma

內核函數 (default 1)(POLY / RBF / SIGMOID / CHI2)

### coef0

內核函數 (default 0)(POLY / SIGMOID)

### p

Set the epsilon in loss function of epsilon-SVR (default 0)(EPS_SVR)

### C

Set the parameter C of C-SVC, epsilon-SVR, and nu-SVR (default 1)(C_SVC / EPS_SVR / NU_SVR)

### nu

set the parameter nu of nu-SVC, one-class SVM, and nu-SVR (default 0)(NU_SVC / ONE_CLASS / NU_SVR)

### classWeights

可選權重，賦給指定的類別。一般乘以C以後去影響不同類別的錯誤分類懲罰項。權重越大，某一類別的誤分類數據的懲罰項就越大。

### termCrit

SVM的迭代訓練過程的中止條件，解决部分受約束二次最優問題。















[A tutorial on support vector machines for pattern recognition](http://www.svms.org/tutorials/Burges1998.pdf)
[LIBSVM: A Library for Support Vector Machines](http://www.csie.ntu.edu.tw/~cjlin/papers/libsvm.pdf)