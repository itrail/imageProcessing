#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

int main()
{
    cv::VideoCapture cam(0);
    if (!cam.isOpened())
    {
        std::cout << "Blad otwarcia kamery" << std::endl;
        return -1;
    }
    //Wyniki kalibracji
    cv::Mat CM, D;
    std::vector<cv::Mat> rvecs, tvecs;
    std::vector<cv::Point3f> patternPoints;
    std::vector< cv::Point2f> imagePoints;
    std::vector<std::vector<cv::Point3f>> patternPointsCalib;
    std::vector<std::vector<cv::Point2f>> imagePointsCalib;
    // Przygotowanie wzorca
    cv::Size patternSize(4,7); //szerokość, wysokość
    int patternElementSize = 34;
    for (int row = 0; row < patternSize.height; row++)
    {
        for (int col = 0; col < patternSize.width; col++)
        {
            patternPoints.push_back(cv::Point3f(row*patternElementSize,
   col*patternElementSize, 0.0f));
        }
    }
    cv::Mat imageIn;
    int nbImages = 0;
    cv::namedWindow("Window");
    while (true)
    {
        cam.read(imageIn);
        bool found = cv::findChessboardCorners(imageIn,
                                               patternSize,
                                               imagePoints,
                                               cv::CALIB_CB_ADAPTIVE_THRESH+cv::CALIB_CB_NORMALIZE_IMAGE);
        if (found)
        {
            cv::Mat imageGray;
            cv::cvtColor(imageIn,imageGray,CV_RGB2GRAY);
            cv::cornerSubPix(imageGray,imagePoints,cv::Size(5,5),cv::Size(-1,-1),cv::TermCriteria(cv::TermCriteria::MAX_ITER +
                           cv::TermCriteria::EPS,
                           30,       //max number of iterations
                           0.1));    //min accuracy
            patternPointsCalib.push_back(patternPoints);
            imagePointsCalib.push_back(imagePoints);
            cv::drawChessboardCorners(imageIn, patternSize,
                                      imagePoints,found);
            nbImages++;
            std::cout << "Liczba zdjec do kalibracji = " << nbImages << std::endl;
        }
        cv::imshow("Window",imageIn);
        char key = static_cast<char>(cv::waitKey(2000));
        if (key == 27)
        {
            std::cout << "Zamykam aplikacje.." <<std::endl;
            return 0;
        }
        if (key == 'c')
        {
            if (nbImages < 10)
            {
                std::cout << "Zbyt mała liczba prezentacji wzorca" << std::endl;
                continue;
            }
            cv::calibrateCamera(patternPointsCalib, imagePointsCalib, imageIn.size(), CM, D, rvecs, tvecs);
            cv::FileStorage fsl("C:/QTProjects/Zadanie7/Kalibracja.xml", cv::FileStorage::WRITE);

            fsl <<"CM" << CM;
            fsl <<"D" << D;
            fsl.release();
            std::cout << "*****************" <<std::endl;
            std::cout << "Wyniki kalibracji" << std::endl;
            std::cout << "fx:    " <<CM.at<double>(0,0) <<std::endl;
            std::cout << "fy:    " <<CM.at<double>(1,1) <<std::endl;
            std::cout << "ox:    " <<CM.at<double>(0,2) <<std::endl;
            std::cout << "oy:    " <<CM.at<double>(1,2) <<std::endl;
            std::cout << "Wspolczynnik znieksztalcen" <<std::endl;
            std::cout << "k1:    " <<CM.at<double>(0,0) <<std::endl;
            std::cout << "k2:    " <<CM.at<double>(1,1) <<std::endl;
            std::cout << "p1:    " <<CM.at<double>(0,2) <<std::endl;
            std::cout << "p2:    " <<CM.at<double>(0,3) <<std::endl;
            std::cout << "k3:    " <<CM.at<double>(0,4) <<std::endl;
        }
    }
      return 0;
}
