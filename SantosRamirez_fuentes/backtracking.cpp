#include "backtracking.hpp"

using namespace std;

bool lugar(int k ,vector <int> x){
	for (int i = 1; i < k; ++i)
	{
		if(x[i] == x[k] || ( abs(x[i]-x[k]) == abs(i-k)  ) ){
			return false;
		}
	}
	return true;
}

void reinas(int n,vector < vector <int> > &Mat){
	vector <int>x(n+1);
	x[1]=0;
	int k =1;
	while(k > 0){
		x[k]=x[k]+1;
		while(x[k]<=n && !lugar(k,x)){
			x[k]=x[k]+1;
		}
		if(x[k] <= n){
			if(k==n){
				Mat.push_back(x);
			}
			else{
				k=k+1;
				x[k]=0;
			}
		}
		else{
			k=k-1;
		}

	}
}

