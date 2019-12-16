
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

      for (int i = 0; i < trueDominantPointPosition.size()-2; ++i) // HASTA N-2 PARA NO HACER VIOLACION DE SEGMENTO EN AUX2 DE ABAJO
    {
      int aux1 = trueDominantPointPosition[i];
      int aux2 = trueDominantPointPosition[i+2]; // COGO LOS DOS PUNTOS DOMINANTES DE LOS EXTREMOS DE LA COMPARACION
      error = abs(calculateISEValue(aux1, trueDominantPointPosition[i+1])) + abs(calculateISEValue(trueDominantPointPosition[i+1], aux2));
      for (int j = aux1+1; j < aux2; ++j) // Y DOY A ERROR EL VALOR ACTUAL DE LOS PUNTOS DOMINANTES
      { // VOY COMPARANDO CON TODOS LOS PUNTOS INTERMEDIOS DE i e i+2 EL ERROR
        if(abs(error) > abs(calculateISEValue(aux1, j)) + abs(calculateISEValue(j, aux2))){
          error = abs(calculateISEValue(aux1, j)) + abs(calculateISEValue(j, aux2)); // SI ES MENOR ACTUALIZO EL ERROR
          trueDominantPointPosition[i+1] = j; // Y ACTUALIZO EL PUNTO DOMINANTE
        }
      }
    }

      setDominantPointsPosition(trueDominantPointPosition);

      calculatePolygonalApproximation();

      //Set the number of points of the polygonal approximation
      setNumberPointsPolygonalApproximation(trueDominantPointPosition.size());

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
