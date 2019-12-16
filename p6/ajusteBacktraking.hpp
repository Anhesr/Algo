#ifndef AJUSTEBACKTRACKING_HPP
#define AJUSTEBACKTRACKING_HPP

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
#include <cmath>
#include "ClaseTiempo.cpp"
#include "backtracking.hpp"

double calcularSumatorio(vector <double> v1, vector <double> v2, int exp1 , int exp2);

void ajusteTiempos();

double calcularFactorial(double n);

double calculaMedia(const vector <double> v);

void calcularTiemposEstimadosFactorial(vector <double> n, const vector <double> &tiemposReales, 
	const double &a0, const double &a1, vector<double> &tiemposEstimados);

void escribirFichero(const vector <double> &n, const vector <double> &tiemposReales,const vector <double> &tiemposEstimados);

void ajusteFactorial(const vector <double> &n, const vector <double> &tiemposReales, double &a0, double &a1);


#endif