#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

const std::string keys =
        "{help      |             | print this message    }"
        "{@image    |contours     | load image            }"
        "{building  |building.jpg | building image        }"
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
    if( file == "building" ){
        file = parser.get<std::string>("building");
    }else if(file == "contours"){
        file = parser.get<std::string>("contours");
    }
    srcImg = cv::imread(file, cv::IMREAD_COLOR );
    if( srcImg.empty() ){
        return -1;
    }


    cv::Mat grayImg, cannyImg;
    cv::cvtColor( srcImg, grayImg, cv::COLOR_BGR2GRAY );
    cv::Canny(grayImg, cannyImg, 50, 150, 3);

    cv::Mat houghImg, houghPImg, houghCImg;
    std::vector<cv::Vec2f> lines;
    cv::cvtColor( cannyImg, houghImg, cv::COLOR_GRAY2BGR );
    cv::cvtColor( cannyImg, houghPImg, cv::COLOR_GRAY2BGR );
    cv::cvtColor( cannyImg, houghCImg, cv::COLOR_GRAY2BGR );
    cv::HoughLines(cannyImg, lines, 1, CV_PI/180, 250, 0, 0 );

    for( size_t i = 0; i < lines.size(); i++ )
    {
        float rho = lines[i][0], theta = lines[i][1];
        cv::Point pt1, pt2;
        double a = std::cos(theta), b = std::sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        cv::line( houghImg, pt1, pt2, cv::Scalar(0,0,255), 3, cv::LINE_AA);
    }

    std::vector<cv::Vec4i> linesP;
    cv::HoughLinesP(cannyImg, linesP, 1, CV_PI/180, 50, 100, 5 );
    for( size_t i = 0; i < linesP.size(); i++ )
    {
        cv::Vec4i l = linesP[i];
        cv::line( houghPImg, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(255,0,0), 3, CV_AA);
    }

    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(grayImg, circles, cv::HOUGH_GRADIENT, 2, grayImg.rows/4, 200, 100 );
    for( size_t i = 0; i < circles.size(); i++ )
    {
        cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        circle( houghCImg, center, 3, cv::Scalar(0,255,0), -1, 8, 0 );
        circle( houghCImg, center, radius, cv::Scalar(0,0,255), 3, 8, 0 );
    }

    cv::imshow("source", srcImg);
    cv::imshow("canny image", cannyImg);
    cv::imshow("hough detected lines", houghImg);
    cv::imshow("hough detected circles", houghCImg);
    cv::imshow("hough P detected lines", houghPImg);
    cv::waitKey(0);


    return 0;
}
