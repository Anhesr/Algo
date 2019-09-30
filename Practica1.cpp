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
#include <cmath>

using namespace std; 

void rellenarVector(vector<int> &v);
int divide(vector<int> &v, int start, int end);
void estaOrdenado(const vector <int> &v);
void quicksort(vector<int> &v,int start, int end ,double &temp);
double calculaMedia(const vector <double> v);
void ajusteNlogN(const vector <double> &n, const vector <double> &tiemposReales, double &a0, double &a1);
double calcularSumatorio(vector <double> v1, vector <double> v2, int exp1 , int exp2);
void calcularTiemposEstimadosNlogN(const vector <double> &n, const vector <double> &tiemposReales, const double &a0, const double &a1, vector<double> &tiemposEstimados);

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
  vector <double> mu;
  vector <double> tiemposReales;
  double a0;
  double a1;


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

	mu.push_back(i);
	tiemposReales.push_back(med);

 	i= i + inc;

 	estaOrdenado(v);

  }



   ajusteNlogN(mu,tiemposReales,a0,a1);


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

	vector <double> z;
	vector <double> tiemposEstimados;

	for(int i=0;i< (int) n.size();i++){
		z.push_back(n[i] * log(n[i]));
	}

	a1=  (((int)n.size()*calcularSumatorio(z,tiemposReales,1,1)) - (calcularSumatorio(z,tiemposReales,1,0) * calcularSumatorio(z,tiemposReales,0,1) ))
		/ ( ((int)n.size()*calcularSumatorio(z,tiemposReales,2,0)) -  pow( calcularSumatorio(z,tiemposReales,1,0) , 2) ) ;

	a0= calculaMedia(tiemposReales) - (a1 * calculaMedia(z));
	
	calcularTiemposEstimadosNlogN(n,tiemposReales,a0,a1,tiemposEstimados);


	ofstream fs("Datos.txt");

	for(int i=0;i< (int) n.size();i++){

	fs << n[i] << " " << tiemposReales[i] << " " << tiemposEstimados[i] <<endl;

	}

	fs.close();

}

double calcularSumatorio(vector <double> v1, vector <double> v2, int exp1 , int exp2){

	double sum=0;

	for(int i=0; i < (int) v1.size() ; i++){
		sum= sum +( pow(v1[i], exp1 ) * pow(v2[i], exp2 ) );
	}

	return sum ;

}

void calcularTiemposEstimadosNlogN(const vector <double> &n, const vector <double> &tiemposReales, 
	const double &a0, const double &a1, vector<double> &tiemposEstimados){

		for(int i=0; i < (int) n.size() ; i++){
			tiemposEstimados.push_back( a0 + (a1 * (n[i] * log(n[i]) ) ));
		}

}