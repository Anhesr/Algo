#include "ochoReinas.hpp"

void n_reinas_LasVegas(int n, vector <int> & X, bool & success)
{
	int count;
	int columna;
	vector <int> ok(n + 1);

	// Fill x vector with zeros
	for(int i = 1; i <= n; i++)
		X[i] = 0;

	// Put the k-esime queen in X vector
	for(int k = 1; k <= n; k++)
	{
		count = 0;

		for(int j = 1; j <= n; j++)
		{
			X[k] = j;

			if(lugar(k, X))
			{
				count = count + 1;
				ok[count] = j;
			}

		}
		
		if (count == 0)
		{
			success = false;
			return;
		}

		X[k] = ok[(rand()%count) + 1];
	}

	if(count == 0)
		success = false;
	else
		success = true;
}

void algoritmoLasVegas(int n)
{
	vector<int> X(n + 1);
	int count = 0;
	bool success = false;

	while(!success)
	{
		 n_reinas_LasVegas(n, X, success);

		 count++;
	}

	cout << "> Solution found: ";

	for(int i = 1; i < X.size(); i++)
	{
		cout << "(" << i << ", " << X[i] << ") ";
	}

	cout << endl << endl << "Number of attemps: " << count << endl;
}