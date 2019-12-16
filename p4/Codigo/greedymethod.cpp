
#include <vector>    // necesario para el contenedor vector
#include "algorithm.hpp"
#include "greedymethod.hpp"
#include "digitalcurve.hpp"
//#include "heapvectorMasood.hpp"
//#include "nodoMasood.hpp"



using namespace std;

/* Functions for Collinear suppression method */

//Constructor.

GreedyMethod::GreedyMethod(char *fileName, int numberPointsPolygonalApproximation)
{
  //A digital curve is created to load the digital curve in file
	DigitalCurve dc(fileName);
  
  //Digital curve as saved as original curve
  setOriginalCurve(dc);

  //Set the number of points of the polygonal approximation
  setNumberPointsPolygonalApproximation(numberPointsPolygonalApproximation);
}

//Destructor
GreedyMethod::~GreedyMethod()
{
}

void GreedyMethod::apply()
{

  int nPts=getNumberPointsPolygonalApproximation();

  calculateSummations();

  collinearPointsElimination();

  vector <int> domainPoints=getDominantPointsPosition();

  int myN=domainPoints.size()/(nPts-1);

  calculatePolygonalApproximationGreedy(myN);

}

void Algorithm::calculatePolygonalApproximationGreedy(int myN){

      DigitalCurve originalCurve;

      originalCurve=getOriginalCurve();

      for(int i = 0; i < _dominantPointPosition.size();){
        _polygonalApproximation.insertPointDigitalCurve(getOriginalCurve().getPointDigitalCurve(_dominantPointPosition[i]));
        trueDominantPointPosition.push_back(i);
        i=i+myN;
      }

      if (getOriginalCurve().isClosed() and not getPolygonalApproximation().isClosed()){
        _polygonalApproximation.insertPointDigitalCurve(getPolygonalApproximation().getPointDigitalCurve(0));
       }
       
      long double error= 1000000000000000.0;
      int pos;

      for (int i = 1; i < trueDominantPointPosition.size() - 1 ;i++)
      {

        for(int j = trueDominantPointPosition[i-1]+1; j < trueDominantPointPosition[i+1];j++){

          if(error > calculateISEValue(trueDominantPointPosition[i-1], j ) + calculateISEValue(j, trueDominantPointPosition[i+1]) ){

            error=calculateISEValue(trueDominantPointPosition[i-1], j ) + calculateISEValue(j, trueDominantPointPosition[i+1]);
            
            trueDominantPointPosition[i]=j;
          }
        }
        error= 1000000000000000000000.0;
      }

      setDominantPointsPosition(trueDominantPointPosition);

      calculatePolygonalApproximation();

      //Set the number of points of the polygonal approximation
      setNumberPointsPolygonalApproximation(newDominantPointPosition.size());

}


long double Algorithm::getGreedyISE()
{
  long double ISE = 0.0;

  for(int i = 0; i < trueDominantPointPosition.size() -1; i++)
  {
    ISE += calculateISEValue(trueDominantPointPosition[i], trueDominantPointPosition[i+1]);
  }
  return ISE;
}
