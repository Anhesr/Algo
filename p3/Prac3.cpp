#include "Prac3.hpp"

using namespace std;

void divideCadena(string cad,string &tr1,string &tr2);
void insertarCerosDelante(int n,string & cad);
void insertarCerosDetras(int n,string & cad);
void sumarNveces(entero &a,int n);

int main(int argc, char const *argv[])
{
	entero a,b;
	string n1,n2;
	cout<<"Introduzca el valor del primer entero"<<endl;
	cin>>n1;
	a._n=n1;
	cout<<"Introduzca el valor del primer entero"<<endl;
	cin>>n2;
	b._n=n2;
	entero aux=a*b;
	cout<<aux._n<<endl;

}


entero & entero::operator+(entero b){
		vector <int> x, y;
		int aux=0;
		entero suma;
		suma._n="";
		int acc=0;
		
		for (int i = 0; i < this->_n.length(); ++i)
		{
			x.insert(x.begin() , this->_n[i] - '0');
		}

		for (int i = 0; i < b._n.length(); ++i)
		{
			y.insert(y.begin() , b._n[i] - '0');
		}

		if(this->_n.length() > b._n.length()){
			insertarCerosDelante(this->_n.length() - b._n.length() ,b._n);
		}
		if(this->_n.length() < b._n.length()){
			insertarCerosDelante(b._n.length()-this->_n.length(),this->_n);
		}


		for (int i = 0; i < b._n.length(); ++i)
		{
			
			if(acc== 0){
				aux = x[i] + y[i];
				if (aux < 10)
				{
					suma._n.insert(suma._n.begin(),aux+'0');
					acc=0;
				}
				else
				{
					suma._n.insert(suma._n.begin(),(aux%10)+ '0');
					acc=1;
				}
			}
			else{
				aux = x[i] + y[i] + 1;
				if (aux < 10)
				{
					suma._n.insert(suma._n.begin(),aux+ '0');
					acc=0;
				}
				else
				{
					suma._n.insert(suma._n.begin(),(aux%10) + '0');
					acc=1;
				}
			}
		}

		if (acc==1){
			suma._n.insert(suma._n.begin(),'1');
		}
		this->_n=suma._n;
		return *this;
}


entero & entero::operator*( entero const &b){
	entero w,x,y,z;
	int n= max(this->_n.size(),b._n.size());
	int s=n/2;
	entero aux1,aux2,aux3,aux4;

	if(this->_n.size()<=4 || b._n.size()<=4 ){
		cout<<this->_n<<" "<<b._n<<endl;
		if(atoi(this->_n.c_str()) <= atoi(b._n.c_str())){
			entero aux=b;
			sumarNveces(aux,atoi(this->_n.c_str()));
			*this=aux;
		}
		else{
			sumarNveces(*this,atoi(b._n.c_str()));
		}
		return *this;
	}
	else{
		divideCadena(this->_n,w._n,x._n);
		divideCadena(b._n,y._n,z._n);
	
		aux1=w*y;
		cout<<aux1._n<<endl;
		/*aux2=w*z;
		aux3=x*y;
		aux4=x*z;

		insertarCerosDetras(s*2,aux1._n);
		return(aux1+(aux2+aux3+aux4));*/
		return *this;
		
	}

}

entero & entero::operator=( entero const &b){
	this->_n=b._n;
	return *this;
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

void insertarCerosDelante(int n,string & cad){
	for (int i = 0; i < n; ++i)
	{
		cad.insert(cad.begin(),'0');
	}
}

void insertarCerosDetras(int n,string & cad){
	for (int i = 0; i < n; ++i)
	{
		cad.push_back('0');
	}
}

void sumarNveces(entero &a,int n){
	entero b=a;
	cout<<a._n<<" "<<n<<endl;
	for (int i = 0; i < n-1; ++i)
	{
		a=a+b;
		cout<<a._n<<endl;
	}
}
