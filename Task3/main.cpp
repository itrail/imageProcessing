#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

//operacje arytmetyczne
int przykladPierwszy(cv::Mat imageIn, cv::Mat imageOut)
{
    double a =1.2;
    double b = 5;
    int64 timeStart = getTickCount();

    //1 metoda
    for (int row = 0; row <imageIn.rows; row++)
    {
        for(int col =0; col <imageIn.cols; col++)
        {
            imageOut.at<uchar>(row,col)=saturate_cast<uchar>(a*imageIn.at<uchar>(row,col)+b);
        }
    }

    int64 timeStop = getTickCount();
    int64 time = ((timeStop - timeStart) /getTickFrequency()) * 1000;
    cout << "1 Metoda: czas = " << time << endl;

    //2 metoda
    timeStart = getTickCount();
    imageOut = a * imageIn + b;
    timeStop = getTickCount();
    time = ((timeStop - timeStart) /getTickFrequency()) * 1000;
    cout << "2 Metoda: czas = " << time << endl;

    //3 metoda
    timeStart = getTickCount();
    imageIn.convertTo(imageOut,-1,a,b);
    timeStop = getTickCount();
    time = ((timeStop - timeStart) /getTickFrequency()) * 1000;
    cout << "3 Metoda: czas = " << time << endl;
}

//korekcja gamma
int przykladDrugi(cv::Mat imageIn, cv::Mat imageOut)
{
    int gamma = 2;
    cv::Mat imageInFloat;
    imageIn.convertTo(imageInFloat,CV_32F);
    cv::Mat imageOutFloat(imageIn.size(),CV_32F);
    cv::pow(imageInFloat,1/gamma,imageOutFloat);
    cv:normalize(imageInFloat,imageOut,255,0,cv::NORM_MINMAX,CV_8U);

}

int main()
{
    Mat imageIn = imread("C:/QTProjects/Zadanie3/Gdynia.jpg");
    Mat imageOut(imageIn.size(),imageIn.type());
    cv::Mat *wskIn = &imageIn;
    cv::Mat *wskOut = &imageOut;

    przykladPierwszy(*wskIn, *wskOut);
    //przykladDrugi(*wskIn, *wskOut);

    cv::namedWindow( "ImageIn", cv::WINDOW_NORMAL );
    namedWindow("ImageOut", WINDOW_NORMAL);
    imshow("ImageIn", imageIn);
    imshow("ImageOut", imageOut);
    waitKey();
    return 0;
}
