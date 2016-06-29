#include "LiquifyProcess.h"

LiquifyProcess::LiquifyProcess()
{

}

void LiquifyProcess::process(cv::Mat srcMat, std::vector<cv::Point> regions, cv::Scalar color)
{
    for( int i = 0; i < regions.size(); i++){
        cv::floodFill(srcMat, regions[i], color);
    }
}
