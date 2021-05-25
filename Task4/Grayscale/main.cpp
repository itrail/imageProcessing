#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

int main()
{
    cv::Mat image = cv::imread("C:/QTProjects/Zadanie4/Gdynia.jpg",cv::IMREAD_GRAYSCALE);
    if (image.empty())
    {
        std::cout << "Błąd w odczycie pliku";
        return -1;
    }
    cv::namedWindow("Window",CV_WINDOW_NORMAL);
    cv::imshow("Window",image);
    cv::waitKey();
    cv::destroyWindow("Window");
    cv::imwrite("C:/QTProjects/Zadanie4/Gdynia_Grey.jpg",image);
    return 0;
}
