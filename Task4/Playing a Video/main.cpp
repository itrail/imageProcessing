#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio.hpp>

int main()
{
    cv::namedWindow("Window",CV_WINDOW_NORMAL);
    cv::VideoCapture cap("C:/QTProjects/Zadanie4/playingAVideo/poppy.mp4");
    if (!cap.isOpened())
    {
        std::cout << "Błąd w odczycie pliku";
        return -1;
    }
    double rate = cap.get(CV_CAP_PROP_FPS);
    std::cout << "Frame rate = " << rate << std::endl;
    int delay = (1 / rate) * 1000;
    std::cout << "delay [ms] = " << delay << std::endl;
    cv::Mat frame;
    for (;;)
    {
        if (!cap.read(frame))
        break;
        cv::imshow("Window",frame);
        if (cv::waitKey(delay) == 27)
        break;
    }
    return 0;
}
