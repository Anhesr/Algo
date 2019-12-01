
#include <vector>    // necesario para el contenedor vector
#include "algorithm.hpp"
#include "suppressioncollinearpointsmethod.hpp"
#include "digitalcurve.hpp"
//#include "heapvectorMasood.hpp"
//#include "nodoMasood.hpp"



using namespace std;

/* Functions for Collinear suppression method */

//Constructor.

CollinearSuppressionMethod::CollinearSuppressionMethod(char *fileName)
{
  //A digital curve is created to load the digital curve in file
	DigitalCurve dc(fileName);
  
  //Digital curve as saved as original curve
  setOriginalCurve(dc);
}

//Destructor
CollinearSuppressionMethod::~CollinearSuppressionMethod()
{
}

void CollinearSuppressionMethod::apply()
{

}

