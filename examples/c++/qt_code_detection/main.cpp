#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

const std::string keys =
        "{help      |           | print this message    }"
        "{@image    |contours   | load image            }"
        "{lena      |lena.jpg   | lena image            }"
        "{contours  |contours.png | contours image   }"
        ;


#define MinSize 100

bool chkInside()
{
    return true;
}

std::vector<std::vector<cv::Point>> chkCode(std::vector<std::vector<cv::Point>> candidates)
{
    std::vector<std::vector<cv::Point>> codeRect;
    int measurementError = 3;
    std::cout<<"---------------------"<<std::endl;
    for( int i = 0; i< candidates.size(); i++ )
    {
        for( int j = 0; j< candidates.size(); j++ )
        {

            cv::Point srcPt1 = candidates[i][0];
            cv::Point srcPt2 = candidates[i][1];
            cv::Point srcPt3 = candidates[i][2];
            cv::Point srcPt4 = candidates[i][3];

            cv::Point dstPt1 = candidates[j][0];
            cv::Point dstPt2 = candidates[j][1];
            cv::Point dstPt3 = candidates[j][2];
            cv::Point dstPt4 = candidates[j][3];

            double distancePt1 = cv::norm(srcPt1-dstPt1);
            double distancePt2 = cv::norm(srcPt2-dstPt2);
            double distancePt3 = cv::norm(srcPt3-dstPt3);
            double distancePt4 = cv::norm(srcPt4-dstPt4);
//            int distancePt2 = std::abs(srcPt2.x - dstPt2.x);
//            int distancePt3 = std::abs(srcPt3.x - dstPt3.x);
//            int distancePt4 = std::abs(srcPt4.x - dstPt4.x);

            if( std::abs( distancePt1 - distancePt3) < measurementError ){
                if(std::abs( distancePt1 - distancePt2) < measurementError){
                    if( std::abs( distancePt1 - distancePt4) < measurementError){
                        codeRect.push_back(candidates[i]);
                    }
                }
            }

//            std::cout<<"point1 x = "<<point1.x<<" , y = "<<point1.y<<std::endl;
//            std::cout<<"point2 x = "<<point2.x<<" , y = "<<point2.y<<std::endl;
//            std::cout<<"point3 x = "<<point3.x<<" , y = "<<point3.y<<std::endl;
//            std::cout<<"point4 x = "<<point4.x<<" , y = "<<point4.y<<std::endl;
        }
    }
    return codeRect;
}

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

    cv::VideoCapture capture(0);

    while(true)
    {
        capture >> srcImg;
        cv::Mat grayImg;
        cv::cvtColor( srcImg, grayImg, cv::COLOR_BGR2GRAY );

        cv::GaussianBlur(grayImg, grayImg,cv::Size(5,5),0);

        cv::Mat cannyImg;
        std::vector<std::vector<cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;

        cv::Canny( grayImg, cannyImg, 50, 100, 3 );
        cv::threshold( cannyImg, cannyImg, 50, 255, cv::THRESH_BINARY);
        cv::findContours( cannyImg, contours, hierarchy, cv::RETR_TREE , cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );

        cv::RNG rng(12345);
        cv::Mat drawing = cv::Mat::zeros( cannyImg.size(), CV_8UC3 );
        std::vector<cv::Point> approx;


        std::vector<std::vector<cv::Point>> candidates;
        for( int i = 0; i< contours.size(); i++ )
        {
            if( hierarchy[i][3] == -1 ){
                continue;
            }

            cv::approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true)*0.02, true);

            if (std::fabs(cv::contourArea(contours[i])) < MinSize || !cv::isContourConvex(approx))
                continue;

            if (approx.size() == 4 )
            {
                cv::Scalar color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
                cv::drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, cv::Point() );
                candidates.push_back(approx);
            }

        }
        std::vector<std::vector<cv::Point>> codeRect = chkCode(candidates);
        for( int i = 0; i < codeRect.size(); i++ )
        {
            for(int j = 0; j < codeRect[i].size()-1; j++)
                cv::line(srcImg, codeRect[i][j], codeRect[i][j+1], cv::Scalar(255,0,0), 3);
        }

        cv::imshow("drawImage", drawing);
        cv::imshow("grayImage", grayImg);
        cv::imshow("cannyImgImage", cannyImg);
        cv::imshow("srcImgImage", srcImg);

        cv::waitKey(30);
    }
    return 0;
}
