#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

//dodawanie i odejmowanie obrazów
void przykladTrzeci()
{
    cv::Mat imageIn1, imageIn2;
    imageIn1 = cv::imread("C:/QTProjects/Zadanie3/Gdynia.jpg",cv::IMREAD_GRAYSCALE);
    imageIn2 = cv::imread("C:/QTProjects/Zadanie3/Gdynia1.jpg",cv::IMREAD_GRAYSCALE);
    cv::Mat imageOutSum(imageIn1.size(),imageIn1.type());
    cv::Mat imageOutSumWeighted(imageIn1.size(),imageIn1.type());
    cv::Mat imageOutSubstract(imageIn1.size(),imageIn1.type());

    cv::add(imageIn1,imageIn2,imageOutSum);
    cv::addWeighted(imageIn1,0.1,imageIn2,0.9,0.0,imageOutSumWeighted);
    cv::subtract(imageIn1,imageIn2,imageOutSubstract);
    cv::namedWindow("imageIn1",CV_WINDOW_NORMAL);
    cv::namedWindow("imageIn2",CV_WINDOW_NORMAL);
    cv::namedWindow("imageOutSumWeighted",CV_WINDOW_NORMAL);
    cv::namedWindow("imageSubstract",CV_WINDOW_NORMAL);
    cv::imshow("imageIn1",imageIn1);
    cv::imshow("imageIn2",imageIn2);
    cv::imshow("imageOutSumWeighted",imageOutSumWeighted);
    cv::imshow("imageSubstract",imageOutSubstract);
    cv::waitKey();
}

//rozszerzanie zakresu jasności
void przykladCzwarty()
{
    int64 timeStart , timeStop, deltaTime;
    Mat imageIn;
    imageIn = cv::imread("C:/QTProjects/Zadanie3/Gdynia2.jpg",cv::IMREAD_GRAYSCALE);
    Mat imageOut1(imageIn.size(),imageIn.type());
    Mat imageOut2(imageIn.size(),imageIn.type());

    timeStart =cv::getTickCount();
    uchar minVal = 255;
    uchar maxVal=0;
    for (int  row = 0; row <imageIn.rows; row++)
    {
        for (int  col = 0; col <imageIn.cols; col++)
        {
            if (imageIn.at<uchar>(row,col) > maxVal)
                maxVal = imageIn.at<uchar>(row,col);

            if (imageIn.at<uchar>(row,col) <minVal)
               minVal = imageIn.at<uchar> (row,col);
         }
    }
    cout << "Min value = " << (int)minVal << ";Max Value = " << (int)maxVal << endl;
    uchar minValNew = 0;
    uchar maxValNew = 255;
    for (int  row = 0; row <imageIn.rows; row++)
    {
        for (int  col = 0; col <imageIn.cols; col++)
        {
            imageOut1.at<uchar>(row,col) = (static_cast<double>(imageIn.at<uchar>(row,col)) - minVal / (maxVal - minVal) * (maxValNew - minValNew)+ minValNew);
        }
    }
    timeStop = cv::getTickCount ();
    deltaTime = (timeStop - timeStart) / getTickFrequency() * 1000;
    std::cout << "Czas obliczenia i metoda = " <<deltaTime << " {ms}" << std::endl;

    cv::namedWindow("imageIn",CV_WINDOW_NORMAL);
    cv::namedWindow("imageOut1",CV_WINDOW_NORMAL);
    cv::namedWindow("imageOut2",CV_WINDOW_NORMAL);
    cv::imshow("imageIn",imageIn);
    cv::imshow("imageOut1",imageOut1);
    cv::imshow("imageOut2",imageOut2);
    cv::waitKey();

}

int main()
{
    //przykladTrzeci();
    przykladCzwarty();
    return 0;
}
