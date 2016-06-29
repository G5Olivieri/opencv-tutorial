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

cv::Mat LiquifyProcess::toTransparent(cv::Mat srcMat, cv::Point bgPoint)
{
    cv::Mat dstMat( srcMat.rows, srcMat.cols, CV_8UC4 );
    int nChannels = srcMat.channels();
    int nDstChannels = dstMat.channels();
    int nRows = srcMat.rows;
    int nCols = srcMat.cols;


    cv::Vec3b pixel = srcMat.at<cv::Vec3b>(bgPoint.y, bgPoint.x);
    int blue = pixel[0];
    int green = pixel[1];
    int red = pixel[2];

    for( int j = 0; j < nRows; j++ ) {
        uchar* srcData = srcMat.ptr<uchar>(j);
        uchar* dstData = dstMat.ptr<uchar>(j);
        for( int i = 0; i < nCols; i++) {
            dstData[nDstChannels*i + 0] = srcData[nChannels*i + 0];
            dstData[nDstChannels*i + 1] = srcData[nChannels*i + 1];
            dstData[nDstChannels*i + 2] = srcData[nChannels*i + 2];
            if( (srcData[nChannels*i + 0] == blue) && (srcData[nChannels*i + 1] == green) && (srcData[nChannels*i + 2] == red)){
                dstData[nDstChannels*i + 3] = 0;
            }else{
                dstData[nDstChannels*i + 3] = 255;
            }
        }
    }
    return dstMat;
}
