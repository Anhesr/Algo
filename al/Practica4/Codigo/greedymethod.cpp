
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

	// Obtenemos los errores
	calculateSummations();

	// Eliminamos los puntos alineados
	collinearPointsElimination();

	int numberDominants = getDominantPointsPosition().size();
	int numberApproximation = getNumberPointsPolygonalApproximation(); 
	double actualPointISE;
	double actualMinorISE;
	int actualBestPoint;

	vector <int> dominantPoints = getDominantPointsPosition();
	vector <int> approximationPoints(numberApproximation);

	// Seleccionamos el numero de puntos de la aproximacion 
	// y eliminamos el resto

	int skip = numberDominants/(numberApproximation - 1);

	for(int i = 0; i < numberApproximation - 1; i++)
		approximationPoints[i] = dominantPoints[i * skip];

	approximationPoints[numberApproximation - 1] = dominantPoints[numberDominants - 1];

	// Movemos los puntos dominantes resultantes para mejorar su posicion
	for (int i = 1; i < numberApproximation - 1; i++)
	{
		// Se van probando los diferentes puntos
		for(int j = approximationPoints[i-1] + 1; j < approximationPoints[i+1]; j++)
		{
			actualPointISE = calculateISEValue(approximationPoints[i-1], j) 
			               + calculateISEValue(j, approximationPoints[i+1]);

			// Si no es el primer punto movido
			if(j != approximationPoints[i-1] + 1)
			{
				if(actualPointISE < actualMinorISE)
				{
					actualMinorISE = actualPointISE;
					actualBestPoint = j;
				}
			}

			// Es el primer punto que se prueba
			else
			{
				actualMinorISE = actualPointISE;
				actualBestPoint = j;
			}
		}

		approximationPoints[i] = actualBestPoint;
	}

	for (int i = 0; i < approximationPoints.size(); ++i)
	{
		cout << i + 1 << ": " << approximationPoints[i] << endl; 
	}

	// Se establecen como puntos dominantes los puntos de la aproximacion
	setDominantPointsPosition(approximationPoints);

	// Se calcula la aproximacion poligonal
    calculatePolygonalApproximation();

    // Se establece el numero de puntos de la aproximacion poligonal
    setNumberPointsPolygonalApproximation(getPolygonalApproximation().getNumberPointsDigitalCurve());
}

