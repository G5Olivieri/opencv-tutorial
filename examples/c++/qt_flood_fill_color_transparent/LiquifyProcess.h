#ifndef LIQUIFYPROCESS_H
#define LIQUIFYPROCESS_H
#include "opencv2/opencv.hpp"

class LiquifyProcess
{
public:
    LiquifyProcess();

    void process(cv::Mat srcMat, std::vector<cv::Point> regions, cv::Scalar color);
};

#endif // LIQUIFYPROCESS_H
