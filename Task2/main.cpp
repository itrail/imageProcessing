#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

/*wyświetlający obraz monochromatyczny o wymiarach 300x400 pikseli o wartości równej 100*/
void obrazMonochromatyczny()
{
    cv::Mat image(300,400,CV_8U,cv::Scalar(100));
    cv::namedWindow("Window");
    cv::imshow("Window",image);
    cv::waitKey();
}

/*Wyświetlenie obrazu koloru niebieskiego o rozdzielczości 600x800 pikseli, następnie zmiana koloru na
zielony z wykorzystaniem klasy cv::Scalar*/
void przykladPierwszy()
{
    cv::Mat image(600,800,CV_8UC3,cv::Scalar(255,0,0));
    cv::namedWindow("Window");
    cv::imshow("Window",image);
    cv::waitKey();
    image.setTo(cv::Scalar(0,255,0));
    cv::imshow("Window",image);
    cv::waitKey();
}

/*Wyświetlenie obrazu koloru niebieskiego o rozdzielczości 600x800 pikseli, następnie zmiana koloru na
zielony z wykorzystaniem dostępu do indywidualnych wartości pikseli:*/
void przykladDrugi()
{
    cv::Mat image(600,800,CV_8UC3);
    //iteracja po wierszach macierzy image, składnik klasy rows zwraca liczbę wierszy
    for (int row = 0; row < image.rows; row++)
    {
        //iteracja po kolumnach macierzy image, składnik klasy cols zwraca liczbę kolumn
        for (int col = 0; col < image.cols; col++)
        {
            //zmiana wartości piksela z wykorzystaniem klasy cv::Vec3b
            image.at<cv::Vec3b>(row,col) = cv::Vec3b(255,0,0);
        }
    }
    cv::namedWindow("Window");
    cv::imshow("Window",image);
    cv::waitKey();
    for (int row = 0; row < image.rows; row++)
    {
        for (int col = 0; col < image.cols; col++)
        {
            //zmiana wartości piksela z wykorzystaniem dostępu do pojedyńczego kanału
            image.at<cv::Vec3b>(row,col)[0] = 0;
            image.at<cv::Vec3b>(row,col)[1] = 255;
        }
    }
    cv::imshow("Window",image);
    cv::waitKey();
}

int main()
{
    //obrazMonochromatyczny();
    //przykladPierwszy();
    przykladDrugi();
}

//postanowiłem wszystkie przykłady mieć w jednym pliku, a więc w celu uruchomienia, któregoś z przykładów należy wywołac wybrana funkcję w funkcji głównej programu
