#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

const std::string keys =
        "{help      |             | print this message    }"
        "{@image    |contours     | load image            }"
        "{j         |j.png        | j image        }"
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
    if( file == "j" ){
        file = parser.get<std::string>("j");
    }else if(file == "contours"){
        file = parser.get<std::string>("contours");
    }
    srcImg = cv::imread(file, cv::IMREAD_COLOR );
    if( srcImg.empty() ){
        return -1;
    }

    cv::Mat grayImg;
    cv::cvtColor(srcImg, grayImg, cv::COLOR_BGR2GRAY);

    int threshval = 100;
    cv::Mat binaryImg = threshval < 128 ? (grayImg < threshval) : (grayImg > threshval);
    cv::Mat labelImage;
    cv::Mat stats, centroids;
//    int nLabels = cv::connectedComponents(bw, labelImage, 8);
    int nLabels = cv::connectedComponentsWithStats(binaryImg, labelImage, stats, centroids, 8, CV_32S);
    std::vector<cv::Vec3b> colors(nLabels);
    colors[0] = cv::Vec3b(0, 0, 0);
    std::cout << "Number of connected components = " << nLabels << std::endl << std::endl;

    for(int label = 1; label < nLabels; ++label){
        colors[label] = cv::Vec3b( (std::rand()&255), (std::rand()&255), (std::rand()&255) );
        std::cout << "Component "<< label << std::endl;
        std::cout << "CC_STAT_LEFT   = " << stats.at<int>(label,cv::CC_STAT_LEFT) << std::endl;
        std::cout << "CC_STAT_TOP    = " << stats.at<int>(label,cv::CC_STAT_TOP) << std::endl;
        std::cout << "CC_STAT_WIDTH  = " << stats.at<int>(label,cv::CC_STAT_WIDTH) << std::endl;
        std::cout << "CC_STAT_HEIGHT = " << stats.at<int>(label,cv::CC_STAT_HEIGHT) << std::endl;
        std::cout << "CC_STAT_AREA   = " << stats.at<int>(label,cv::CC_STAT_AREA) << std::endl;
        std::cout << "CENTER   = (" << centroids.at<double>(label, 0) <<","<< centroids.at<double>(label, 1) << ")"<< std::endl << std::endl;
    }
    cv::Mat dst(grayImg.size(), CV_8UC3);
    for(int r = 0; r < dst.rows; ++r){
        for(int c = 0; c < dst.cols; ++c){
            int label = labelImage.at<int>(r, c);
            cv::Vec3b &pixel = dst.at<cv::Vec3b>(r, c);
            pixel = colors[label];
        }
    }

    cv::imshow( "Source", srcImg );
    cv::imshow( "Connected Components", dst );


    cv::waitKey(0);


    return 0;
}
