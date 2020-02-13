#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <cmath>
#include <iostream>

using namespace cv;

/// Global Variables
const int C_max = 200;
int C;
int B;
int G;
double alpha;
double beta;


Mat img1;
Mat img2;
Mat dst;

const cv::String keys =
    "{help h usage ? |      | print this message   }"
    "{path           |.     | path to file         }"
    "{fps            | -1.0 | fps for output video }"
    "{N count        |100   | count of objects     }"
    "{ts timestamp   |      | use time stamp       }"
    "{@image1        |      | image1 for compare   }"
    "{@image2        |<none>| image2 for compare   }"
    "{@repeat        |1     | number               }"
    "{i      		 |      | interactive mode     }"
    "{c      		 |1.0   | contraste		       }"
    "{b      		 |0.0   | brillo		       }"
    "{g      		 |1.0   | gamma			       }"
    ;



void ModificarImg( int, void* )
{
 double Cont= C/100.0;
 double Bri=(B/100.0)-1.0;
 double Gam=C/100.0;

 for(int i=0;i< img1.rows;i++){
  for (int j = 0; j < img1.cols; ++j)
  {
    Vec3f pixel=img1.at<Vec3f>(i,j);
    pixel[0]=min(max((Cont*(pow(pixel[0],Gam))+Bri),0.0),1.0 ) ;
    pixel[1]=min(max((Cont*(pow(pixel[1],Gam))+Bri),0.0),1.0 ) ;
    pixel[2]=min(max((Cont*(pow(pixel[2],Gam))+Bri),0.0),1.0 ) ;
    img2.at<Vec3f>(i,j)= pixel;
  }
 }
 imshow("IMG",img2);
}




int main( int argc, char** argv )
{


 cv::CommandLineParser parser(argc, argv, keys);
      parser.about("Application name v1.0.0");
      if (parser.has("help"))
      {
          parser.printMessage();
          return 0;
      }
      cv::String im1 = parser.get<cv::String>(0);
      cv::String im2 = parser.get<cv::String>(1);
      int repeat = parser.get<int>(2);
      if (!parser.check())
      {
          parser.printErrors();
          return 0;
      }

     img1 = cv::imread(im1, cv::IMREAD_COLOR);

     img2 = cv::imread(im2, cv::IMREAD_COLOR);



 	namedWindow("IMG", 1);

 	bool comp = parser.get<bool>("i");


 	if(comp == true){
 	C =100;
 	B =100;
 	G =100;

 	img1.convertTo(img1,CV_32F,(1.0/255),0.0);
 	img2.convertTo(img2,CV_32F,(1.0/255),0.0);

 	createTrackbar( "C", "IMG", &C, C_max, ModificarImg );
 	createTrackbar( "B", "IMG", &B, C_max, ModificarImg );
 	createTrackbar( "G", "IMG", &G, C_max, ModificarImg );


 	ModificarImg( C, 0 );
	ModificarImg( B, 0 );
	ModificarImg( G, 0 );
	waitKey(0);
	}
	if(comp == false){

		img1.convertTo(img1,CV_32F,(1.0/255),0.0);
 		img2.convertTo(img2,CV_32F,(1.0/255),0.0);

		double Cont=parser.get<double>("c");
		double Bri=parser.get<double>("b");
		double Gam=parser.get<double>("g");

		for (int i = 0; i < img1.rows; i++){

    	   	for (int j = 0; j < img1.cols; j++){

    	    	Vec3f pixel = img1.at<Vec3f>(i,j);

				pixel[0]= min(max((Cont*(pow(pixel[0],Gam))+Bri),0.0),1.0 ) ;
				pixel[1]= min(max((Cont*(pow(pixel[1],Gam))+Bri),0.0),1.0 ) ;
				pixel[2]= min(max((Cont*(pow(pixel[2],Gam))+Bri),0.0),1.0 ) ;

    	 		img2.at<Vec3f>(i,j) = pixel;

   		    }
   		}
     	
 		imshow( "IMG", img2 );
 		waitKey(0);
	}

 return 0;
}


