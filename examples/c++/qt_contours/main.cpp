#include <iostream>
#include <opencv2/opencv.hpp>

const std::string keys =
        "{help      |           | print this message    }"
        "{@image    |contours   | load image            }"
        "{lena      |lena.jpg   | lena image            }"
        "{contours  |contours.png | contours image   }"
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
    }else if( file == "contours" ){
        file = parser.get<std::string>("contours");
    }
    srcImg = cv::imread(file, cv::IMREAD_COLOR );
    if( srcImg.empty() ){
        return -1;
    }


    cv::Mat grayImg;
    cv::cvtColor( srcImg, grayImg, cv::COLOR_BGR2GRAY );


    cv::waitKey(0);


    return 0;
}
