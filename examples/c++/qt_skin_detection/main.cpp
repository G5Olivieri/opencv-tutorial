#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace cv;

const std::string keys =
        "{help      |           | print this message    }"
        "{@image    |ann        | load image            }"
        "{lena      |lena.jpg   | lena image            }"
        "{ann       |ann.jpg    | ann image             }"
        "{patty     |patty.jpg  | patty image           }"
        ;

cv::Mat convertBGR2YCrCb( cv::Mat srcMat )
{
    cv::Mat dstMat( srcMat.rows, srcMat.cols, srcMat.type() );
    int nChannels = srcMat.channels();
    int nRows = srcMat.rows;
    int nCols = srcMat.cols * nChannels;
    int nStep = (int)srcMat.step;

    uchar* srcData= srcMat.data;
    uchar* dstData = dstMat.data;
    for( int j = 0; j < nRows; j++ ){
        for( int i = 0; i < nCols; i+= nChannels ) {
            uchar b = *(srcData+i+0);
            uchar g = *(srcData+i+1);
            uchar r = *(srcData+i+2);
            uchar y = (uchar)(0.299*r+0.587*g+0.114*b);
            uchar cr = (uchar)((r-y)*0.713+128);
            uchar cb = (uchar)((b-y)*0.564+128);

            if( 80 <= y && (135 <= cr && cr <= 180) && (85 <= cb && cb <= 135 )){
                *(dstData+i+0) = 255;
                *(dstData+i+1) = 255;
                *(dstData+i+2) = 255;
            }else{
                *(dstData+i+0) = 0;
                *(dstData+i+1) = 0;
                *(dstData+i+2) = 0;
            }

        }
        srcData += nStep;
        dstData += nStep;
    }
    return dstMat;
}

cv::Mat convertBGR2HSV( cv::Mat srcMat )
{
    cv::Mat dstMat( srcMat.rows, srcMat.cols, srcMat.type() );
    int nChannels = srcMat.channels();
    int nRows = srcMat.rows;
    int nCols = srcMat.cols * nChannels;
    int nStep = (int)srcMat.step;

    uchar* srcData= srcMat.data;
    uchar* dstData = dstMat.data;
    for( int j = 0; j < nRows; j++ ){
        for( int i = 0; i < nCols; i+= nChannels ) {
            float b = *(srcData+i+0);
            float g = *(srcData+i+1);
            float r = *(srcData+i+2);

            float vmax = std::max(r,g);
            vmax = std::max(vmax, b);

            float vmin = std::min(r,g);
            vmin = std::min(vmin, b);

            float diff = vmax - vmin;
            float h, s, v = vmax;

            if( vmax != 0 ){
//                s = diff / vmax;
                s = diff/(float)(fabs(vmax) + FLT_EPSILON);
                diff = (float)(60./(diff + FLT_EPSILON));
            }
            else{
                s = 0;
                h = -1;
            }

            if( vmax == r )
                h = (g - b)*diff;
            else if( vmax == g )
                h = (b - r)*diff + 120.f;
            else
                h = (r - g)*diff + 240.f;

            if( h < 0 ) h += 360.f;

            *(dstData+i+0) = (uchar)(h*60*0.708);
            *(dstData+i+1) = (uchar)(s*255);
            *(dstData+i+2) = (uchar)(v);

        }
        srcData += nStep;
        dstData += nStep;
    }
    return dstMat;
}


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
    }else if( file == "ann" ){
        file = parser.get<std::string>("ann");
    }else if( file == "patty" ){
        file = parser.get<std::string>("patty");
    }
    srcImg = cv::imread(file, cv::IMREAD_COLOR );
    if( srcImg.empty() ){
        return -1;
    }

    cv::Mat dstImg = convertBGR2HSV(srcImg);

    cv::Mat bgr2hsvImg, hsv2skinImg;
    cv::cvtColor(srcImg, bgr2hsvImg, cv::COLOR_BGR2HSV);
    cv::inRange(bgr2hsvImg, cv::Scalar(0,40,0), cv::Scalar(35,174,255), hsv2skinImg);

    cv::Mat bgr2ycrcbImg, ycrcb2skinImg;
    cv::cvtColor( srcImg, bgr2ycrcbImg, cv::COLOR_BGR2YCrCb );
    cv::inRange( bgr2ycrcbImg, cv::Scalar(80, 135, 85), cv::Scalar(255, 180, 135), ycrcb2skinImg );


    cv::imshow("Display Window", srcImg);
    cv::imshow("Display HSV Window", bgr2hsvImg);
    cv::imshow("Display YCrCb Window", bgr2ycrcbImg);
    cv::imshow("Display HSV Skin Window", hsv2skinImg);
    cv::imshow("Display YCrCb Skin Window", ycrcb2skinImg);
    cv::waitKey(0);


    return 0;
}
