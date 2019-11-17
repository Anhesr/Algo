#include "Prac3.hpp"
using namespace std;


int main(int argc, char const *argv[])
{
	int op;

	do{
	entero a,b;
	cout<< "¿Qué operación desea realizar?"<<endl;
	cout<< "	1. Suma de dos enteros grandes"<<endl;
	cout<< "	2. Producto de dos enteros grandes"<<endl;
	cout<< "	3. Factorial"<<endl;
	cout<< "	4. Salir"<<endl;
	cin>>op;
	system("clear");

	switch(op){
		case 1:{
			cout<<"Introduzca el valor del primer entero"<<endl;
			cin>>a;
			cout<<"Introduzca el valor del segundo entero"<<endl;
			cin>>b;
			system("clear");
			cout<<"El resultado de la suma de "<<a._n<<" mas "<< b._n;
			entero aux=a+b;
			cout<<" es : " <<aux._n<<endl;
		}break;
		case 2:{
			cout<<"Introduzca el valor del primer entero"<<endl;
			cin>>a;
			cout<<"Introduzca el valor del segundo entero"<<endl;
			cin>>b;
			system("clear");
			cout<<"El resultado del producto de "<<a._n<<" por "<< b._n;
			entero aux=a*b;
			cout<<" es : " <<aux._n<<endl;
		}break;
		case 3:{
			cout<<"Introduzca el valor del factorial"<<endl;
			cin>>a;
			b=calcularFactorial(a);
			cout<<"El resultado del factorial de "<<a._n<<" es :"<<endl;
			cout<<b._n<<endl;

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


entero & entero::operator+(entero b){
		vector <int> x, y;

		int aux=0;
		entero suma;
		suma._n="";
		int acc=0;

		if(this->_n.length() > b._n.length()){
			insertarCerosDelante(this->_n.length() - b._n.length() ,b._n);
		}
		if(this->_n.length() < b._n.length()){
			insertarCerosDelante(b._n.length()-this->_n.length(),this->_n);
		}
		
		for (int i = 0; i < this->_n.length(); ++i)
		{
			x.insert(x.begin() , this->_n[i] - '0');
		}

		for (int i = 0; i < b._n.length(); ++i)
		{
			y.insert(y.begin() , b._n[i] - '0');
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
	entero baux=b;

	if(n <= 4){
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

		if(this->_n.size() < b._n.size()){
			insertarCerosDelante(b._n.size() - this->_n.size(),this->_n);
		}
		else if(this->_n.size() > b._n.size()){
			insertarCerosDelante(this->_n.size() - b._n.size(), baux._n);
		}

		divideCadena(this->_n,w._n,x._n);
		divideCadena(baux._n,y._n,z._n);

		aux1=w;aux2=w;aux3=x;aux4=x;
		aux1*y;
		aux2*z;
		aux3*y;
		aux4*z;
		aux2+aux3;
		insertarCerosDetras(s,aux2._n);
		aux2+aux4;
		insertarCerosDetras(s*2,aux1._n);
		aux1+aux2;
		*this=aux1;
		quitarCeros(this->_n);
		return(*this);
		
	}

}

entero & entero::operator*( int const &num){
	entero w,x,y,z,b;
	char buff[50];
	sprintf(buff,"%d",num);
	b._n=string(buff);

	int n= max(this->_n.size(),b._n.size());
	int s=n/2;
	entero aux1,aux2,aux3,aux4;

	if(this->_n.size()<=4 || b._n.size()<=4 ){
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

		aux1=w;aux2=w;aux3=x;aux4=x;
		aux1*y;
		aux2*z;
		aux3*y;
		aux4*z;
		aux2+aux3;
		insertarCerosDetras(s,aux2._n);
		aux2+aux4;
		insertarCerosDetras(s*2,aux1._n);
		aux1+aux2;
		*this=aux1;
		quitarCeros(this->_n);
		return(*this);
		
	}

}

entero & entero::operator=( entero const &b){
	this->_n=b._n;
	return *this;
}

void divideCadena(string cad,string &tr1,string &tr2){


	if(cad.size() %2==0){
		tr1=cad.substr(0,cad.size()/2 );
		tr2=cad.substr(cad.size()/2);
	}

	else{
		tr1=cad.substr(0,(int) cad.size()/2 + 1 );
		tr2=cad.substr((int)cad.size()/2 + 1);
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
	entero b;
	b._n="0";
	for (int i = 0; i < n; ++i)
	{
		b=b+a;
	}
	a=b;
}
ostream& operator << (ostream &o,const entero &n)
{
    o << n._n;
    return o;
}

istream& operator >> (istream &i, entero &n)
{
    i >> n._n;
    i.ignore();
    return i;
}

entero calcularFactorial(entero n){
	entero f;
	f._n='1';
	for (int i = 1; i < atoi(n._n.c_str())+1; ++i)
	{
		f=f*i;
	}
	return f;
}

void quitarCeros(string &s){
	int i=0;
	while(s[i] == '0' && s.size() > 1){
		s.erase(i);
	}
}