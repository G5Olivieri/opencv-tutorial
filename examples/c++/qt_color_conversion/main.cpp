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

    cv::Mat srcImg = cv::imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
    cv::Mat resizeImg;
    cv::resize(srcImg, resizeImg, cv::Size(srcImg.cols/2, srcImg.rows/2));
    cv::imshow("BGR Color Space", resizeImg);

    //BGR to RGB Color Space
    cv::Mat bgr2rgbImg, rgb2bgrImg;
    cv::cvtColor(resizeImg, bgr2rgbImg, cv::COLOR_BGR2RGB);
    cv::cvtColor(bgr2rgbImg, rgb2bgrImg, cv::COLOR_RGB2BGR);
    cv::imshow("RGB Color Space", bgr2rgbImg);

    //BGR to Gray Color Space
    cv::Mat bgr2grayImg;
    cv::cvtColor(resizeImg, bgr2grayImg, cv::COLOR_BGR2GRAY);
    cv::imshow("Gray Color Space", bgr2grayImg);

    //BGR to HSV Color Space
    cv::Mat bgr2hsvImg, hsv2bgrImg;
    cv::cvtColor(resizeImg, bgr2hsvImg, cv::COLOR_BGR2HSV);
    cv::cvtColor(bgr2hsvImg, hsv2bgrImg, cv::COLOR_HSV2BGR);
    cv::imshow("HSV Color Space", bgr2hsvImg);

    //BGR to YCbCr Color Space
    cv::Mat bgr2ycrcbImg, ycrcb2bgrImg;
    cv::cvtColor(resizeImg, bgr2ycrcbImg, cv::COLOR_BGR2YCrCb);
    cv::cvtColor(bgr2ycrcbImg, ycrcb2bgrImg, cv::COLOR_YCrCb2BGR);
    cv::imshow("YCrCb Color Space", bgr2ycrcbImg);

    //BGR to CIE Lab Color Space
    cv::Mat bgr2labImg,lab2bgrImg;
    cv::cvtColor(resizeImg, bgr2labImg, cv::COLOR_BGR2Lab);
    cv::cvtColor(bgr2labImg, lab2bgrImg, cv::COLOR_Lab2BGR);
    cv::imshow("Lab Color Space", bgr2labImg);

    //BGR to HLS Color Space
    cv::Mat bgr2hlsImg, hls2bgrImg;
    cv::cvtColor(resizeImg, bgr2hlsImg, cv::COLOR_BGR2HLS);
    cv::cvtColor(bgr2hlsImg, hls2bgrImg, cv::COLOR_HLS2BGR);
    cv::imshow("HLS Color Space", bgr2hlsImg);

    //BGR to XYZ Color Space
    cv::Mat bgr2xyzImg, xyz2bgrImg;
    cv::cvtColor(resizeImg, bgr2xyzImg, cv::COLOR_BGR2XYZ);
    cv::cvtColor(bgr2xyzImg, xyz2bgrImg, cv::COLOR_XYZ2BGR);
    cv::imshow("XYZ Color Space", bgr2xyzImg);

    cv::waitKey(0);

    return 0;
}
