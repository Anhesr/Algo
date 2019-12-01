
#include <vector>    // necesario para el contenedor vector
#include "algorithm.hpp"
#include "dynamicprogrammingmethod.hpp"
#include "digitalcurve.hpp"
//#include "heapvectorMasood.hpp"
//#include "nodoMasood.hpp"



using namespace std;

/* Functions for Collinear suppression method */

//Constructor.

DynamicProgrammingMethod::DynamicProgrammingMethod(char *fileName,int numberPointsPolygonalApproximation)
{
  //A digital curve is created to load the digital curve in file
	DigitalCurve dc(fileName);
  	setOriginalCurve(dc);

	setNumberPointsPolygonalApproximation(numberPointsPolygonalApproximation);

  //Digital curve as saved as original curve
}

//Destructor
DynamicProgrammingMethod::~DynamicProgrammingMethod()
{
}

void DynamicProgrammingMethod::apply()
{
	//Summations are calculated
	calculateSummations();

	int Npts=getOriginalCurve().getNumberPointsDigitalCurve();
	int Mpts=getNumberPointsPolygonalApproximation();

	vector <vector <double> > E(Npts+1,vector <double> (Mpts+1));

	vector <vector <int> > father(Npts+1,vector <int> (Mpts+1));

	vector <int> domaintPoints(Mpts);

	double min;

	for (int i = 2; i < Npts+1; ++i)
	{
		for (int j = 1; j < Mpts+1; ++j)
		{
			E[i][j]=999999;
		}
	}

	E[1][1]=0;

	for(int m = 2 ; m <= Mpts ; m++)
	{

		for (int n = m; n <= Npts; n++)
		{

			for (int k = m-1; k <= n-1; ++k)
			{

				min=E[k][m-1] + calculateISEValue(k-1,n-1);

				if( E[n][m] > min ){

					E[n][m]=min;
					father[n][m]=k;

				}
			}	
		}
	}


	int sig= Npts;
	domaintPoints.clear();
	domaintPoints.insert(domaintPoints.begin(),Npts-1);
	for (int i = Mpts; i > 1; i--)
	{
		sig=father[sig][i];
		domaintPoints.insert(domaintPoints.begin(),sig-1);

	}

	setDominantPointsPosition(domaintPoints);

	calculatePolygonalApproximation();

}