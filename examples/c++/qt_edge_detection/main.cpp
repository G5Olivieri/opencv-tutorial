#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>


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

    cv::Mat srcImg;
    std::string file = parser.get<std::string>(0);
    if( file == "lena" ){
        file = parser.get<std::string>("lena");
    }

    srcImg = cv::imread(file, cv::IMREAD_COLOR );
    if( srcImg.empty() ){
        return -1;
    }


    cv::Mat grayImg;
    cv::cvtColor( srcImg, grayImg, cv::COLOR_BGR2GRAY );


    cv::Mat cannyImg;
    double minThreshold = 50;
    double maxThreshold = 150;
    int apertureSize = 3;
    bool L2gradient = false;
    cv::Canny( grayImg, cannyImg, minThreshold, maxThreshold, apertureSize, L2gradient );



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

    cv::Mat laplacianImg, grad_16S;
    cv::Laplacian( grayImg, grad_16S, CV_16S, 3, 1, 0, cv::BORDER_DEFAULT);
    cv::convertScaleAbs( grad_16S, laplacianImg );



    cv::imshow("Display Windows", srcImg );
    cv::imshow("Display Canny Windows", cannyImg );
    cv::imshow("Display Sobel Windows", sobelImg );
    cv::imshow("Display Laplacian Windows", laplacianImg );
    cv::waitKey(0);

    return 0;
}
