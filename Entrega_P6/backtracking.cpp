#include "ochoReinas.hpp"


void n_reinas_Backtracking(int n, vector< vector<int> > & queens_position)
{
	if (n <= 0) return;
	
	int k;
	std::vector<int> x(n + 1);

	x[1] = 0;
	k = 1;

	while(k > 0)
	{
		x[k] = x[k] + 1;

		while(( x[k] <= n ) and (lugar(k, x) == false))
		{
			x[k] = x[k] + 1;
		}

		if (x[k] <= n)
		{
			if ( k == n )
			{
				queens_position.push_back(x);
			}

			else
			{
				k = k + 1;
				x[k] = 0;
			}
		}

		else
			k = k - 1;		
	}
}