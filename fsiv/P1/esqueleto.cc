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

using namespace std;
using namespace cv;

const cv::String keys =
    "{help h usage ? |      | print this message   }"
    "{@image1        |      | image1 for compare   }"
    "{@image2        |<none>| image2 for compare   }"
    ;

cv::Mat imgOriginal;
cv::Mat imgGray;
bool dibujar = false;


void mouseEvents(int event, int x, int y, int flags, void* userdata)
{
  cv::Point coord(x, y);
  if (event == EVENT_LBUTTONDOWN)  {
    dibujar = true;
    static_cast<Point*>(userdata)[0] = coord;
    static_cast<Point*>(userdata)[1] = coord;
  }    
  if ((event == EVENT_MOUSEMOVE) and (dibujar == true))  {
    static_cast<Point*>(userdata)[1] = coord;
    imgGray = imgOriginal.clone();
    cv::rectangle(imgGray, static_cast<Point*>(userdata)[0], static_cast<Point*>(userdata)[1], cv::Scalar(255, 0, 180), 2);
    cv::imshow("Practica 1 - Realce", imgGray);
  }
  if (event == EVENT_LBUTTONUP)  {
    dibujar = false;
    static_cast<Point*>(userdata)[1] = coord;
  }
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

      cv::String img1 = parser.get<cv::String>(0);
      cv::String img2 = parser.get<cv::String>(1);
      if (!parser.check())
      {
          parser.printErrors();
          return 0;
      }

    /*Ahora toca que tu rellenes con lo que hay que hacer ...*/

    // Carga de la imagen
    imgOriginal = cv::imread(img1, cv::IMREAD_COLOR);

    // Seleccion de la ROI
    cv::Point Puntos[2];

    cv::namedWindow("Practica 1 - Realce");
    setMouseCallback("Practica 1 - Realce", mouseEvents, Puntos);
    cv::imshow("Practica 1 - Realce", imgOriginal);
    waitKey(0);

    // Modificacion de la imagen
    for(int i = 0; i < imgOriginal.rows; i++)
    {
      for(int j = 0; j < imgOriginal.cols; j++)
      {
        cv::Vec3b pixel = imgOriginal.at<Vec3b>(i, j);

        uchar B = pixel[0];
        uchar G = pixel[1];
        uchar R = pixel[2];

        if(((i < min(Puntos[0].y, Puntos[1].y)) or (i > max(Puntos[0].y, Puntos[1].y))) or 
           ((j < min(Puntos[0].x, Puntos[1].x)) or (j > max(Puntos[0].x, Puntos[1].x))))
        {
          uchar avg = (B + G + R) / 3;

          pixel[0] = avg;
          pixel[1] = avg;
          pixel[2] = avg;
        }

        imgGray.at<Vec3b>(i, j) = pixel;
      }
    }

    cv::imshow("Practica 1 - Realce", imgGray);

    // Esperando cualquier tecla
    int key = cv::waitKey(0) & 0xff;

    if (key != 27) // 27 es ESC
    {
      cout << "\nSaving image...\n";
      cv::imwrite(img2, imgGray);
    }

    else
    {
      cout << "\nLeaving without save...\n";
    }
    
  }
  catch (std::exception& e)
  {
    std::cerr << "Capturada excepcion: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}
