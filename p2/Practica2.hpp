#include <iostream>
#include <cstdlib>
#include <vector>


using namespace std;


struct punto
{
	int x;
	int y;
};

vector <vector<punto> > matp;

int encontrarCaminos(int f, int c,vector<punto> p);

int encontrarCaminosPrimero(int f, int c, vector <punto> p);

void imprime(vector <punto> p);

void mostrarCaminos();

void imprimeTablero(vector <vector <int> > m);