#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace cv;
using namespace std;


int main() 
{
    Mat img=imread("paisaje.jpg",IMREAD_GRAYSCALE);
    Mat dst = Mat::zeros(img.rows-2, img.cols-2, CV_8UC1);
    for(int i=1;i<img.rows-1;i++) 
    {
        for(int j=1;j<img.cols-1;j++) 
        {
            /*uchar center = img.at<uchar>(i,j);
            unsigned char code = 0;
            code |= ((img.at<uchar>(i-1,j-1)) > center) << 7;
            code |= ((img.at<uchar>(i-1,j)) > center) << 6;
            code |= ((img.at<uchar>(i-1,j+1)) > center) << 5;
            code |= ((img.at<uchar>(i,j+1)) > center) << 4;
            code |= ((img.at<uchar>(i+1,j+1)) > center) << 3;
            code |= ((img.at<uchar>(i+1,j)) > center) << 2;
            code |= ((img.at<uchar>(i+1,j-1)) > center) << 1;
            code |= ((img.at<uchar>(i,j-1)) > center) << 0;
            dst.at<uchar>(i-1,j-1) = code;*/
        }
    }
    imshow("LBP",dst);
    imshow("Source",img);
    waitKey(0);
    return 0;
}