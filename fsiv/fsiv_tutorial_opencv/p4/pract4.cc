#include <iostream>
#include <exception>
#include <vector>

//Includes para OpenCV, Descomentar según los módulo utilizados.
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core/types_c.h>


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
  vector<Point3d> ejes;
  vector<Point2d> imgp;
  ejes.push_back(Point3d(0,0,0));
  ejes.push_back(Point3d(size,0,0));
  ejes.push_back(Point3d(0,size,0));
  ejes.push_back(Point3d(0,0,-1*size));

  projectPoints(ejes,rvec,tvec,camera_mat,dist_coefs,imgp);

  line(img,imgp[0],imgp[1],Scalar(255,0,0),3);
  line(img,imgp[0],imgp[2],Scalar(255,0,0),3);
  line(img,imgp[0],imgp[3],Scalar(255,0,0),3);


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
           vector<Point2f> corners;
           if(findChessboardCorners(frame,Size(cols-1,rows-1),corners,CALIB_CB_FAST_CHECK)){
            Mat gray;
            cvtColor(frame,gray,COLOR_BGR2GRAY);
            cornerSubPix(gray,corners,Size(11,11),Size(-1,-1),TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
            Mat rvec,tvec;
            solvePnP(obj_pts,corners,camera_mat,dist_coefs,rvec,tvec);
            draw_model(frame,size,camera_mat,dist_coefs,rvec,tvec);
            imshow("video",frame);
           }
           else{
            imshow("video",frame);
           }
           key=waitKey(20) & 0xff;
           vid>>frame;
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
  vector<Point3f> obj;
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      obj.push_back(Point3f(j*size,i*size,0));
    }
  }
  return obj;
}
