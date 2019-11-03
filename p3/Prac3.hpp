#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


class entero
{
private:
public:
	string _n;
};


/*entero operator*( entero a, entero b)
	{
		cout<<"1"<<endl;
		vector <int> x, y;
		int aux;
		string suma;
		int acc=0;
		
		for (int i = 0; i < a._n.length(); ++i)
		{
			x.insert(x.begin() , a._n[i] - '0');
		}

		for (int i = 0; i < b._n.length(); ++i)
		{
			y.insert(y.begin() , b._n[i] - '0');
		}

		if(a._n.length() >= b._n.length()){

			for (int i = 0; i < b._n.length(); ++i)
			{
				if(acc== 0){
					aux = x[i] + y[i];
					if (aux < 10)
					{
						suma.push_back(aux);
						acc=0;
					}
					else
					{
						suma.push_back(aux%10);
						acc=1;
					}
				}
				if(acc== 1){
					aux = x[i] + y[i] + 1;
					if (aux < 10)
					{
						suma.push_back(aux);
						acc=0;
					}
					else
					{
						suma.push_back(aux%10);
						acc=1;
					}
				}
			}

			for (int i = 0; i < a._n.length() - b._n.length(); ++i)
			{
				if(acc == 1){
					aux=x[i]+1;

					if (aux < 10)
					{
						suma.push_back(aux);
						acc=0;
					}
					else
					{
						suma.push_back(aux%10);
						acc=1;
					}
				}
				else{
					suma.push_back(aux);
					acc=0;
				}
			}
		}
//---------------------------------------------------------
		if(a._n.length() < b._n.length()){

			for (int i = 0; i < a._n.length(); ++i)
			{
				if(acc== 0){
					aux = x[i] + y[i];
					if (aux < 10)
					{
						suma.push_back(aux);
						acc=0;
					}
					else
					{
						suma.push_back(aux%10);
						acc=1;
					}
				}
				if(acc== 1){
					aux = x[i] + y[i] + 1;
					if (aux < 10)
					{
						suma.push_back(aux);
						acc=0;
					}
					else
					{
						suma.push_back(aux%10);
						acc=1;
					}
				}
			}

			for (int i = 0; i < b._n.length() - a._n.length(); ++i)
			{
				if(acc == 1){
					aux=y[i]+1;

					if (aux < 10)
					{
						suma.push_back(aux);
						acc=0;
					}
					else
					{
						suma.push_back(aux%10);
						acc=1;
					}
				}
				else{
					suma.push_back(aux);
					acc=0;
				}
			}
		}

		a._n= suma;

}
*/



