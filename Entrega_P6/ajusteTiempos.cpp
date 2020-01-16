#include "ochoReinas.hpp"

double sumatorio(const vector <double> &a, const int exp1, const vector <double> &b, const int exp2)
{
	double suma = 0.00;

	int size = a.size();

	for (int i = 0; i < size; i++)
	{
		suma += pow(a[i], exp1) * pow(b[i], exp2);
	}

	return suma;
}


void ajusteFactorial(const vector <double> &n, const vector <double> &tiemposReales, double &a0, double &a1)
{
	vector <vector <double> > A; // Matriz
	vector <vector <double> > B; // Term. Independientes
	vector <vector <double> > X; // Valores de a
	vector <double> z;

	A = vector <vector <double> > (2, vector <double>(2));
	B = vector <vector <double> > (2, vector <double>(1));
	X = vector <vector <double> > (2, vector <double>(1));

	// Fill in the vector z with the factorial values from 1 to n
	z.resize((int)n.size());

	// Set the first value
	z[0] = n[0];

	for(int i = 1; i < n.size(); i++)
	{
		z[i] = z[i - 1] * n[i];
	}

	// Fill in the A and B vectors
	for(int i = 0; i < 2; i++)
	{
		B[i][0] = sumatorio(z, i, tiemposReales, 1);

		for(int j = 0; j < 2; j++)
		{
			A[i][j] = sumatorio(z, i+j, z, 0);
		}
	}

	resolverSistemaEcuaciones(A, B, 2, X);

	a0 = X[0][0];
	a1 = X[1][0];

	//cout << endl << "a0: " << a0 << ", a1: " << a1 << endl;
}

void calcularTiemposEstimadosFactorial(const vector<double> &n, const vector<double> &tiemposReales, const double &a0, const double &a1, vector<double> &tiemposEstimados)
{
    tiemposEstimados.resize(n.size());
   	vector <double> fact;

   	// Fill in the vector fact with the factorial values from 1 to n
	fact.resize((int)n.size());

	// Calculate the factorial values
	fact[0] = n[0];

	for(int i = 1; i < n.size(); i++)
	{
		fact[i] = fact[i - 1] * n[i];
	}

	// Calculate the estimated times
    for(int i = 0; i < (int) n.size(); i++)
    {
        tiemposEstimados[i] = a0 + (a1 * fact[i]);
    }
}

void guardarTiempos(const vector<double> &n, const vector<double> &tiemposReales, const vector<double> &tiemposEstimados)
{
	ofstream fs("Datos.txt");

	for(int i = 0; i < (int) n.size(); i++)
    {
        fs << n[i] << "\t" << tiemposReales[i] << "\t" << tiemposEstimados[i] << endl;
    }

    fs.close();
}


void ajustarTiemposBacktracking()
{
	int n_value;
	vector < vector<int> > queens_position;
	vector < double > n;
	vector < double > tiemposReales;
	vector < double > tiemposEstimados;
	double a0, a1;
	Clock time;

	cout << "Introduce n value: ";
	cin >> n_value;


	// Fill in the real time vector
	for (int i = 1; i <= n_value; i++)
	{
		system("clear");
		cout << "----------< Opc. 3. Ajuste de Tiempos>----------" << endl << endl;
		
		cout << "Calculating times for the problem with " << i << " queens" << endl;
		queens_position.clear();

		// Start clock
		time.start();

		n_reinas_Backtracking(i, queens_position);

		// Stop clock
		time.stop();

		// Set the queens number and the real time
		n.push_back(i);
		tiemposReales.push_back(time.elapsed());

	}

	ajusteFactorial(n, tiemposReales, a0, a1);

	calcularTiemposEstimadosFactorial(n, tiemposReales, a0, a1, tiemposEstimados);

	guardarTiempos(n, tiemposReales, tiemposEstimados);

	cout << endl << "Execution finished. Times save in Datos.txt file." << endl;
}