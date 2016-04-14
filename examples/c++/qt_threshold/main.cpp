#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

const std::string keys =
        "{help      |             | print this message    }"
        "{@image    |level        | load image            }"
        "{level     |level.jpg    | level image           }"
        ;


int main(int argc, char *argv[])
{
    cv::CommandLineParser parser( argc, argv, keys);
    parser.about("");
    if (parser.has("help")){
        parser.printMessage();
        return 0;
    }

    cv::Mat srcImg;
    std::string file = parser.get<std::string>(0);
    if( file == "lena" ){
        file = parser.get<std::string>("lena");
    }else if(file == "level"){
        file = parser.get<std::string>("level");
    }
    srcImg = cv::imread(file, cv::IMREAD_COLOR );
    if( srcImg.empty() ){
        return -1;
    }

    cv::Mat grayImg;
    cv::cvtColor(srcImg, grayImg, cv::COLOR_BGR2GRAY);

    cv::Mat binImg, binInvImg, truncImg, tozeroImg, tozeroInvImg, otsuImg, trianImg;
    cv::Mat adapMaenImg, adapGaussianImg;

    double th = 127, maxVal = 255;
    cv::threshold( grayImg, binImg, th, maxVal, cv::THRESH_BINARY );
    cv::threshold( grayImg, binInvImg, th, maxVal, cv::THRESH_BINARY_INV );
    cv::threshold( grayImg, truncImg, th, maxVal, cv::THRESH_TRUNC );
    cv::threshold( grayImg, tozeroImg, th, maxVal, cv::THRESH_TOZERO );
    cv::threshold( grayImg, tozeroInvImg, th, maxVal, cv::THRESH_TOZERO_INV );
    cv::threshold( grayImg, trianImg, th, maxVal, cv::THRESH_TRIANGLE );
    cv::threshold( grayImg, otsuImg, 0, maxVal, cv::THRESH_BINARY+cv::THRESH_OTSU );

    cv::adaptiveThreshold( grayImg, adapMaenImg, maxVal, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 5, 2 );
    cv::adaptiveThreshold( grayImg, adapGaussianImg, maxVal, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 5, 2 );

    cv::imshow("Original", grayImg);

//    cv::imshow("THRESH_BINARY", binImg);
//    cv::imshow("THRESH_BINARY_INV", binInvImg);
//    cv::imshow("THRESH_TRUNC", truncImg);
//    cv::imshow("THRESH_TOZERO", tozeroImg);
//    cv::imshow("THRESH_TOZERO_INV", tozeroInvImg);
//    cv::imshow("THRESH_TRIANGLE", trianImg);
//    cv::imshow("THRESH_OTSU", otsuImg);
    cv::imshow("ADAPTIVE_THRESH_MEAN_C", adapMaenImg);
    cv::imshow("ADAPTIVE_THRESH_GAUSSIAN_C", adapGaussianImg);

    cv::waitKey(0);


    return 0;
}
