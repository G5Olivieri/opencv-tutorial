#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>


const std::string keys =
        "{help      |         | print this message   }"
        "{@source   |camera   | camera or video source(./video/test.avi)   }"
        "{camera    |0        | camera index for prediction    }"
        ;

int main(int argc, char *argv[])
{
    cv::CommandLineParser parser( argc, argv, keys);
    parser.about("Background Subtraction");
    if (parser.has("help")){
        parser.printMessage();
        return 0;
    }

    cv::VideoCapture cap;
    std::string mediaSrc = parser.get<std::string>(0);
    if( mediaSrc == "camera" ){
        int camIdx = parser.get<int>("camera");
        cap.open(camIdx);
    }else{
        cap.open(mediaSrc);
    }


    int history = 500;
    double dist2Threshold = 400;
    double varThreshold = 16;
    bool detectShadows = true ;
    cv::Ptr<cv::BackgroundSubtractor> pMOG2, pKNN;
    pMOG2 = cv::createBackgroundSubtractorMOG2(history, varThreshold, detectShadows);
    pKNN = cv::createBackgroundSubtractorKNN(history, dist2Threshold, detectShadows);

    bool update_bg_model = true;
    cv::Mat frame;
    cv::Mat fgMOG2MaskImg, fgMOG2Img;
    cv::Mat fgKNNMaskImg, fgKNNImg;
    while(1)
    {
        cap >> frame;
        if( frame.empty() ){
            break;
        }

        if( fgMOG2Img.empty() )
            fgMOG2Img.create(frame.size(), frame.type());
        if( fgKNNImg.empty() )
            fgKNNImg.create(frame.size(), frame.type());


        //update the model
        pMOG2->apply(frame, fgMOG2MaskImg, update_bg_model ? -1 : 0);
        pKNN->apply(frame, fgKNNMaskImg, update_bg_model ? -1 : 0);

        fgMOG2Img = cv::Scalar::all(0);
        fgKNNImg = cv::Scalar::all(0);

        frame.copyTo(fgMOG2Img, fgMOG2MaskImg);
        frame.copyTo(fgKNNImg, fgKNNMaskImg);

        cv::Mat bgMOG2Img, bgKNNImg;
        pMOG2->getBackgroundImage(bgMOG2Img);
        pKNN->getBackgroundImage(bgKNNImg);


        cv::imshow("frame", frame);
        cv::imshow("MOG2 Foreground Mask", fgMOG2MaskImg);
        cv::imshow("KNN Foreground Mask", fgKNNMaskImg);

        cv::imshow("MOG2 Foreground Image", fgMOG2Img);
        cv::imshow("KNN Foreground Image", fgKNNImg);

        if(!bgMOG2Img.empty())
            cv::imshow("MOG2 Mean Background Image", bgMOG2Img );
        if(!fgKNNImg.empty())
            cv::imshow("KNN Mean Background Image", bgKNNImg );

        cv::waitKey(30);
    }

    return 0;
}
