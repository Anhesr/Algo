#include "Prac3.hpp"

using namespace std;

void divideCadena(string cad,string &tr1,string &tr2);

entero operator+(entero &a, entero &b);
entero operator*(entero &a, entero &b);

int main(int argc, char const *argv[])
{


	return 0;
}

entero operator+(entero &a, entero &b){

		vector <int> x, y;
		int aux=0;
		string suma="";
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
						suma.insert(suma.begin(),aux+'0');
						acc=0;
					}
					else
					{
						suma.insert(suma.begin(),(aux%10)+ '0');
						acc=1;
					}
				}
				else{
					aux = x[i] + y[i] + 1;
					if (aux < 10)
					{
						suma.insert(suma.begin(),aux+ '0');
						acc=0;
					}
					else
					{
						suma.insert(suma.begin(),(aux%10) + '0');
						acc=1;
					}
				}
			}

			for (int i = b._n.length() ; i < a._n.length(); ++i)
			{
				if(acc == 1){
					aux=x[i]+1;

					if (aux < 10)
					{
						suma.insert(suma.begin(),aux+ '0');
						acc=0;
					}
					else
					{
						suma.insert(suma.begin(),(aux%10) + '0');
						acc=1;
					}
				}
				else{
					aux=x[i];
					suma.insert(suma.begin(),aux+ '0');
					acc=0;
				}
			}
		}
//-------------------------------------------

		if(a._n.length() < b._n.length()){


			for (int i = 0; i < a._n.length(); ++i)
			{
				
				if(acc== 0){
					aux = x[i] + y[i];
					if (aux < 10)
					{
						suma.insert(suma.begin(),aux+'0');
						acc=0;
					}
					else
					{
						suma.insert(suma.begin(),(aux%10)+ '0');
						acc=1;
					}
				}
				else{
					aux = x[i] + y[i] + 1;
					if (aux < 10)
					{
						suma.insert(suma.begin(),aux+ '0');
						acc=0;
					}
					else
					{
						suma.insert(suma.begin(),(aux%10) + '0');
						acc=1;
					}
				}
			}

			for (int i = a._n.length() ; i < b._n.length(); ++i)
			{
				if(acc == 1){
					aux=y[i]+1;

					if (aux < 10)
					{
						suma.insert(suma.begin(),aux+ '0');
						acc=0;
					}
					else
					{
						suma.insert(suma.begin(),(aux%10) + '0');
						acc=1;
					}
				}
				else{
					aux=y[i];
					suma.insert(suma.begin(),aux+ '0');
					acc=0;
				}
			}
		}
		return suma;
}


entero operator*(entero &a, entero &b){
	entero w,x,y,z,r,p,q;
	int n= max(a._n.size(),b._n.size());

	if(a._n.size() == 4 && b._n.size() == 4 ){
		int aux1= atoi(a._n.c_str());
		int aux2= atoi(b._n.c_str());
		int mul= aux1*aux2;
	}
	else{
		divideCadena(a._n,w._n,x._n);
		divideCadena(b._n,y._n,z._n);
		r=((w+x)*(y+z));

	}
	return a;
}

void divideCadena(string cad,string &tr1,string &tr2){
	if(cad.size() %2==0){
		tr1=cad.substr(0,cad.size()/2 );
		tr2=cad.substr(cad.size()/2,cad.size());
	}
	else{
		tr1=cad.substr(0,(int) cad.size()/2 + 1 );
		tr2=cad.substr((int)cad.size()/2 + 1 ,cad.size());
	}
}