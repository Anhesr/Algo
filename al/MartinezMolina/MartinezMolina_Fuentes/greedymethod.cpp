
#include <vector>    // necesario para el contenedor vector
#include <cmath>
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

	//**********************************************
	//Summations are calculated
	calculateSummations();

  	//Collinear points are eliminated
  	collinearPointsElimination();
  	//**********************************************

    vector<int> dominantPoints = getDominantPointsPosition();
  	vector<int> dominantPointsChoosen;
  	vector<int> possitionPoints;

 	  chooseNumberPointsPolygonalApproximation(dominantPoints, dominantPointsChoosen, possitionPoints);

  	//**********************************************
    // Move the dominant Points for minimize the ISE

    // NOTA: En la ultima pasada, obtiene un valor de ISE negativo que no se deberia dar.

    int numberPoints = getOriginalCurve().getNumberPointsDigitalCurve();
    int numberPointsForChoose = dominantPointsChoosen.size();

  	int previousDominant, nextDominant;
  	int pos;

  	long double ISE, menorError;
  	int possitionBestDominant;

  	for (int i = 1; i < numberPointsForChoose; ++i)
  	{
  		ISE = 0.0;

      // Choose previous and next dominant for dominantPointsChoosen[i]
  		previousDominant = dominantPointsChoosen[i - 1];

  		if (i + 1 == numberPointsForChoose)
  		{
  			nextDominant = dominantPointsChoosen[1];
  		}

  		else
  		{
  			nextDominant = dominantPointsChoosen[i + 1];
  		}

      // Set the value of pos to the value of the previous dominant position + 1
  		pos = previousDominant + 1;

      //cout << "> Intervalo: " << previousDominant << " - " << nextDominant << endl;

      // Look for the dominant point with the lowest ISE and save its position
  		while(pos != nextDominant)
  		{
  			ISE = abs(calculateISEValue(previousDominant, pos)) + abs(calculateISEValue(pos, nextDominant));

        //cout << "pos: " << pos << "\tISE: " << ISE <<endl;

  			if (pos != previousDominant + 1)
  			{
  				if(ISE < menorError)
  				{
  					menorError = ISE;
  					possitionBestDominant = pos;
  				}
  			}

        // Set the ISE of the first element as the first minor.
  			else
  			{
  				menorError = ISE;
  				possitionBestDominant = pos;
  			}

  			pos++; 

  			// In the case of the last point, pos is set to 0
  			if (pos == numberPoints)
  				pos = 0;

  		}

      //cout << endl << "Menor ISE: " << menorError << " (" << possitionBestDominant << ")";
      //cout << endl;

  		// Set the new dominant
  		dominantPointsChoosen[i] = possitionBestDominant;
  	}

    // Set the dominant point 0 with the same value as the new last dominant point
		dominantPointsChoosen[0] = dominantPointsChoosen[numberPointsForChoose - 1];
		possitionPoints[0] = possitionPoints[numberPointsForChoose - 1];

    //***********************************************

  	//Set the position of the dominant points choosen
  	setDominantPointsPosition(dominantPointsChoosen);

  	//Obtaining polygonal approximattion
  	calculatePolygonalApproximation();

    //Set the number of points of the polygonal approximation
    setNumberPointsPolygonalApproximation(getPolygonalApproximation().getNumberPointsDigitalCurve());
}

void GreedyMethod::chooseNumberPointsPolygonalApproximation(const vector <int> & dominantPoints, vector <int> & dominantPointsChoosen, vector <int> & possitionPoints)
{
    int numberDominantPoints = dominantPoints.size();

    int numberPointsForChoose = getNumberPointsPolygonalApproximation();

    if(numberPointsForChoose > numberDominantPoints)
       numberPointsForChoose = numberDominantPoints;

    // Calculamos el valor del salto para escoger los x puntos dominantes indicados 
    int skipValue = numberDominantPoints / (numberPointsForChoose - 1);

    // Guardamos los puntos escogidos
    for(int i = 0; i < numberPointsForChoose - 1; i++)
    {
      dominantPointsChoosen.push_back(dominantPoints[skipValue * i]);
      possitionPoints.push_back(skipValue * i);
    }

    dominantPointsChoosen.push_back(dominantPoints[numberDominantPoints - 1]);
    possitionPoints.push_back(numberDominantPoints - 1);
}


