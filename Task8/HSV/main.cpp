#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

int main()
{
    cv::VideoCapture cap(0);
    if (!cap.isOpened())
    {
        std::cout << "Błąd otwarcia kamery" << std::endl;
        return -1;
    }
    cv::Mat frameRGB;
    cv::Mat frameHSV;
    cv::namedWindow("Window",CV_WINDOW_NORMAL);
    for (;;)
    {
        if (!cap.read(frameRGB))
            break;
        cv::cvtColor(frameRGB,frameHSV,CV_BGR2HSV);
        for (int row = 0; row < frameHSV.rows; row++)
        {
            for (int col = 0; col < frameHSV.cols; col++)
            {
                uchar hue = frameHSV.at<cv::Vec3b>(row,col)[0];
                uchar sat = frameHSV.at<cv::Vec3b>(row,col)[1];
                if ((hue > 160 || hue < 10) && (sat > 25 && sat < 166))
                    continue;
                else
                    frameRGB.at<cv::Vec3b>(row,col) = cv::Vec3b(0,0,0);
            }
        }
        cv::imshow("Window",frameRGB);
        if (cv::waitKey(40) == 27)
        break;
    }
    return 0;
}
