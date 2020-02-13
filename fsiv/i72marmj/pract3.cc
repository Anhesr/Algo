/*!
  Esto es un esqueleto de programa para usar en las prácticas
  de Visión Artificial.

  Se supone que se utilizará OpenCV.

  Para compilar, puedes ejecutar:
    g++ -Wall -o esqueleto esqueleto.cc `pkg-config opencv --cflags --libs`

*/

#include <iostream>
#include <exception>
#include <algorithm>


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
    "{f filter       | 0    | filtro		       }"
    "{g ganancia     | 1.0  | ganancia			   }"
    "{@image1        |      | image1 for compare   }"
    "{@image2        |<none>| image2 for compare   }"
    ;

cv::Mat create_sharp_filter(int tipo, float g)
{
	cv::Mat filter(3, 3, CV_32FC1);

	if ((g >= 0.0) and ((tipo == 0) or (tipo == 1)))
	{
		if ( tipo == 0 )
		{
			filter = (Mat_<double>(5, 5) << 0,  0,    0,   0,   0, 
                                      0,  0,   -1,   0,   0, 
                                      0, -1,  g+4,  -1,   0,
                                      0,  0,   -1,   0,   0,
                                      0,  0,    0,   0,   0);
		}

		else if ( tipo == 1 )
		{
			filter = (Mat_<double>(3, 3) << -1,  -1,  -1,
                                      -1,  g+8, -1,
                                      -1,  -1,  -1);
		}
	}

	else
	{
		std::cout << "\n\n > ERROR. Alguno de los valores de entrada (g o f) fuera de rango.\n\n";
		exit(-1);
	}
	
	filter.convertTo(filter, CV_32FC1);

	if(filter.type() != CV_32FC1)
	{
		std::cout << "\n\n > ERROR. Error con el filtro.\n\n";
		exit(-1);
	}


	return filter;
}

//******************************************************************

void aplicarConvolucion(const int x, const int y, const cv::Mat& in, const cv::Mat& filter, cv::Mat& out)
{

  float pixel = 0.0;

  for (int i = 0; i < filter.rows; ++i)
  {
    for (int j = 0; j < filter.cols; ++j)
    {
      pixel += in.at<float>((x - ((filter.rows-1)/2) + i),(y - ((filter.cols-1)/2) + j)) * filter.at<float>(i, j);
    }
  }

  out.at<float>(x - ((filter.rows-1)/2), y - ((filter.rows-1)/2)) = pixel;

}

/*00 01 02 03 04
10 11 12 13 14
20 21 22 23 24
30 31 32 33 34
40 41 42 43 44*/

//******************************************************************

void convolve(const cv::Mat& in, const cv::Mat& filter, cv::Mat& out, int border_type=0)
{
  vector<Mat> channelsIn,channelsOut;
  Mat inResized=Mat::zeros(in.rows + ((filter.rows-1)/2),in.cols + ((filter.cols-1)/2) ,in.type());
  out=Mat::zeros(in.rows,in.cols,in.type());

  split(in,channelsIn);
  split(out,channelsOut);

  for(int i=0;i<in.channels();i++){
    copyMakeBorder(channelsIn[i],channelsIn[i],((filter.rows-1)/2),((filter.rows-1)/2),((filter.rows-1)/2),((filter.rows-1)/2),BORDER_CONSTANT,0);
  }

  for (int i = ((filter.rows-1)/2); i < inResized.rows-((filter.rows-1)/2); ++i)
  {
    for (int j = ((filter.rows-1)/2); j < inResized.cols-((filter.rows-1)/2); ++j)
    {
      for (int k = 0; k < in.channels(); ++k)
      {
        aplicarConvolucion(i,j,channelsIn[k],filter,channelsOut[k]);
      }
    }
  }
  merge(channelsOut,out);
  imshow("IMG Normal",in);
  imshow("IMG Realzada",out);
}

//******************************************************************

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
      int filterOption = parser.get<int>("filter");

      if((filterOption != 0) and (filterOption != 1))
      {
          cout << "\nValor de filtro invalido." << endl << endl;

          cout << "Valores permitidos: <-f=0> o <-f=1>" << endl;
          return 0;
      }

      float ganancia = parser.get<float>("g");

      if(ganancia < 0)
      {
          cout << "\nValor de ganancia invalido." << endl << endl;

          cout << "Valores permitidos: <-g={Value >= 0.0}>" << endl;
          return 0;
      }

      cv::String input = parser.get<cv::String>(0);
      cv::String output = parser.get<cv::String>(1);
      if (!parser.check())
      {
          parser.printErrors();
          return 0;
      }

    /*Ahora toca que tu rellenes con lo que hay que hacer ...*/

    int key;
    cv::Mat imgIn;
    cv::Mat imgOut;
    cv::Mat filter;

    imgIn = cv::imread(input);

    filter = create_sharp_filter(filterOption, ganancia);

    imgIn.convertTo(imgIn, CV_32FC1, 1.00/255.00, 0.00);

    convolve(imgIn, filter, imgOut);

    key = cv::waitKey(0) & 0xff;

    //Guardar resultado / Cancelar 

    if(key != 27)
    {
      std::cout << "\nGuardando imagen procesada..." << std::endl;
      imgOut.convertTo(imgOut, CV_32FC1, 255.00, 0.00);
      cv::imwrite(output, imgOut);
    }

    else
    {
      std::cout << "\nCancelando proceso..." << std::endl;
    }

    
  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}
