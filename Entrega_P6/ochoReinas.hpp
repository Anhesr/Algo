#ifndef OCHO_REINAS
#define OCHO_REINAS

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <ctime>
#include <cmath>
#include <fstream>
#include "ClaseTiempo.cpp"
#include "sistemaEcuaciones.hpp"


using namespace std;

bool lugar(int k, std::vector<int> queens);

void show_positions(vector< vector<int> > v);

void n_reinas_Backtracking(int n, vector< vector<int> > & queens_position);

void n_reinas_LasVegas(int n, vector <int> & X, bool & success);

void algoritmoLasVegas(int n);

void ajustarTiemposBacktracking();

#endif