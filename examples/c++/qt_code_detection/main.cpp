#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

const std::string keys =
        "{help      |           | print this message    }"
        "{@image    |qrcode     | load image            }"
        "{lena      |lena.jpg   | lena image            }"
        "{contours  |contours.png | contours image      }"
        "{qrcode    |qrcode.jpg |  qr code              }"
        ;


#define MinSize 100

struct CodeMap
{
    std::vector<cv::Point> outside;
    std::vector<cv::Point> inside;
    cv::Point center;
};

cv::Point calCenterPoint(std::vector<cv::Point> rect)
{
    cv::Point centerPt;
    int x = 0, y = 0;
    for( int i = 0; i< rect.size(); i++ )
    {
        x += rect[i].x;
        y += rect[i].y;
    }
    centerPt.x = x/4;
    centerPt.y = y/4;
    return centerPt;
}

std::vector<CodeMap> chkCode(std::vector<std::vector<cv::Point>> candidates, int threshold)
{

    std::vector<CodeMap> codeRect;
    int measurementError = 3;
    std::cout<<"---------------------"<<std::endl;
    for( int i = 0; i< candidates.size(); i++ )
    {
        for( int j = i; j< candidates.size(); j++ )
        {
            if( i == j )
                continue;
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

            if( std::abs( distancePt1 - distancePt3) < measurementError && distancePt3 < threshold){
                if(std::abs( distancePt1 - distancePt2) < measurementError && distancePt2 < threshold){
                    if( std::abs( distancePt1 - distancePt4) < measurementError && distancePt4 < threshold){
                        CodeMap codeMap;
                        codeMap.outside = candidates[j];
                        codeMap.inside = candidates[i];
                        codeMap.center = calCenterPoint(candidates[i]);
                        codeRect.push_back(codeMap);
                    }
                }
            }
        }
    }
    return codeRect;
}

bool isRectangle(cv::Point pt1, cv::Point pt2,cv::Point pt3,cv::Point pt4)
{

    double cx,cy;
    double dd1,dd2,dd3,dd4;

    cx=(pt1.x+pt2.x+pt3.x+pt4.x)/4;
    cy=(pt1.y+pt2.y+pt3.y+pt4.y)/4;

    dd1=std::abs(cx-pt1.x)+std::abs(cy-pt1.y);
    dd2=std::abs(cx-pt2.x)+std::abs(cy-pt2.y);
    dd3=std::abs(cx-pt3.x)+std::abs(cy-pt3.y);
    dd4=std::abs(cx-pt4.x)+std::abs(cy-pt4.y);
    return dd1==dd2 && dd1==dd3 && dd1==dd4;
}


//bool isRectangle(double x1, double y1,
//                 double x2, double y2,
//                 double x3, double y3,
//                 double x4, double y4)
//{
//    double cx,cy;
//    double dd1,dd2,dd3,dd4;

//    cx=(x1+x2+x3+x4)/4;
//    cy=(y1+y2+y3+y4)/4;

//    dd1=std::abs(cx-x1)+std::abs(cy-y1);
//    dd2=std::abs(cx-x2)+std::abs(cy-y2);
//    dd3=std::abs(cx-x3)+std::abs(cy-y3);
//    dd4=std::abs(cx-x4)+std::abs(cy-y4);
//    return dd1==dd2 && dd1==dd3 && dd1==dd4;
//}

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
    }else if( file == "qrcode" ){
        file = parser.get<std::string>("qrcode");
    }
    srcImg = cv::imread(file, cv::IMREAD_COLOR );
    if( srcImg.empty() ){
        return -1;
    }

//    cv::VideoCapture capture(0);

//    while(true)
//    {
//        capture >> srcImg;
        cv::Mat grayImg;
        cv::cvtColor( srcImg, grayImg, cv::COLOR_BGR2GRAY );

//        cv::GaussianBlur(grayImg, grayImg,cv::Size(5,5),0);

        cv::Mat cannyImg;
        std::vector<std::vector<cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;

        cv::Canny( grayImg, cannyImg, 50, 100, 3 );
//        cv::threshold( cannyImg, cannyImg, 50, 255, cv::THRESH_BINARY);
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
        int thresholdBound = 30;
        std::vector<CodeMap> codeRect = chkCode(candidates, thresholdBound);

        for( int i = 0; i < codeRect.size(); i++ )
        {
            cv::Scalar color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
            cv::line(srcImg, codeRect[i].outside[0], codeRect[i].outside[1], color, 3);
            cv::line(srcImg, codeRect[i].outside[1], codeRect[i].outside[2], color, 3);
            cv::line(srcImg, codeRect[i].outside[2], codeRect[i].outside[3], color, 3);
            cv::line(srcImg, codeRect[i].outside[3], codeRect[i].outside[0], color, 3);

//            cv::line(srcImg, codeRect[i].inside[0], codeRect[i].inside[1], color, 3);
//            cv::line(srcImg, codeRect[i].inside[1], codeRect[i].inside[2], color, 3);
//            cv::line(srcImg, codeRect[i].inside[2], codeRect[i].inside[3], color, 3);
//            cv::line(srcImg, codeRect[i].inside[3], codeRect[i].inside[0], color, 3);

            cv::circle(srcImg, codeRect[i].center, 3, color, 3);
        }

        bool result = false;
        for( int i = 0; i < codeRect.size(); i++ )
        {
            if( result ) break;
            for( int j = i; j < codeRect.size(); j++ )
            {
                if( result ) break;
                for( int k = j; k < codeRect.size(); k++ )
                {
                    if( result ) break;
                    for( int l = k; l < codeRect.size(); l++ )
                    {
                        if( result ) break;
                        if(i==j||j==k||k==l)
                            continue;
                        if( codeRect[i].center == codeRect[j].center || codeRect[j].center == codeRect[k].center ||codeRect[k].center == codeRect[l].center)
                            continue;

                        result = isRectangle(codeRect[i].center, codeRect[j].center, codeRect[k].center, codeRect[l].center);
                        if( result ){
                            std::cout<<"-------------------------------------"<<std::endl;
                            std::cout<<codeRect[i].center.x<<","<<codeRect[i].center.y<<std::endl;
                            std::cout<<codeRect[j].center.x<<","<<codeRect[j].center.y<<std::endl;
                            std::cout<<codeRect[k].center.x<<","<<codeRect[k].center.y<<std::endl;
                            std::cout<<codeRect[l].center.x<<","<<codeRect[l].center.y<<std::endl;
                        }
                    }
                }
            }
//            std::cout<<i<<std::endl;
        }

        cv::imshow("drawImage", drawing);
//        cv::imshow("grayImage", grayImg);
//        cv::imshow("cannyImgImage", cannyImg);
        cv::imshow("srcImgImage", srcImg);

        cv::waitKey(0);
//    }
    return 0;
}
