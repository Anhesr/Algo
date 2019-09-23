#include <iostream> 
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdint.h>
#include <cassert>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <fstream>
#include "ClaseTiempo.cpp"

using namespace std; 

void rellenarVector(vector<int> &v);
int divide(vector<int> &v, int start, int end);
void estaOrdenado(const vector <int> &v);
void quicksort(vector<int> &v,int start, int end ,double &temp);
double calculaMedia(const vector <double> v);
void ajusteNlogN(const vector <double> &n, const vector <double> &tiemposReales, double &a0, double &a1);

int main()
{
	vector<int> v;
	std::vector<double> vaux;
  int n;

  int min;
  int max;
  int inc;
  int rep;
  double med;
  double temp;
  Clock time;
  char cadena[128];

  ofstream fs("Datos.txt"); 

  cout<<"Introduzca el minimo de elementos : "<<endl;

  cin >> min ;

  cout<<"Introduzca el maximo de elementos : "<<endl;

  cin >> max ;

  cout<<"Introduzca el incremento : "<<endl;

  cin >> inc ;

  cout<<"Introduzca el numero de repeticiones : "<<endl;

  cin >> rep ;


  for(int i=min ; i < max ;){

 	
 	v.resize(i);

 	for(int j=0 ; j < rep ;j++ ){
  		rellenarVector(v);

  		time.start();

  		quicksort(v,0, (int) v.size()-1,temp);

  		if (time.isStarted())
		{
			time.stop();
			vaux.push_back(time.elapsed());
		}
	}

	med = calculaMedia(vaux);

	fs << i << "  " << med << endl;

 	i= i + inc;

 	estaOrdenado(v);

  }

   fs.close();




}

void rellenarVector(vector<int> &v){
  srand(time(NULL));

  for(int i=0;i< v.size();i++){

    v[i] = rand() % 10000;
  }
}

void quicksort(vector<int> &v,int start, int end , double &temp){

    int pivot;
    Clock time;

    time.start();

    if (start < end) {
        pivot = divide(v, start, end);
        quicksort(v, start, pivot - 1,temp);
        quicksort(v, pivot + 1, end,temp);
    }

}

int divide(vector<int> &v, int start, int end){
    int left;
    int right;
    int pivot;
    int temp;
 
    pivot = v[start];
    left = start;
    right = end;

    while (left < right) {
        while (v[right] > pivot) {
            right--;
        }
 
        while ((left < right) && (v[left] <= pivot)) {
            left++;
        }
 
        if (left < right) {
            temp = v[left];
            v[left] = v[right];
            v[right] = temp;
        }
    }
 
    temp = v[right];
    v[right] = v[start];
    v[start] = temp;
 
    return right;
}

void estaOrdenado(const vector <int> &v){
  for(int i=0;i< (int) v.size()-1; i++){
      assert( v[i] <= v[i+1] );
  }

  /*cout<<"-----------------------------"<<endl;
  for(int i=0;i< (int) v.size(); i++){
    cout<<" "<< v[i] << " " << endl;
  }
  cout<<"-----------------------------"<<endl;*/
}

double calculaMedia(const vector <double> v){

	double sum = 0;

	for(int i = 0 ; i< v.size(); i++){
		sum=sum+v[i];
	}

	sum= sum/(int)v.size();

	return sum;
}

void ajusteNlogN(const vector <double> &n, const vector <double> &tiemposReales, double &a0, double &a1){

	
}