
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

  //Completar

  //Summations are calculated
  calculateSummations();

  //Collinear points are eliminated
  collinearPointsElimination();


  int jump;

  jump = (int) ((getOriginalCurve().getNumberPointsDigitalCurve()) / (getNumberPointsPolygonalApproximation() - 1)); // GENERO EL SALTO


  vector <int> newDominantPointPosition; 

  for (int i = 0; i < getOriginalCurve().getNumberPointsDigitalCurve()-1; i = i+jump) // HASTA N-1 PARA NO COGER EL ÚLTIMO AUNQUE COINCIDA
  {                                         // YA QUE LO AÑADO ABAJO SI O SI
    newDominantPointPosition.push_back(i); // VOY METIENDO LOS PUNTOS CORRESPONDIENTES AL SALTO
  }

  newDominantPointPosition.push_back(getOriginalCurve().getNumberPointsDigitalCurve()-1); // AÑADO AL FINAL EL PRIMER/ULTIMO PUNTO PARA CERRAR EL CICLO

  int aux1, aux2;

  double errorT = 999999, error;

    for (int i = 0; i < newDominantPointPosition.size()-2; ++i) // HASTA N-2 PARA NO HACER VIOLACION DE SEGMENTO EN AUX2 DE ABAJO
    {
      aux1 = newDominantPointPosition[i];
      aux2 = newDominantPointPosition[i+2]; // COGO LOS DOS PUNTOS DOMINANTES DE LOS EXTREMOS DE LA COMPARACION
      error = (calculateISEValue(aux1, newDominantPointPosition[i+1])) + (calculateISEValue(newDominantPointPosition[i+1], aux2));
      for (int j = aux1+1; j < aux2; ++j) // Y DOY A ERROR EL VALOR ACTUAL DE LOS PUNTOS DOMINANTES
      { // VOY COMPARANDO CON TODOS LOS PUNTOS INTERMEDIOS DE i e i+2 EL ERROR
        if((error) > (calculateISEValue(aux1, j)) + (calculateISEValue(j, aux2))){
          error = (calculateISEValue(aux1, j)) + (calculateISEValue(j, aux2)); // SI ES MENOR ACTUALIZO EL ERROR
          newDominantPointPosition[i+1] = j; // Y ACTUALIZO EL PUNTO DOMINANTE
        }
      }
    }

  setDominantPointsPosition(newDominantPointPosition); // ACTUALIZO EL VECTOR
  //Obtaining polygonal approximattion
  calculatePolygonalApproximation();

  //Set the number of points of the polygonal approximation
  setNumberPointsPolygonalApproximation(newDominantPointPosition.size());

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
      error = (calculateISEValue(aux1, trueDominantPointPosition[i+1])) + (calculateISEValue(trueDominantPointPosition[i+1], aux2));
      for (int j = aux1+1; j < aux2; ++j) // Y DOY A ERROR EL VALOR ACTUAL DE LOS PUNTOS DOMINANTES
      { // VOY COMPARANDO CON TODOS LOS PUNTOS INTERMEDIOS DE i e i+2 EL ERROR
        if((error) > (calculateISEValue(aux1, j)) + (calculateISEValue(j, aux2))){
          error = (calculateISEValue(aux1, j)) + (calculateISEValue(j, aux2)); // SI ES MENOR ACTUALIZO EL ERROR
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
