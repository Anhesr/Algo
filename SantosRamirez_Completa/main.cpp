#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "backtracking.hpp"
#include "lasVegas.hpp"
#include "ajusteBacktraking.hpp"


int main(int argc, char const *argv[])
{
	int op;
	int n;
	vector <int> x;

	do{
	cout<< "¿Qué operación desea realizar?"<<endl;
	cout<< "	1. Backtracking para N reinas"<<endl;
	cout<< "	2. LasVegas para N reinas"<<endl;
	cout<< "	3. Ajustar curva N reinas Backtracking"<<endl;
	cout<< "	4. Salir"<<endl;
	cin>>op;
	system("clear");

	switch(op){
		case 1:{

			vector <vector <int> > mat;
			cout<< "¿Qué numero de reninas quiere colocar?"<<endl;
			cin>>n;
			reinas(n,mat);
			for (int i = 0; i < mat.size(); ++i)
			{
				cout<<i+1<<" : (";
				for (int j = 1; j < mat[i].size(); ++j)
				{
					cout<<mat[i][j];
				}
				cout<<")"<<endl;
			}
		}break;
		case 2:{
			bool exito=false;
			cout<< "¿Qué numero de reninas quiere colocar?"<<endl;
			cin>>n;
			do{
				lasVegas(n,x,exito);
			}while(exito==false);
		}break;
		case 3:{
			ajusteTiempos();
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