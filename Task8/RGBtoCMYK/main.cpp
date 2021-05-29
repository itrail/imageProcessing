#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

int main()
{
    cv::Mat imageBGR = cv::imread("C:/QTProjects/Zadanie8/Gdynia.jpg");
    cv::Mat imageBGR_prim;
    imageBGR.convertTo(imageBGR_prim,CV_32FC3,1/255.0);
    cv::Mat imagesCMYK[4];
    for (int i = 0; i < 4; i++)
    {
        imagesCMYK[i].create(imageBGR_prim.size(),CV_8U);
    }
    for(int row = 0; row < imageBGR_prim.rows; row++)
    {
        for (int col = 0; col < imageBGR_prim.cols; col++)
        {
            float R_prim = imageBGR_prim.at<cv::Vec3f>(row,col)[2];
            float G_prim = imageBGR_prim.at<cv::Vec3f>(row,col)[1];
            float B_prim = imageBGR_prim.at<cv::Vec3f>(row,col)[0];
            float K = 1 - (std::max(std::max(R_prim,G_prim),B_prim));
            float C = (1 - R_prim - K) / (1 - K) * 255;
            float M = (1 - G_prim - K) / (1 - K) * 255;
            float Y = (1 - B_prim - K) / (1 - K) * 255;
            K = K * 255;
            imagesCMYK[0].at<uchar>(row,col) = static_cast<uchar>(C);
            imagesCMYK[1].at<uchar>(row,col) = static_cast<uchar>(M);
            imagesCMYK[2].at<uchar>(row,col) = static_cast<uchar>(Y);
            imagesCMYK[3].at<uchar>(row,col) = static_cast<uchar>(K);
        }
    }
    cv::namedWindow("Channel C",cv::WINDOW_NORMAL);
    cv::namedWindow("Channel M",cv::WINDOW_NORMAL);
    cv::namedWindow("Channel Y",cv::WINDOW_NORMAL);
    cv::namedWindow("Channel K",cv::WINDOW_NORMAL);
    cv::imshow("Channel C", imagesCMYK[0]);
    cv::imshow("Channel M", imagesCMYK[1]);
    cv::imshow("Channel Y", imagesCMYK[2]);
    cv::imshow("Channel K", imagesCMYK[3]);
    cv::waitKey();
    return 0;
}
