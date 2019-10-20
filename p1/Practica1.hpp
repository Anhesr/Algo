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
#include "sistemaEcuaciones.cpp"
#include <cmath>

using namespace std;

void ajusteQuicksort();
void rellenarVector(vector<int> &v);
int divide(vector<int> &v, int start, int end);
void estaOrdenado(const vector <int> &v);
void quicksort(vector<int> &v,int start, int end ,double &temp);
double calculaMedia(const vector <double> v);
void ajusteNlogN(const vector <double> &n, const vector <double> &tiemposReales, double &a0, double &a1);
double calcularSumatorio(vector <double> v1, vector <double> v2, int exp1 , int exp2);
void calcularTiemposEstimadosNlogN(const vector <double> &n, const vector <double> &tiemposReales, const double &a0, const double &a1, vector<double> &tiemposEstimados);
double calcularCoeficienteDeterminacion(const vector <double> &tiemposReales,const vector <double> &tiemposEstimados);
double calcularVarianza(const vector <double> v);
double calcularTiempoEstimadoNlogN(const double &n, const double &a0, const double &a1);
void rellenarMatriz(vector <vector <double> > &v );
void multiplicacion();
void productoMatrices(vector <vector <double> > v1 , vector <vector <double> > v2);
void ajustePolinomico(const vector <double> &n, const vector <double> &tiemposReales, vector <double> &a);
void calcularTiemposEstimadosPolinomico(const vector <double> &n, const vector <double> &tiemposReales, const vector <double> &a, vector <double> &tiemposEstimados);
double calcularTiempoEstimadoPolinomico(const double &n, const vector <double> &a);