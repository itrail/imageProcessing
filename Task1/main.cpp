#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main()
{
    cv::Mat img = cv::imread("C:/TestPicture.jpeg");

    if(img.empty())
        return -1;

    cv::namedWindow( "Przyklad1", cv::WINDOW_NORMAL );
    cv::imshow( "Przyklad1", img );
    cv::waitKey( 5000 );
    cv::destroyWindow( "Przyklad1" );
    return 0;
}
