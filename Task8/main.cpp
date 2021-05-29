#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

int main()
{
    cv::Mat imageBGR = cv::imread("C:/QTProjects/Zadanie8/Gdynia.jpg");

    cv::Mat imageB = cv::Mat(imageBGR.rows,imageBGR.cols,CV_8U);
    cv::Mat imageG = cv::Mat(imageBGR.rows,imageBGR.cols,CV_8U);
    cv::Mat imageR = cv::Mat(imageBGR.rows,imageBGR.cols,CV_8U);
    int64 t_start = cv::getTickCount();
    for (int row = 0; row < imageBGR.rows; row++)
    {
        for (int col = 0; col < imageBGR.cols; col++)
        {
            imageB.at<uchar>(row,col) = imageBGR.at<cv::Vec3b>(row,col)[0];
            imageG.at<uchar>(row,col) = imageBGR.at<cv::Vec3b>(row,col)[1];
            imageR.at<uchar>(row,col) = imageBGR.at<cv::Vec3b>(row,col)[2];
        }
    }
    int64 t_stop = cv::getTickCount();
    double time = ((t_stop - t_start) / cv::getTickFrequency()) * 1000;
    std::cout << "Method 1 - Time elapsed = " << time << " [ms]"<< std::endl;

    // 2 Metoda
    t_start = cv::getTickCount();
    std::vector<cv::Mat> images;
    cv::split(imageBGR,images);
    t_stop = cv::getTickCount();
    time = ((t_stop - t_start) / cv::getTickFrequency()) * 1000;
    std::cout << "Method 2 - Time elapsed = " << time << " [ms]" << std::endl;


    cv::namedWindow("Channel B",cv::WINDOW_NORMAL);
    cv::namedWindow("Channel G",cv::WINDOW_NORMAL);
    cv::namedWindow("Channel R",cv::WINDOW_NORMAL);
    cv::imshow("Channel B", imageB);
    cv::imshow("Channel G", imageG);
    cv::imshow("Channel R", imageR);
    cv::waitKey();
    return 0;
}
