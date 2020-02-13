//! \file lbp.cpp
//! Utils for LBP

#include "lbp.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace cv;

static const int uniform[256] =
{   
0,1,2,3,4,58,5,6,7,58,58,58,8,58,9,10,11,58,58,58,58,58,58,58,12,58,58,58,13,58,
14,15,16,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,17,58,58,58,58,58,58,58,18,
58,58,58,19,58,20,21,22,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,
58,58,58,58,58,58,58,58,58,58,58,58,23,58,58,58,58,58,58,58,58,58,58,58,58,58,
58,58,24,58,58,58,58,58,58,58,25,58,58,58,26,58,27,28,29,30,58,31,58,58,58,32,58,
58,58,58,58,58,58,33,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,34,58,58,58,58,
58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,
58,35,36,37,58,38,58,58,58,39,58,58,58,58,58,58,58,40,58,58,58,58,58,58,58,58,58,
58,58,58,58,58,58,41,42,43,58,44,58,58,58,45,58,58,58,58,58,58,58,46,47,48,58,49,
58,58,58,50,51,52,58,53,54,55,56,57
};


void fsiv_lbp(const cv::Mat & imagem, cv::Mat & lbp)
{
    lbp = cv::Mat::zeros(imagem.rows, imagem.cols, CV_8UC1);
    cv::Mat imgC;
    cvtColor(imagem,imgC,COLOR_BGR2GRAY);
    copyMakeBorder(imgC,imgC,1,1,1,1,BORDER_CONSTANT,0);

    for (int i = 1; i < imgC.rows-1; ++i)
    {
        for (int j = 1; j < imgC.cols-1  ; ++j)
           {
                uchar center=imgC.at<uchar>(i,j);
                int centR=0;
                if( imgC.at<uchar>(i-1,j-1) > center){
                centR = centR + pow(2,7);
                }// 7
                if(imgC.at<uchar>(i-1,j) > center){
                    centR = centR + pow(2,6);
                }// 6
                if(imgC.at<uchar>(i-1,j+1) > center){  
                    centR = centR + pow(2,5);
                }// 5
                if(imgC.at<uchar>(i,j+1) > center){
                    centR = centR + pow(2,4);
                }//4
                if(imgC.at<uchar>(i+1,j+1) > center){
                    centR = centR + pow(2,3);
                }//3
                if(imgC.at<uchar>(i+1,j) > center) {
                    centR = centR + pow(2,2);
                }//2
                if(imgC.at<uchar>(i+1,j-1) > center) {
                    centR = centR + pow(2,1);
                }//1
                if(imgC.at<uchar>(i,j-1) > center) {
                    centR = centR + pow(2,0);
                }//0
                lbp.at<uchar>(i-1,j-1) = centR;
           }   
    }
}

void fsiv_ulbp(const cv::Mat & imagem, cv::Mat & ulbp)
{
    ulbp = cv::Mat::zeros(imagem.rows, imagem.cols, CV_8UC1);
	//TODO compute u-LBP centRs.
}

void fsiv_lbp_hist(const cv::Mat & lbp, cv::Mat & lbp_hist, bool norm, int nbins)
{	    
    vector<Mat> images={lbp};
    vector<int> channels={0},size={nbins};
    vector<float> range={0,(float)nbins};

    calcHist(images,channels,Mat(),lbp_hist,size,range);

    if(norm){
        lbp_hist=lbp_hist.mul(1.0/(lbp.cols*lbp.rows));
    }
    lbp_hist=lbp_hist.reshape(0,1);
}
void fsiv_lbp_desc(const cv::Mat & image, cv::Mat & lbp_desc, const int *ncells, bool normalize, int nbins)
{
	//TODO compute lbp desc.
    if (normalize)
    {
		//TODO normaliza lbp_desc to mett cv::sum(lbp_desc)[0] == 1.0
		;
    }
}

void fsiv_lbp_disp(const cv::Mat & lbpmat, const std::string & winname)
{
	imshow(winname,lbpmat);
	waitKey(0);
}

float fsiv_chisquared_dist(const cv::Mat & h1, const cv::Mat & h2)
{
	float dist= 0.0;
    for (int i = 0; i < h1.cols; ++i)
    {
        if(h1.at<float>(0,i) != 0 and h2.at<float>(0,i) != 0){
        dist+= ((pow( abs (h1.at<float>(0,i) - h2.at<float>(0,i)) , 2)) /
                (h1.at<float>(0,i) + h2.at<float>(0,i)));
        }
    }
    dist*=0.5;
    return dist;
}
