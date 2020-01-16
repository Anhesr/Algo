#include "ochoReinas.hpp"

using namespace std;

int main()
{
	int opcion = -1;
	int n;
	vector< vector<int> > queens_position;
	
	srand(time(NULL));

	while (opcion != 0)
	{
		system("clear");
		cout << "--------------------< Menú >--------------------" << endl << endl;
	
		cout << "1. Basic Option.\t Backtracking." << endl;
		cout << "2. Basic Option.\t Algoritmo de las Vegas." << endl;
		cout << "3. Basic Option.\t Ajuste de tiempos (Backtracking)" << endl << endl;

		cout << "0. Salir." << endl << endl;

		cout << "------------------------------------------------" << endl << endl;

		cout << "Opción: ";
		cin >> opcion;

		switch(opcion)
		{
			case 0:
				system("clear");

				cout << endl << "Saliendo..." << endl << endl;
			break;

			case 1:

				system("clear");

				cout << "------------< Opc. 1. Backtracking>-------------" << endl << endl;

				cout << "Introduce n value: ";
				cin >> n;
				cout << endl << "------------------> SOLUCIÓN <------------------" << endl << endl;

				queens_position.clear();
				n_reinas_Backtracking(n, queens_position);
				show_positions(queens_position);

				cout << endl << "----------> PRESS ENTER TO CONTINUE <-----------" << endl;
				cin.get();
				cin.ignore();

			break;

			case 2:
				system("clear");

				cout << "--------------< Opc. 2. Las Vegas>--------------" << endl << endl;

				cout << "Introduce n value: ";
				cin >> n;
				cout << endl << "------------------> SOLUCIÓN <------------------" << endl << endl;

				queens_position.clear();
				algoritmoLasVegas(n);
				//show_positions(queens_position);

				cout << endl << "----------> PRESS ENTER TO CONTINUE <-----------" << endl;
				cin.get();
				cin.ignore();
			break;

			case 3:
				system("clear");
				cout << "----------< Opc. 3. Ajuste de Tiempos>----------" << endl << endl;

				ajustarTiemposBacktracking();

				cout << endl << "----------> PRESS ENTER TO CONTINUE <-----------" << endl;
				cin.get();
				cin.ignore();
			break;

			default:

				system("clear");
			
				cout << "--------------< Opción Invalida >---------------" << endl << endl;

				cout << "> Option (" << opcion << ") is not a valid option." << endl;

				cout << endl << "----------> PRESS ENTER TO CONTINUE <-----------" << endl;
				cin.get();
				cin.ignore();
			break;
		}

	}
}