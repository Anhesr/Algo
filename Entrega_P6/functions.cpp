#include "ochoReinas.hpp"

using namespace std;

bool lugar(int k, std::vector<int> queens)
{
	for(int i = 1; i < k; i++)
	{
		if((queens[i] == queens[k]) or (abs(queens[i] - queens[k])) == abs(i - k))
			return false;
	}

	return true;
}

void show_positions(vector< vector<int> > v)
{
	for (int i = 0; i < v.size(); i++)
	{
		cout << i+1 << ": ";

		for (int j = 1; j < v[i].size(); j++)
		{
			cout << "(" << j << ", " << v[i][j] << ") ";
		}

		cout << endl;
	}
}

// --------------------------------------------------------------- 