/*!
  Esto es un esqueleto de programa para usar en las prácticas
  de Visión Artificial.

  Se supone que se utilizará OpenCV.

  Para compilar, puedes ejecutar:
    g++ -Wall -o esqueleto esqueleto.cc `pkg-config opencv --cflags --libs`

*/

#include <iostream>
#include <exception>

//Includes para OpenCV, Descomentar según los módulo utilizados.
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/calib3d/calib3d.hpp>

using namespace cv;
using namespace std;

const cv::String keys =
    "{help h usage ? |      | print this message   }"
    "{path           |.     | path to file         }"
    "{@image1        |      | image1 for compare   }"
    ;


cv::Mat normalizeInput(cv::Mat &input)
{
  cv::Mat output = cv::Mat::zeros(input.rows, input.cols, CV_32FC1);

  //COMPLETAR

  // Busca el valor maximo y minimo de los pixeles de la imagen
  float max = input.at<float>(0, 0);
  float min = input.at<float>(0, 0);

  for(int i = 0; i < input.rows; i++)
  {
  	for(int j = 0; j < input.cols; j++)
  	{
  		if(input.at<float>(i, j) > max)
  			max = input.at<float>(i, j);

  		else if(input.at<float>(i, j) < min)
  			min = input.at<float>(i, j);
  	}
  }

  std::cout << "Max: " << max << "\nMin: " << min << endl;

  // Normaliza en el rango [0.0, 1.0]
  for(int i = 0; i < input.rows; i++)
  {
  	for(int j = 0; j < input.cols; j++)
  	{
  		output.at<float>(i, j) = (input.at<float>(i, j) - min)/(max - min);
  	}
  }

  return output;
}




int main (int argc, char* const* argv)
{
  int retCode=EXIT_SUCCESS;
  
  try {    

      cv::CommandLineParser parser(argc, argv, keys);
      parser.about("Normalize Application name v1.0.0");
      if (parser.has("help"))
      {
          parser.printMessage();
          return 0;
      }
      cv::String path = parser.get<cv::String>("path");
      cv::String img = parser.get<cv::String>(0);
      if (!parser.check())
      {
          parser.printErrors();
          return 0;
      }

    /*Ahora toca que tu rellenes con lo que hay que hacer ...*/

    cv::Mat input = cv::imread(img);
    cv::imshow("Original", input);
    cv::waitKey(0);
    cout<<input.type()<<endl;
    cout<<endl;
    input.convertTo(input, CV_32FC1);


    cv::Mat output_norm;
    cv::normalize(input, output_norm, 1.0, 0.0, NORM_MINMAX);
    //input.convertTo(output_norm, CV_32FC1, 1.00/<max>, 0.00);
    cv::imshow("Normalize", output_norm);
    cv::waitKey(0);


    cv::Mat output = normalizeInput(input);
    cv::imshow("Normalize manual", output);
    cv::waitKey(0);


    for(int i = 0; i < input.rows; i++)
  	{
  		for(int j = 0; j < input.cols; j++)
  		{
  			std::cout << output_norm.at<float>(i, j) << " : " << output.at<float>(i, j) << endl;
  		}
  	}

    
  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}
