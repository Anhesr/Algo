//! \file test_lbp.cpp
//! \author FSIV-UCO

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "lbp.h"

using namespace std;

const cv::String keys =
    "{help h usage ? |      | print this message.}"
//    "{u uniform      |      | use uLBP.}"
//    "{c colunms      |0     | Build descriptor using a grid with c colums.}"
//    "{r rows         |0     | Build descriptor using a grid with r rows.}"
    "{@image1        |<none>| path to input image.}"
    "{@image2        |      | path to second image, for comparison.}"
    ;

int main(int argc, char * argv[])
{
   cv::CommandLineParser parser(argc, argv, keys);
   parser.about("Test LBP implementation.");
   if (parser.has("help"))
   {
      parser.printMessage();
      return 0;
   }
   cv::String im1 = parser.get<cv::String>(0);
   cv::String im2 = parser.get<cv::String>(1);
   if (!parser.check())
     {
         parser.printErrors();
         return 0;
     }

    // Load the image1
    cv::Mat image1;

    //Load the image2 (if it is set).
    cv::Mat image2;

    cv::Mat lbp1,lbp2,hist1,hist2;

    image1 = cv::imread(im1);

    image2 = cv::imread(im2);

    if(!image2.data)
    {
      cv::flip(image1,image2,0);
    }

    fsiv_lbp(image1,lbp1);

    fsiv_lbp_disp(lbp1,"lbp imagen 1");

    fsiv_lbp(image2,lbp2);

    fsiv_lbp_disp(lbp2,"lbp imagen 2");

    fsiv_lbp_hist(lbp1,hist1,true,256);

    fsiv_lbp_hist(lbp2,hist2,true,256);

    cout<<"La distancia chi^2 entre los dos histogramas es : "<<fsiv_chisquared_dist(hist1,hist2) <<endl;
   
   return 0;
}
