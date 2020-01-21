#include <iostream>
#include <exception>
#include <vector>

//Includes para OpenCV, Descomentar según los módulo utilizados.
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>


const cv::String keys =
    "{help h usage ? |      | print this message   }"
    "{@rows          |<none>| path to file         }"
    "{@cols          |<none>| path to file         }"
    "{@size          |<none>| path to file         }"
    "{@calibfile     |<none>| path to file         }"
    "{@input         |<none>| path to file         }"
    ;
using namespace std;
using namespace cv;

vector<Point3f> create_obj_points(int cols,int rows,float size);
void draw_model(Mat img,float size, Mat camera_mat,Mat dist_coefs,Mat rvec,Mat tvec);


void draw_model(Mat img,float size, Mat camera_mat,Mat dist_coefs,Mat rvec,Mat tvec){

    std::vector<Point2d> img_points;
    std::vector<Point3d> ejes;

    ejes.push_back(Point3d(0,0,0));
    ejes.push_back(Point3d(size,0,0));
    ejes.push_back(Point3d(0,size,0));
    ejes.push_back(Point3d(0,0,-1*size));

    ejes.push_back(Point3d(size,size,0));
    ejes.push_back(Point3d(size,size,-1*size));
    ejes.push_back(Point3d(size,0,-1*size));
    ejes.push_back(Point3d(0,size,-1*size));

    projectPoints(ejes,rvec,tvec,camera_mat,dist_coefs,img_points);

   	line(img, img_points[0],img_points[1], Scalar(255,0,0), 3);
   	line(img, img_points[0],img_points[2], Scalar(0,255,0), 3);
   	line(img, img_points[0],img_points[3], Scalar(0,0,255), 3);
    line(img, img_points[3],img_points[4], Scalar(0,0,255), 3);
    line(img, img_points[5],img_points[6], Scalar(0,0,255), 3);
    line(img, img_points[6],img_points[7], Scalar(0,0,255), 3);
}

int main (int argc, char* const* argv)
{
  int retCode=EXIT_SUCCESS;

  try {

      cv::CommandLineParser parser(argc, argv, keys);
      parser.about("Application name v1.0.0");
      if (parser.has("help"))
      {
          parser.printMessage();
          return 0;
      }
      int rows= parser.get<int>(0);
      int cols= parser.get<int>(1);
      float size= parser.get<float>(2);
      String calibfile= parser.get<String>(3);
      String inputfile= parser.get<String>(4);

      if (!parser.check())
      {
          parser.printErrors();
          return 0;
      }

       //Abrir el video
      VideoCapture vid ;
      vid.open(inputfile);

      if(! vid.isOpened()){
        cout <<"Eror"<< endl;
        return EXIT_FAILURE;
      }
      cv::FileStorage intr (calibfile,FileStorage::READ);
      if(! intr.isOpened()){
        cout <<"Eror"<< endl;
        return EXIT_FAILURE;
      }

      Mat camera_mat;
      Mat dist_coefs;
      intr["camera-matrix"]>> camera_mat;
      intr["distortion-coefficients"]>> dist_coefs;

      Mat frame;

      vid >> frame;

      int key = 0;
      vector<Point3f> obj_pts= create_obj_points(cols-1,rows-1,size);

      while(!frame.empty() && key != 27){
           cv::imshow("video", frame);
           std::vector<Point2f> corners;

           if(findChessboardCorners(frame,cv::Size(cols-1,rows-1),corners,CALIB_CB_FAST_CHECK)){
                Mat gray;
                cvtColor(frame,gray,COLOR_BGR2GRAY);
                cornerSubPix(gray,corners,Size(11,11),Size(-1,-1), TermCriteria(CV_TERMCRIT_EPS +CV_TERMCRIT_ITER,30,0.1));
                Mat rvec;
                Mat tvec;
                solvePnP(obj_pts, corners,camera_mat,dist_coefs,rvec,tvec);
                draw_model(frame,size,camera_mat,dist_coefs,rvec,tvec);
                imshow("video", frame);
           }
           else{
               imshow("video", frame);
           }
           key= waitKey(20) & 0xff;

           vid >> frame;
      }


  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}

vector<Point3f> create_obj_points(int cols,int rows,float size){
	std::vector<cv::Point3f> objectPoints;
	for(int y=0; y<rows; ++y) {
   		for(int x=0; x<cols; ++x){
        	objectPoints.push_back(cv::Point3f(x*size,y*size,0));
   		}
	}
	return objectPoints;
}
