#ifndef LIQUIFYPROCESS_H
#define LIQUIFYPROCESS_H
#include "opencv2/opencv.hpp"

class LiquifyProcess
{
public:
    LiquifyProcess();

    void process(cv::Mat srcMat, std::vector<cv::Point> regions, cv::Scalar color);
    cv::Mat toTransparent(cv::Mat srcMat, cv::Point bgPoint);
};

#endif // LIQUIFYPROCESS_H
