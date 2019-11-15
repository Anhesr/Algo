#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void quitarCeros(string &s);

class entero
{
private:
public:
	string _n;
	entero & operator+( entero b);
	entero & operator*( entero const &b);
	entero & operator=( entero const &b);
	entero & operator*( int const &n);
};

void divideCadena(string cad,string &tr1,string &tr2);
void insertarCerosDelante(int n,string & cad);
void insertarCerosDetras(int n,string & cad);
void sumarNveces(entero &a,int n);
ostream& operator << (ostream &o,const entero &n);
istream& operator >> (istream &i, entero &n);
entero calcularFactorial(entero n);

