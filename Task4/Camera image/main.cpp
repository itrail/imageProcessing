#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio.hpp>

int main()
{
    cv::namedWindow("Window",cv::WINDOW_NORMAL);
    cv::Mat frame;
    cv::VideoCapture cap(0);
    if (!cap.isOpened())
    {
        std::cout << "Błąd otwarcia kamery" << std::endl;
        return -1;
    }
    int frameWidth = static_cast<int> (cap.get(CV_CAP_PROP_FRAME_WIDTH));
    int frameHeight = static_cast<int> (cap.get(CV_CAP_PROP_FRAME_HEIGHT));
    cv::Size frameSize(frameWidth,frameHeight);
    cv::VideoWriter writer;
    int codec = CV_FOURCC('M','J','P','G');
    double fps = 25.0; //Liczba klatek na sekundę
    writer.open("C:/QTProjects/Zadanie4/CameraImage/Camera_movie.avi",codec,fps,frameSize);
    if (!writer.isOpened())
    {
        std::cout << "Błąd otwarcia pliku do zapisu" << std::endl;
        return -1;
    }
    while (true)
    {
        if (!cap.read(frame))
            break;
        writer.write(frame);
        cv::imshow("Window",frame);
        if (cv::waitKey(40) == 27)
            break;
    }
    return 0;
}
