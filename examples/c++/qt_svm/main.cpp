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
            circle(	image, Point(x,y), 2, Scalar(  0,   0,   0), thickness, lineType );
        }else{
            circle(	image, Point(x,y), 2, Scalar(  255,   255,   255), thickness, lineType );
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
