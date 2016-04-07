#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

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

    cv::Mat cannyImg;
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::Canny( grayImg, cannyImg, 50, 100, 3 );
    cv::findContours( cannyImg, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );

    cv::RNG rng(12345);
    cv::Mat drawing = cv::Mat::zeros( cannyImg.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ )
    {
        cv::Scalar color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        cv::drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, cv::Point() );
    }

    cv::imshow( "Display Window", srcImg );
    cv::imshow( "Canny Image", cannyImg );
    cv::imshow( "Contours", drawing );

    cv::waitKey(0);


    return 0;
}
