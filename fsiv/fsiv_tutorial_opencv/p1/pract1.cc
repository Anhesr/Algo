#include <iostream>
#include <exception>

//Includes para OpenCV, Descomentar según los módulo utilizados.
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace cv;

cv::Mat img;
cv::Mat imgaux;
bool dibujar=false;

const cv::String keys =
    "{help h usage ? |      | print this message   }"
    "{@image1        |      | image1 for compare   }"
    "{@image2        |<none>| image2 for compare   }"
    ;

void mouseEvents(int event,int x ,int y, int flags,void *userdata){
  Point punto(x,y);
  if(event == EVENT_LBUTTONDOWN){
    dibujar=true;
    static_cast<Point*>(userdata)[0]=punto;
    static_cast<Point*>(userdata)[1]=punto;
  }
  if((event == EVENT_MOUSEMOVE) and (dibujar==true)){
    static_cast<Point*>(userdata)[1]=punto;
    imgaux=img.clone();
    rectangle(imgaux,static_cast<Point*>(userdata)[0],static_cast<Point*>(userdata)[1],Scalar(255,0,0),2);
    imshow("IMG",imgaux);
  }
  if(event == EVENT_LBUTTONUP){
    dibujar=false;
    static_cast<Point*>(userdata)[1]=punto;
  }
}

int
main (int argc, char* const* argv)
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
      cv::String img1 = parser.get<cv::String>(0);
      cv::String img2 = parser.get<cv::String>(1);
      if (!parser.check())
      {
          parser.printErrors();
          return 0;
      }

      	//Carga de la imagen 

		img = cv::imread(img1, cv::IMREAD_COLOR);

		if (img.empty())
   		   {
   	    	  std::cerr << "Error: no he podido abrir el fichero '" << img1 << "'." << std::endl;
        	  return EXIT_FAILURE;
     		 }

      Point punto[2];     	

     	cv::namedWindow("IMG");
      setMouseCallback("IMG",mouseEvents,punto);
      imshow("IMG",img);
      waitKey(0);
      
      for (int i = 0; i < img.rows; ++i)
      {
        for (int j = 0; j < img.cols; ++j)
        {
          Vec3b pixel=img.at<Vec3b>(i,j);
            uchar B = pixel[0];
            uchar G = pixel[1];
            uchar R = pixel[2];
          if( (i < min(punto[0].y,punto[1].y) or (i > max(punto[0].y,punto[1].y))) or
          ((j < min(punto[0].x,punto[1].x)) or (j > max(punto[0].x,punto[1].x)))) {
            uchar avg= (B+G+R)/3;
            pixel[0]=avg;
            pixel[1]=avg;
            pixel[2]=avg;
          }
          imgaux.at<Vec3b>(i,j)=pixel;
        }
      }

		cv::imshow("IMG", imgaux);

		int wait = cv::waitKey(0);


		if (wait != 27){

			cv::imwrite(img2,img);
		}

  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}