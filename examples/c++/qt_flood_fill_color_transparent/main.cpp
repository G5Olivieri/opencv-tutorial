#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>
#include "LiquifyProcess.h"

const std::string keys =
        "{help      |           | print this message    }"
        "{@image    |shape       | load image            }"
        "{shape     |shape.png   | shape image            }"
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
    if( file == "shape" ){
        file = parser.get<std::string>("shape");
    }

    srcImg = cv::imread(file, cv::IMREAD_COLOR );
    if( srcImg.empty() ){
        return -1;
    }

    LiquifyProcess liquifyProc;

    std::vector<cv::Point> blueRegions = std::vector<cv::Point>();
    blueRegions.push_back(cv::Point(300,200));
    blueRegions.push_back(cv::Point(1000,410));

    std::vector<cv::Point> redRegions = std::vector<cv::Point>();
    redRegions.push_back(cv::Point(650,240));
    redRegions.push_back(cv::Point(1050,200));

    std::vector<cv::Point> greenRegions = std::vector<cv::Point>();
    greenRegions.push_back(cv::Point(300,550));
    greenRegions.push_back(cv::Point(600,550));
    greenRegions.push_back(cv::Point(750,550));

    cv::Scalar BlueColor = cv::Scalar(255,0,0);
    cv::Scalar RedColor = cv::Scalar(0,0,255);
    cv::Scalar GreenColor = cv::Scalar(0,255,0);

    liquifyProc.process(srcImg, blueRegions, BlueColor);
    liquifyProc.process(srcImg, redRegions, RedColor);
    liquifyProc.process(srcImg, greenRegions, GreenColor);

    cv::Mat dstMat = liquifyProc.toTransparent(srcImg, cv::Point(1,100));
    cv::imwrite("source.png", srcImg);
    cv::imwrite("transparent.png", dstMat);

    cv::imshow("Display Windows", srcImg );
    cv::imshow("Display Transparent Windows", dstMat );
    cv::waitKey(0);

    return 0;
}
