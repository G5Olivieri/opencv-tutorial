#include <iostream>
#include <opencv2/opencv.hpp>

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

    cv::imshow("display windows", srcImg );
    cv::waitKey(0);

    return 0;
}
