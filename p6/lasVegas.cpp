#include "lasVegas.hpp"

using namespace std;

bool lugarVegas(int k ,vector <int> x){
	for (int i = 1; i < k; ++i)
	{
		if(x[i] == x[k] || ( abs(x[i]-x[k]) == abs(i-k)  ) ){
			return false;
		}
	}
	return true;
}

void lasVegas(int n , vector <int> x,bool &exito){

	srand(time(NULL));
	x.push_back(0);
	vector <int> ok(n+1);
	int cont;

	for (int i = 1; i <= n; ++i)
	{
		x.push_back(0);
	}

	for (int i = 1; i <= n; ++i)
	{
		cont= 0;
		for (int k = 1; k <= n; ++k)
		{
			x[i]=k;
			if(lugarVegas(i,x)){
				cont=cont+1;
				ok[cont]=k;
			}
		}
		if(cont == 0) {
			exito=false;
			return;	
		} 
		int columna = ok[(rand()%cont)+1];
		x[i]=columna;
	}
	if(cont == 0){
		exito=false;
	}
	else{
		imprimeResultado(x);
		exito=true;
	}

}

void imprimeResultado(vector <int> x){
	cout<<"La solución encontrada es : ";
	cout<<"(";
	for (int i = 1; i < x.size(); ++i)
		{
			cout<<x[i];
		}	
	cout<<")"<<endl;
}
