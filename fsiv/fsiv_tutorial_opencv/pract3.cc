#include <cv.h>
#include <highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <cmath>
#include <iostream>

using namespace cv;

/// Global Variables
const int C_max = 200;
double alpha;
double beta;


Mat img1;
Mat img2;

const cv::String keys =
    "{help h usage ? |      | print this message   }"
    "{path           |.     | path to file         }"
    "{fps            | -1.0 | fps for output video }"
    "{N count        |100   | count of objects     }"
    "{ts timestamp   |      | use time stamp       }"
    "{@image1        |      | image1 for compare   }"
    "{@image2        |<none>| image2 for compare   }"
    "{@repeat        |1     | number               }"
    ;

void convolve(Mat fil){
  for (int i = 0; i < img1.rows; i++){

    for (int j = 0; j < img1.cols; j++){

        Vec3f pixel = img1.at<Vec3f>(i,j);



        img2.at<Vec3f>(i,j) = pixel;

    }
  }
}

void cambiarWH(){
  for (int i = 0; i < img2.rows; i++){

    for (int j = 0; j < img2.cols; j++){

      if(i+1 < img2.rows && j+1 < img2.cols ){
        img2.at<Vec3f>(i,j) = img1.at<Vec3f>(i+1,j+1);
      }
    }
  }
}




int main( int argc, char** argv )
{

    cv::CommandLineParser parser(argc, argv, keys);
    parser.about("Application name v1.0.0");s
    if (parser.has("help"))
    {
        parser.printMessage();
          return 0;
    }
    int N = parser.get<int>("N");
    double fps = parser.get<double>("fps");
    cv::String path = parser.get<cv::String>("path");
    bool use_time_stamp = parser.has("timestamp");

    cv::String im1 = parser.get<cv::String>(0);
    cv::String im2 = parser.get<cv::String>(1);
    int repeat = parser.get<int>(2);

    if (!parser.check())
    {
        parser.printErrors();
        return 0;
    }

    img1 = cv::imread(im1, cv::IMREAD_COLOR);

    img2 = Mat::zeros(img1.rows+1,img1.cols+1,CV_32F);
      
    namedWindow("IMG", 1);

    cambiarWH();

	img1.convertTo(img1,CV_32F,(1.0/255),0.0);
 	img2.convertTo(img2,CV_32F,(1.0/255),0.0);

    Mat filLap;

    convolucion(filLap);
     	
 		imshow( "IMG", img2 );
 		waitKey(0); 

 return 0;
}