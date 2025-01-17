#include "algorithm.hpp"
#include "suppressioncollinearpointsmethod.hpp"
#include "dynamicprogrammingmethod.hpp"
#include <iostream>


using namespace std;

int main(int argc, char *argv[])
{
   //It creates a pointer to algorithm class to use overload in execution
   Algorithm *a;

   char fileNameDC[100], fileNamePA[100];
   int n;
   cout << "Digital curve to obtain polygonal approximation: ";
   cin >> fileNameDC;
   cout << "Number of points to obtain polygonal approximation: ";
   cin >> n;

   //Creates a new class for method and the pointer points to the new class
   a = new DynamicProgrammingMethod(fileNameDC,n);

   //Execute the method
   a->apply();

   cout << "Number of points of the polygonal approxmation: " << a->getNumberPointsPolygonalApproximation() << endl;
   cout << "The value of ISE is " << a->getISE() << endl;

   DigitalCurve aP = a->getPolygonalApproximation();

   cout << "Name of file to save the polygonal approximation: ";
   cin >> fileNamePA;
   
   aP.saveDigitalCurve(fileNamePA);
   return 0;
}
