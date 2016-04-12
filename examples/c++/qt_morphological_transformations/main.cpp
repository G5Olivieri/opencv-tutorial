#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

const std::string keys =
        "{help      |             | print this message    }"
        "{@image    |j            | load image            }"
        "{j         |j.png        | j image        }"
        "{contours  |contours.png | contours image        }"
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
    if( file == "j" ){
        file = parser.get<std::string>("j");
    }else if(file == "contours"){
        file = parser.get<std::string>("contours");
    }
    srcImg = cv::imread(file, cv::IMREAD_COLOR );
    if( srcImg.empty() ){
        return -1;
    }

    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));

    cv::Mat dilateImg;
    cv::dilate(srcImg, dilateImg, element, cv::Point(-1,-1), 1);

    cv::Mat erodeImg;
    cv::erode(srcImg, erodeImg, element, cv::Point(-1,-1), 1);

    cv::Mat closeImg;
    cv::morphologyEx( srcImg, closeImg, cv::MORPH_CLOSE, element);

    cv::Mat openImg;
    cv::morphologyEx( srcImg, openImg, cv::MORPH_OPEN, element);

    cv::imshow("Source",srcImg);
    cv::imshow("Dilation", dilateImg);
    cv::imshow("Erodsion", erodeImg);
    cv::imshow("Close", closeImg);
    cv::imshow("Open", openImg);
    cv::waitKey(0);


    return 0;
}
