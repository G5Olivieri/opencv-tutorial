#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

const std::string keys =
        "{help      |           | print this message    }"
        "{@image    |qrcode     | load image            }"
        "{lena      |lena.jpg   | lena image            }"
        "{contours  |contours.png | contours image      }"
        "{qrcode    |rotateCode.jpg |  qr code              }"
        ;


#define MinSize 100
#define PI 3.14

struct CodeMap
{
    std::vector<cv::Point> outside;
    std::vector<cv::Point> inside;
    cv::Point center;
    CodeMap(){

    }
};

struct CodeRectangle
{
    cv::Point leftTop;
    cv::Point leftDown;
    cv::Point rightTop;
    cv::Point rightDown;
    int angle;
    CodeRectangle(){
        angle = 0;
    }
};

struct CodeContour
{
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
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
    int measurementError = 5;
    for( int i = 0; i< candidates.size(); i++ ){
        for( int j = i; j< candidates.size(); j++ ){
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
    int distPt13 = std::abs(pt1.x-pt3.x) + std::abs(pt1.y-pt3.y);
    int distPt24 = std::abs(pt2.x-pt4.x) + std::abs(pt2.y-pt4.y);
    int distPt12 = std::abs(pt1.x-pt2.x) + std::abs(pt1.y-pt2.y);
    int distPt34 = std::abs(pt3.x-pt4.x) + std::abs(pt3.y-pt4.y);
    return distPt13==distPt24 && distPt12==distPt34;
}

bool compare(const cv::Point &pt1, const cv::Point &pt2)
{
    return pt1.y > pt2.y;
}

void arrangeRectanglePoints(std::vector<cv::Point> vec)
{
    std::sort(vec.begin(), vec.end(), compare);
}

CodeRectangle calculateRectangle( std::vector<CodeMap> codeMap)
{
    CodeRectangle codeRect;
    bool result = false;
    for( int i = 0; i < codeMap.size(); i++ ){
        for( int j = i; j < codeMap.size(); j++ ){
            for( int k = j; k < codeMap.size(); k++ ){
                for( int l = k; l < codeMap.size(); l++ ){
                    if(i==j||j==k||k==l)
                        continue;
                    if( codeMap[i].center == codeMap[j].center || codeMap[j].center == codeMap[k].center ||codeMap[k].center == codeMap[l].center)
                        continue;

                    result = isRectangle(codeMap[i].center, codeMap[j].center, codeMap[k].center, codeMap[l].center);
                    if( result ){
                        std::vector<cv::Point> rect;
                        rect.push_back(codeMap[i].center);
                        rect.push_back(codeMap[j].center);
                        rect.push_back(codeMap[k].center);
                        rect.push_back(codeMap[l].center);
                        arrangeRectanglePoints(rect);

                        int deltaY = rect[0].y - rect[1].y;
                        int deltaX = rect[0].x - rect[1].x;
                        int angleInDegrees = std::atan2(deltaY, deltaX) * 180 / PI + 1;
                        if( rect[0].x < rect[1].x ){
                            angleInDegrees = angleInDegrees*(-1);
                            codeRect.leftTop = rect[0];
                            codeRect.rightTop = rect[1];
                        }else{
                            codeRect.leftTop = rect[1];
                            codeRect.rightTop = rect[0];
                        }
                        if( rect[2].x < rect[3].x ){
                            codeRect.leftDown = rect[2];
                            codeRect.rightDown = rect[3];
                        }else{
                            codeRect.leftDown = rect[3];
                            codeRect.rightDown = rect[2];
                        }
                        codeRect.angle = angleInDegrees;
                        return codeRect;
                    }
                }
            }
        }
    }

    return codeRect;
}


cv::Mat rotate(cv::Mat src, double angle)
{
    cv::Mat dst;
    cv::Point2f pt(src.cols/2., src.rows/2.);
    cv::Mat r = cv::getRotationMatrix2D(pt, angle, 1.0);
    cv::warpAffine(src, dst, r, cv::Size(src.cols, src.rows));
    return dst;
}

std::vector<std::vector<cv::Point>> findRectangle(std::vector<std::vector<cv::Point> > contours, std::vector<cv::Vec4i> hierarchy)
{
    std::vector<cv::Point> approx;
    std::vector<std::vector<cv::Point>> candidates;
    for( int i = 0; i< contours.size(); i++ ){
        if( hierarchy[i][3] == -1 )
            continue;

        cv::approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true)*0.02, true);
        if (std::fabs(cv::contourArea(contours[i])) < MinSize || !cv::isContourConvex(approx))
            continue;

        if (approx.size() == 4 )
            candidates.push_back(approx);

    }
    return candidates;
}

cv::Mat preprocessing(cv::Mat srcImg )
{
    cv::Mat grayImg;
    cv::cvtColor( srcImg, grayImg, cv::COLOR_BGR2GRAY );
    cv::Mat cannyImg;
    cv::Canny( grayImg, cannyImg, 50, 150, 3 );
    return cannyImg;
}

void drawContourImage(cv::Size size, std::vector<std::vector<cv::Point>> candidates)
{
    cv::RNG rng(12345);
    cv::Mat drawing = cv::Mat::zeros( size, CV_8UC3 );
    for( int i = 0; i< candidates.size(); i++ ){
        cv::Scalar color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        cv::drawContours( drawing, candidates, i, color, 2, 8);
    }
    cv::imshow("drawImage", drawing);
}

void drawCodeMapImage(cv::Mat srcImg, std::vector<CodeMap> codeRect)
{
    cv::RNG rng(12345);
    for( int i = 0; i < codeRect.size(); i++ ){
        cv::Scalar color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        cv::line(srcImg, codeRect[i].outside[0], codeRect[i].outside[1], color, 3);
        cv::line(srcImg, codeRect[i].outside[1], codeRect[i].outside[2], color, 3);
        cv::line(srcImg, codeRect[i].outside[2], codeRect[i].outside[3], color, 3);
        cv::line(srcImg, codeRect[i].outside[3], codeRect[i].outside[0], color, 3);
        cv::circle(srcImg, codeRect[i].center, 3, color, 3);
    }
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
    }else if( file == "qrcode" ){
        file = parser.get<std::string>("qrcode");
    }
    srcImg = cv::imread(file, cv::IMREAD_COLOR );
    if( srcImg.empty() ){
        return -1;
    }

    cv::VideoCapture capture(0);

    while(true)
    {
        capture >> srcImg;

        cv::Mat cannyImg = preprocessing(srcImg);

        CodeContour codeContour;
        cv::findContours( cannyImg, codeContour.contours, codeContour.hierarchy, cv::RETR_TREE , cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );

        std::vector<std::vector<cv::Point>> candidates;
        candidates = findRectangle(codeContour.contours, codeContour.hierarchy);
        drawContourImage(srcImg.size(), candidates);

        int thresholdBound = 30;
        std::vector<CodeMap> codeRect = chkCode(candidates, thresholdBound);
//        drawCodeMapImage(srcImg, codeRect);

        CodeRectangle mainRect = calculateRectangle(codeRect);
        cv::Mat rotateImg = rotate(srcImg, mainRect.angle);

        cv::imshow("srcImgImage", srcImg);



        cv::Mat cannyImg2 = preprocessing(rotateImg);

        CodeContour codeContour2;
        cv::findContours( cannyImg2, codeContour2.contours, codeContour2.hierarchy, cv::RETR_TREE , cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );

        std::vector<std::vector<cv::Point>> candidates2;
        candidates2 = findRectangle(codeContour2.contours, codeContour2.hierarchy);
        drawContourImage(rotateImg.size(), candidates2);

        std::vector<CodeMap> codeRect2 = chkCode(candidates2, 30);
        drawCodeMapImage(rotateImg, codeRect2);

        CodeRectangle mainRect2 = calculateRectangle(codeRect2);
        cv::imshow("rotateImage", rotateImg);

//        cv::Mat Marc_ROI;
//        Marc_ROI = rotateImg(cv::Rect(mainRect2.leftTop, mainRect2.rightDown));
//        cv::imshow("Marc_ROI", Marc_ROI);

        cv::waitKey(33);
    }
    return 0;
}
