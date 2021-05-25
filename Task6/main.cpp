#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

void przykladPierwszy(cv::Mat imageIn)
{
    // Obliczenie histogramu
    const int binNb = 32;
    const int range = 256 / binNb;
    cv::Mat histogram(binNb,1,CV_32S,cv::Scalar(0));
    for (int row = 0; row < imageIn.rows; row++)
    {
        for (int col = 0; col < imageIn.cols; col++)
        {
            int pixelValue = imageIn.at<uchar>(row,col);
            int bin = pixelValue / range;
            histogram.at<int>(bin) += 1;
        }
    }
    // Wyświetlenie histogramu
    int maxBinValue = 0;
    for (int i = 0; i < binNb; i++)
    {
        if (maxBinValue < histogram.at<int>(i))
            maxBinValue = histogram.at<int>(i);
    }
    cv::Mat imageHist(120,256,CV_8U,cv::Scalar(0));
    for (int col = 0; col < imageHist.cols; col++)
    {
        double scale = 100.0 / maxBinValue;
        for (int row = 0; row < imageHist.rows; row++)
        {
            int bin = col / range;
            int binHeight = histogram.at<int>(bin) * scale;
            if (row < (120 - binHeight))
            imageHist.at<uchar>(row,col) = 255;
        }
    }
    for (int i = 0; i < histogram.rows; i++)
    {
        std::cout << "Liczba pikseli w przedziale " << i+1 << " = " << histogram.at<int>(i) << std::endl;
    }

    cv::namedWindow("Histogram",CV_WINDOW_NORMAL);
    cv::imshow("Histogram",imageHist);
}

void przykladDrugi(cv::Mat imageIn)
{
    //Obliczanie histogramu z wykorzystaniem funkcji calcHist()
    const int binNb = 256;
    const int range = 256 / binNb;
    std::vector<int> channels(1,0);
    std::vector<int> histSize(1,binNb);
    std::vector<float> ranges = {0.0, 256.0};
    std::vector<cv::Mat> images;
    images.push_back(imageIn);
    cv::Mat histogram;
    cv::calcHist(images,channels,cv::noArray(),histogram,histSize,ranges);
    int sumPixels = imageIn.rows * imageIn.cols;
    cv::Mat histogramProbability = histogram / sumPixels;
    cv::Mat distribution(histogramProbability.size(), histogramProbability.type(),
    cv::Scalar(0));
    cv::Mat normalizedPixelsLevels(histogramProbability.size(), histogramProbability.type(),
    cv::Scalar(0));
    cv::Mat normalizedHistogram(histogramProbability.size(), histogramProbability.type(),
    cv::Scalar(0));
    float sum = 0.0;

    for (int i = 0; i < histogramProbability.rows; i++)
    {
        sum += histogramProbability.at<float>(i);
        distribution.at<float>(i) = sum;
        normalizedPixelsLevels.at<float>(i) = (i + 1) * range / 256.0;
    }
    cv::Mat lookUpTable(256,1,CV_8U);
    for (int i = 0; i < distribution.rows; i++)
    {
        float distanceMin = 1.0;
        int position = 0;
        for (int j = 0; j < normalizedPixelsLevels.rows; j++)
        {
            float distance = std::abs(distribution.at<float>(i) -
            normalizedPixelsLevels.at<float>(j));
            if (distance < distanceMin)
            {
                distanceMin = distance;
                position = j;
            }
        }
        lookUpTable.at<uchar>(i) = position;
        normalizedHistogram.at<float>(position) += histogram.at<float>(i);
    }

    //Obraz wyrównanego histogramu
    cv::Mat imageHist1(120,256,CV_8U,cv::Scalar(0));
    int maxBinValue = 0;;
    for (int i = 0; i < binNb; i++)
    {
        if (maxBinValue < normalizedHistogram.at<float>(i))
        maxBinValue = normalizedHistogram.at<float>(i);
    }
    for (int col = 0; col < imageHist1.cols; col++)
    {
        double scale = 100.0 / maxBinValue;
        for (int row = 0; row < imageHist1.rows; row++)
        {
            int bin = col / range;
            int binHeight = normalizedHistogram.at<float>(bin) * scale;
            if (row < (120 - binHeight))
            imageHist1.at<uchar>(row,col) = 255;
        }
    }

    //Obraz histogramu przed operacją wyrównania
    cv::Mat imageHist2(120,256,CV_8U,cv::Scalar(0));
    maxBinValue = 0;;
    for (int i = 0; i < binNb; i++)
    {
        if (maxBinValue < histogram.at<float>(i))
        maxBinValue = histogram.at<float>(i);
    }
    for (int col = 0; col < imageHist2.cols; col++)
    {
        double scale = 100.0 / maxBinValue;
        for (int row = 0; row < imageHist2.rows; row++)
        {
        int bin = col / range;
        int binHeight = histogram.at<float>(bin) * scale;
        if (row < (120 - binHeight))
        imageHist2.at<uchar>(row,col) = 255;
        }
    }
    cv::Mat imageEqualled(imageIn.size(),imageIn.type());
    for (int row = 0; row < imageEqualled.rows; row++)
    {
        for (int col = 0; col < imageEqualled.cols; col++)
        {
            uchar pixelValue = imageIn.at<uchar>(row,col);
            imageEqualled.at<uchar>(row,col) = lookUpTable.at<uchar>(pixelValue);
        }
    }
    cv::namedWindow("Input Histogram",CV_WINDOW_NORMAL);
    cv::imshow("Input Histogram",imageHist2);
    cv::namedWindow("Output Image",CV_WINDOW_NORMAL);
    cv::imshow("Output Image",imageEqualled);
    cv::namedWindow("Output histogram",CV_WINDOW_NORMAL);
    cv::imshow("Output histogram",imageHist1);
}

void przykladTrzeci(cv::Mat imageIn1)
{
    cv::Mat imageIn2 =
    cv::imread("C:/QTProjects/Zadanie6//Gdynia1.jpg",cv::IMREAD_GRAYSCALE);
    cv::Mat imageIn3 =
    cv::imread("C:/QTProjects/Zadanie6/Gdynia2.jpg",cv::IMREAD_GRAYSCALE);
    cv::Mat imageIn4 =
    cv::imread("C:/QTProjects/Zadanie6/Gdynia3.jpg",cv::IMREAD_GRAYSCALE);

    //Obliczanie histogramu z wykorzystaniem funkcji calcHist()
    const int binNb = 128;
    std::vector<int> channels(1,0);
    std::vector<int> histSize(1,binNb);
    std::vector<float> ranges = {0.0, 256.0};
    std::vector<cv::Mat> images;
    images.push_back(imageIn1);
    cv::Mat histogram1;
    cv::calcHist(images,channels,cv::noArray(),histogram1,histSize,ranges);
    images.at(0) = imageIn2;
    cv::Mat histogram2;
    cv::calcHist(images,channels,cv::noArray(),histogram2,histSize,ranges);
    images.at(0) = imageIn3;
    cv::Mat histogram3;
    cv::calcHist(images,channels,cv::noArray(),histogram3,histSize,ranges);
    images.at(0) = imageIn4;
    cv::Mat histogram4;
    cv::calcHist(images,channels,cv::noArray(),histogram4,histSize,ranges);
    double distanceMin_1 = 0.0;
    double distanceMin_2 = 0.0;
    double distanceMin_3 = 0.0;
    for (int i = 0; i < histogram1.rows; i++)
    {
        distanceMin_1 += cv::min(histogram1.at<float>(i),histogram2.at<float>(i));
        distanceMin_2 += cv::min(histogram1.at<float>(i),histogram3.at<float>(i));
        distanceMin_3 += cv::min(histogram1.at<float>(i),histogram4.at<float>(i));
    }

    std::cout << "distanceMin_1 = " << distanceMin_1 << std::endl;
    std::cout << "distanceMin_2 = " << distanceMin_2 << std::endl;
    std::cout << "distanceMin_3 = " << distanceMin_3 << std::endl;
    double distanceCorrel_1 = cv::compareHist(histogram1,histogram2,CV_COMP_CORREL);
    std::cout << "distanceCorrel_1 = " << distanceCorrel_1 << std::endl;
    double distanceCorrel_2 = cv::compareHist(histogram1,histogram3,CV_COMP_CORREL);
    std::cout << "distanceCorrel_2 = " << distanceCorrel_2 << std::endl;
    double distanceCorrel_3 = cv::compareHist(histogram1,histogram4,CV_COMP_CORREL);
    std::cout << "distanceCorrel_3 = " << distanceCorrel_3 << std::endl;
}

int main()
{
    cv::Mat imageIn =cv::imread("C:/QTProjects/Zadanie6/Gdynia.jpg",cv::IMREAD_GRAYSCALE);

    cv::Mat *wskIn = &imageIn;

    cv::namedWindow("ImageIn",CV_WINDOW_NORMAL);
    cv::imshow("ImageIn",imageIn);

    //przykladPierwszy(*wskIn);
    //przykladDrugi(*wskIn);
    przykladTrzeci(*wskIn);

    cv::waitKey();
    return 0;
}
