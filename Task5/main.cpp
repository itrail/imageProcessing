#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <random>

using namespace std;

void lowPassLineFilter(cv::Mat imageIn, cv::Mat imageOut)
{

    for (int row = 1; row < (imageIn.rows - 1); row++)
    {
        for (int col = 1; col < (imageIn.cols - 1); col++)
        {
            int newPixelValue = 0;
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    newPixelValue += imageIn.at<uchar>(row + i, col + j);
                }
            }
            imageOut.at<uchar>(row,col) = newPixelValue / 9;
        }
    }

}

void highPassLineFilter(cv::Mat imageIn, cv::Mat imageOut)
{
    cv::Mat mask(3,3,CV_32S);
    mask.at<int>(2,2) = -1;
    for (int row = 0; row < (imageIn.rows - 2); row++)
    {
        for (int col = 0; col < (imageIn.cols - 2); col++)
        {
            int newPixelValue = 0;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    newPixelValue += mask.at<int>(i,j) * imageIn.at<uchar>(row + i, col + j);
                }
            }
            imageOut.at<uchar>(row+1,col+1) = cv::saturate_cast<uchar>(newPixelValue);
        }
    }
}

void prewittMask(cv::Mat imageIn, cv::Mat imageOut)
{
    cv::Mat imagePrewitt1, imagePrewitt2, imagePrewitt;
    cv::Mat mask1 = (cv::Mat_<char>(3,3) << 1, 1, 1, 0, 0, 0, -1, -1, -1);
    cv::Mat mask2 = (cv::Mat_<char>(3,3) << -1, 0, 1, -1, 0, 1, -1, 0, 1);
    cv::filter2D(imageIn,imagePrewitt1,CV_32F,mask1);
    cv::filter2D(imageIn,imagePrewitt2,CV_32F,mask2);
    imagePrewitt = (cv::abs(imagePrewitt1) + cv::abs(imagePrewitt2));
    cv::normalize(imagePrewitt,imageOut,0,255,cv::NORM_MINMAX,CV_8U);
}

void medianFilter(cv::Mat imageIn, cv::Mat imageOut)
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> randomRow(0,imageIn.rows - 1);
    std::uniform_int_distribution<int> randomCol(0,imageIn.cols - 1);
    int row, col;
    int noiseNumber = 4000;
    while (noiseNumber > 0)
    {
        row = randomRow(generator);
        col = randomCol(generator);
        imageIn.at<uchar>(row,col) = 255;
        noiseNumber--;
    }
    cv::medianBlur(imageIn,imageOut,3);
}

int main()
{
    cv::Mat imageIn =cv::imread("C:/QTProjects/Zadanie5/TestFilters.jpg",cv::IMREAD_GRAYSCALE);
    cv::Mat imageOut(imageIn.size(),CV_8U,cv::Scalar(0));

    cv::Mat *wskIn = &imageIn;
    cv::Mat *wskOut = &imageOut;

    //lowPassLineFilter(*wskIn, *wskOut);
    //highPassLineFilter(*wskIn, *wskOut);
    //prewittMask(*wskIn, *wskOut);
    medianFilter(*wskIn, *wskOut);

    cv::namedWindow("ImageIn",CV_WINDOW_NORMAL);
    cv::namedWindow("ImageOut",CV_WINDOW_NORMAL);
    cv::imshow("ImageIn",imageIn);
    cv::imshow("ImageOut",imageOut);
    cv::waitKey();
    return 0;
}
