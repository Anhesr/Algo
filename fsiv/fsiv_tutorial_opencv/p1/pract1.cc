#include <iostream>
#include <exception>

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
    "{@image1        |      | image1 for compare   }"
    "{@image2        |<none>| image2 for compare   }"
    ;

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

		cv::Mat img = cv::imread(img1, cv::IMREAD_COLOR);

		if (img.empty())
   		   {
   	    	  std::cerr << "Error: no he podido abrir el fichero '" << img1 << "'." << std::endl;
        	  return EXIT_FAILURE;
     		 }

     	cv::Rect2d r = cv::selectROI(img);

     	cv::namedWindow("IMG");



     	cv::Mat imgc = img(r);

     	for (int i = 0; i < img.rows; i++){

       			for (int j = 0; j < img.cols; j++){

       				if (((i < r.y ) or (i > r.y + r.height)) or ((j < r.x) or (j > r.x + r.width))){

        			cv::Vec3b pixel = img.at<cv::Vec3b>(i,j);

            		uchar B = pixel[0];
            		uchar G = pixel[1];
            		uchar R = pixel[2];

            		uchar avg = (B + G + R) / 3;

            		pixel[0] = avg;
            		pixel[1] = avg;
            		pixel[2] = avg;

            		img.at<cv::Vec3b>(i,j) = pixel;

            	}

        	}
    	}

		cv::imshow("IMG", img);

		int wait = cv::waitKey(0);

		std::cout<< wait << std::endl;

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