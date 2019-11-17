#include "Practica1.hpp"

using namespace std;

int main()
{
    int op;
    while(op != 3){
    cout<<"Elija una opción:"<<endl;
    cout<<"1.Ajuste del algoritmo Quicksort"<<endl;
    cout<<"2.Ajuste del algoritmo del producto de matrices"<<endl;
    cout<<"3.Salir"<<endl;
    cin>>op;
    switch(op){
      case 1:{
        ajusteQuicksort();
      }break;
      case 2:{
        multiplicacion();
     }break;
     case 3: {
        cout<<"Saliendo del sistema"<<endl;
     }break;
     default:{
      cout<<"Opción desconocida"<<endl;
     }break;
  }
  }
}

void ajusteQuicksort(){
    vector<int> v;
  std::vector<double> vaux;
  int n,min,max,inc,rep;
  double med;
  double temp;
  Clock time;
  vector <double> mu;
  vector <double> tiemposReales;
  double a0,a1;
  string op;


  cout<<"Introduzca el minimo de elementos : "<<endl;

  cin >> min ;

  cout<<"Introduzca el maximo de elementos : "<<endl;

  cin >> max ;

  cout<<"Introduzca el incremento : "<<endl;

  cin >> inc ;

  cout<<"Introduzca el numero de repeticiones : "<<endl;

  cin >> rep ;


  for(int i=min ; i < max ;){

  
  v.resize(i);

  for(int j=0 ; j < rep ;j++ ){
      rellenarVector(v);

      time.start();

      quicksort(v,0, (int) v.size()-1,temp);

      if (time.isStarted())
    {
      time.stop();
      vaux.push_back(time.elapsed());
    }
  }

  med = calculaMedia(vaux);

  mu.push_back(i);
  tiemposReales.push_back(med);

  i= i + inc;

  estaOrdenado(v);

  }
  
  ajusteNlogN(mu,tiemposReales,a0,a1);

  cout<< "¿Quiere realizar una estimación de tiempo? S/N"<< endl;
  cin >> op;

  if(op == "S"){
    while(n!=0){
    cout<< "Introduzca el numero de elementos"<< endl;
    cin>>n;
    if(n!=0)
    cout<< " El tiempo estimado es "<< (calcularTiempoEstimadoNlogN(n,a0,a1)/86400000000)<<" dias"  <<endl;
    }
  }



}




void rellenarVector(vector<int> &v){
  srand(time(NULL));

  for(int i=0;i< v.size();i++){

    v[i] = rand() % 10000;
  }
}

void quicksort(vector<int> &v,int start, int end , double &temp){

    int pivot;
    Clock time;

    time.start();

    if (start < end) {
        pivot = divide(v, start, end);
        quicksort(v, start, pivot - 1,temp);
        quicksort(v, pivot + 1, end,temp);
    }

}

int divide(vector<int> &v, int start, int end){
    int left;
    int right;
    int pivot;
    int temp;
 
    pivot = v[start];
    left = start;
    right = end;

    while (left < right) {
        while (v[right] > pivot) {
            right--;
        }
 
        while ((left < right) && (v[left] <= pivot)) {
            left++;
        }
 
        if (left < right) {
            temp = v[left];
            v[left] = v[right];
            v[right] = temp;
        }
    }
 
    temp = v[right];
    v[right] = v[start];
    v[start] = temp;
 
    return right;
}

void estaOrdenado(const vector <int> &v){
  for(int i=0;i< (int) v.size()-1; i++){
      assert( v[i] <= v[i+1] );
  }

}

double calculaMedia(const vector <double> v){

	double sum = 0;

	for(int i = 0 ; i< v.size(); i++){
		sum=sum+v[i];
	}

	sum= sum/(int)v.size();

	return sum;
}

void ajusteNlogN(const vector <double> &n, const vector <double> &tiemposReales, double &a0, double &a1){

	vector <double> z;
	vector <double> tiemposEstimados;

	for(int i=0;i< (int) n.size();i++){
		z.push_back(n[i] * log(n[i]));
	}

	a1=  (((int)n.size()*calcularSumatorio(z,tiemposReales,1,1)) - (calcularSumatorio(z,tiemposReales,1,0) * calcularSumatorio(z,tiemposReales,0,1) ))
		/ ( ((int)n.size()*calcularSumatorio(z,tiemposReales,2,0)) -  pow( calcularSumatorio(z,tiemposReales,1,0) , 2) ) ;

	a0= calculaMedia(tiemposReales) - (a1 * calculaMedia(z));
	
	calcularTiemposEstimadosNlogN(n,tiemposReales,a0,a1,tiemposEstimados);


	ofstream fs("Datos.txt");

	for(int i=0;i< (int) n.size();i++){

	fs << n[i] << " " << tiemposReales[i] << " " << tiemposEstimados[i] <<endl;

	}

	fs.close();


  	cout<<"El coeficiente de determinación del ajuste es: "<< calcularCoeficienteDeterminacion(tiemposReales,tiemposEstimados) <<endl;

}

double calcularSumatorio(vector <double> v1, vector <double> v2, int exp1 , int exp2){

	double sum=0;

	for(int i=0; i < (int) v1.size() ; i++){
		sum= sum +( pow(v1[i], exp1 ) * pow(v2[i], exp2 ) );
	}

	return sum ;

}

void calcularTiemposEstimadosNlogN(const vector <double> &n, const vector <double> &tiemposReales, 
	const double &a0, const double &a1, vector<double> &tiemposEstimados){

		for(int i=0; i < (int) n.size() ; i++){
			tiemposEstimados.push_back( a0 + (a1 * (n[i] * log(n[i]) ) ));
		}

}

double calcularCoeficienteDeterminacion(const vector <double> &tiemposReales,const vector <double> &tiemposEstimados){

  double varianzaR=calcularVarianza(tiemposReales);
  double varianzaE=calcularVarianza(tiemposEstimados);

  return varianzaE/varianzaR;


}

double calcularVarianza(const vector <double> v){
  double media=calculaMedia(v);
  double varianza;
  for (int i = 0; i < (int) v.size(); ++i)
  {
    varianza= varianza+ pow(v[i] - media,2);
  }

  varianza=varianza/(int) v.size();

  return varianza;

}

double calcularTiempoEstimadoNlogN(const double &n, const  double &a0, const double &a1){
  return (a0 +(a1 * n * log(n) ) );
}


// Ej2 : Multiplicacion de matrices

void multiplicacion(){
  std::vector<double> vaux;
  int n,min,max,inc;
  int rep=1;
  int conta=0;
  double med;
  double temp;
  Clock time;
  vector <double> mu;
  vector <double> tiemposReales;
  vector <double> a;
  vector <double> tiemposEstimados;
  string op;


  cout<<"Introduzca el minimo de elementos : "<<endl;

  cin >> min ;

  cout<<"Introduzca el maximo de elementos : "<<endl;

  cin >> max ;

  cout<<"Introduzca el incremento : "<<endl;

  cin >> inc ;


  for(int i=min ; i <= max ;){

  
  vector <vector <double> > mat1(i,vector <double> (i));

  for(int j=0 ; j < rep ;j++ ){
      rellenarMatriz(mat1);

      time.start();

      productoMatrices(mat1,mat1);

      if (time.isStarted())
    {
      time.stop();
      vaux.push_back(time.elapsed());
    }
  }

  med = calculaMedia(vaux);

  mu.push_back(i);
  tiemposReales.push_back(med);

  i= i + inc;

    if((i > max)&&(conta=0)){
      i=max;
      conta++;
    }
  }

  ajustePolinomico(mu,tiemposReales,a);

  calcularTiemposEstimadosPolinomico(mu,tiemposReales,a,tiemposEstimados);


  cout<< "¿Quiere realizar una estimación de tiempo? S/N"<< endl;
  cin >> op;



  if(op == "S"){
    while(n!=0){
    cout<< "Introduzca el numero de elementos"<< endl;
    cin>>n;
    if(n!=0)
    cout<< " El tiempo estimado es "<< (calcularTiempoEstimadoPolinomico(n,a)/86400000000)<<" dias" <<endl;
    }
  }



}


void rellenarMatriz(vector <vector <double> > &v ){

  double aux;

  for (int i = 0; i < (int) v[1].size(); ++i)
  {
    for (int j = 0; j < (int) v[1].size(); ++j)
    {
      aux=rand() % 11;
      v[i][j] =1.05- aux/100;
    }
  }
}

void productoMatrices(vector <vector <double> > v1 , vector <vector <double> > v2){

  vector <vector <double> > mat3((int) v1[1].size(),vector <double> ((int) v1[1].size()));
  for(int i=0; i<(int) v1[1].size(); ++i)
  {
    for(int j=0; j<(int) v1[1].size(); ++j)
    {
      mat3[i][j] = 0;
    }
  }

  for(int i=0; i<(int) v1[1].size(); ++i)
  {
    for(int j=0; j<(int) v1[1].size(); ++j)
    {
      for(int z=0; z<(int) v1[1].size(); ++z){

        mat3[i][j] += v1[i][z] * v2[z][j];
      }
    }
  }


}

void ajustePolinomico(const vector <double> &n, const vector <double> &tiemposReales, vector <double> &a){

  vector <vector <double> > A(4,vector <double> (4));
  vector <vector <double> > B(4,vector <double> (1));
  vector <vector <double> > X(4,vector <double> (1));

  for (int i=0 ; i< 4 ;i++){
    for (int j = 0; j < 4; ++j)
    {
      A[i][j]=calcularSumatorio(n,tiemposReales,i+j,0);
    }
  }

  A[0][0]=n.size();

  for (int i = 0; i < 4; ++i)
  {
    B[i][0]=calcularSumatorio(n,tiemposReales,i,1);
  }

  resolverSistemaEcuaciones(A,B,4,X);
  for (int i = 0; i < 4; ++i)
  {
    a.push_back(X[i][0]);
  }

}

void calcularTiemposEstimadosPolinomico(const vector <double> &n, const vector <double> &tiemposReales, const vector <double> &a, vector <double> &tiemposEstimados){
  for (int i = 0; i <(int) n.size(); ++i)
  {
    double aux = a[0]+ (a[1]*n[i]) +(a[2]*pow(n[i],2)) +(a[3]*pow(n[i],3));

    tiemposEstimados.push_back(aux);
  }

  ofstream fs("Datos.txt");

  for(int i=0;i< (int) n.size() ;i++){

  fs << n[i] << " " << tiemposReales[i] << " " << tiemposEstimados[i] <<endl;

  }
  fs.close();
}

double calcularTiempoEstimadoPolinomico(const double &n, const vector <double> &a){
  return a[0]+ (a[1]*n) +(a[2]*pow(n,2)) +(a[3]*pow(n,3));
}


