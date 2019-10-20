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

int main()
{
	int op,op2,c;
	vector<punto> p;
	do{
	cout<< "¿Qué operación desea realizar?"<<endl;
	cout<< "	1. Cálculo de los caminos posibles para llegar a una casilla de la fila 8 desdecualquier casilla de la fila 1"<<endl;
	cout<< "	2. Cálculo de los caminos posibles para llegar a la fila 8 desde la casilla inicial (1,2)"<<endl;
	cout<< "	3. Cálculo de los caminos posibles para llegar a la fila 8 desde la casilla inicial (1,7)"<<endl;
	cout<< "	4. Salir"<<endl;
	cin>>op;
	system("clear");

	switch(op){
		case 1:{
			matp.clear();
			cout<< "Introduzca la casilla de destino de la fila 8"<<endl;
			cin>>c;
			system("clear");
			cout<<"Se han encontrado "<<encontrarCaminos(8, c, p)<<" caminos para la casilla de destino 8,"<<c<<endl;

			cout<<"¿Quiere ver todos los caminos en un tablero?"<<endl;
			cout<<"		1.Sí"<<endl;
			cout<<"		2.No"<<endl;
			cin>>op2;
			system("clear");
			switch(op2){
				case 1:{
				mostrarCaminos();
				}
				case 2:{}
			}

		}break;
		case 2:{
			matp.clear();
			cout<<"Se han encontrado "<<encontrarCaminosPrimero(1, 2, p)<<" caminos para la casilla de origen 1,2"<<endl;

			cout<<"¿Quiere ver todos los caminos en un tablero?"<<endl;
			cout<<"		1.Sí"<<endl;
			cout<<"		2.No"<<endl;
			cin>>op2;
			system("clear");
			switch(op2){
				case 1:{
				mostrarCaminos();
				}
				case 2:{}
			}

		}break;
		case 3:{
			matp.clear();
			cout<<"Se han encontrado "<<encontrarCaminosPrimero(1, 7, p)<<" caminos para la casilla de origen 1,7"<<endl;

			cout<<"¿Quiere ver todos los caminos en un tablero?"<<endl;
			cout<<"		1.Sí"<<endl;
			cout<<"		2.No"<<endl;
			cin>>op2;
			system("clear");
			switch(op2){
				case 1:{
				mostrarCaminos();
				}
				case 2:{}
			}

		}break;
		case 4:{
			cout<<"Saliendo."<<endl;
		}break;
		default:{
			cout<<"Opción no valida"<<endl;
		}break;
	}
	}while(op != 4);
}


int encontrarCaminos(int f, int c, vector <punto> p){
	punto auxp;
	auxp.x=f;
	auxp.y=c;
	p.push_back(auxp);

	if( f <=0 || f > 8 ){
		return 0;
	}

	if( c <=0 || c > 8 ){
		return 0;
	}

	if ( f == 1 ){
		imprime(p);
		p.clear();
		return 1;
	}

	return (encontrarCaminos(f-1,c+2,p)+encontrarCaminos(f-2,c+1,p)
		+encontrarCaminos(f-1,c-2,p)+encontrarCaminos(f-2,c-1,p));
}

int encontrarCaminosPrimero(int f, int c, vector <punto> p){
	punto auxp;
	auxp.x=f;
	auxp.y=c;
	p.push_back(auxp);

	if( f <=0 || f > 8 ){
		return 0;
	}

	if( c <=0 || c > 8 ){
		return 0;
	}

	if ( f == 8 ){
		imprime(p);
		p.clear();
		return 1;
	}

	return (encontrarCaminosPrimero(f+1,c-2,p)+encontrarCaminosPrimero(f+2,c-1,p)
		+encontrarCaminosPrimero(f+1,c+2,p)+encontrarCaminosPrimero(f+2,c+1,p));
}

void imprime(vector <punto> p){

	matp.push_back(p);

	for (int i = 0; i <(int) p.size(); ++i)
	{
		cout<<"("<<p[i].x<<","<<p[i].y<<")"<<"-->";
		if(i== (int) p.size()-1){
			cout<<"("<<p[i].x<<","<<p[i].y<<")"<<endl;
		}
	}
}

void mostrarCaminos(){

	for (int i = 0; i < matp.size(); ++i)
	{
		vector <vector <int> > maux(8,vector <int> (8));

		for (int j = 0; j < matp[i].size(); ++j)
		{
			maux[matp[i][j].x-1][matp[i][j].y-1] = 1;

		}

		cout<<"Camino "<<i+1<<" :"<<endl;
		imprimeTablero(maux);
		maux.clear();
	}
}

void imprimeTablero(vector <vector <int> > m){

	cout<<"_ _ _ _ _ _ _ _ _"<<endl;

	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if(m[i][j] == 1){
				cout<<"|x";
			}
			else{
				cout<<"|_";
			}
			if(j == 7){
				cout<<"|"<<endl;
			}
		}
	}
}
