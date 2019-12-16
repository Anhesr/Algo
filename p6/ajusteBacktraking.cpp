#include "ajusteBacktraking.hpp"



double calcularSumatorio(vector <double> v1, vector <double> v2, int exp1 , int exp2){

	double sum=0;

	for(int i=0; i < (int) v1.size() ; i++){
		sum= sum +( pow(v1[i], exp1 ) * pow(v2[i], exp2 ) );
	}

	return sum ;

}

void ajusteTiempos(){
  std::vector<double> vaux;
  int n,min,max,inc;
  int rep=1;
  int conta=0;
  double a0,a1;
  double med;
  double temp;
  Clock time;
  vector <double> mu;
  vector <double> tiemposReales;
  vector <double> tiemposEstimados;
  vector <vector <int> > mat;
  string op;

  cout<<"Introduzca el minimo de elementos : "<<endl;

  cin >> min ;

  cout<<"Introduzca el maximo de elementos : "<<endl;

  cin >> max ;

  cout<<"Introduzca el incremento : "<<endl;

  cin >> inc ;



  for(int i=min ; i <= max ;){

  
  for(int j=0 ; j < rep ;j++ ){

      time.start();

      reinas(i,mat);

      if (time.isStarted())
    {
      time.stop();
      vaux.push_back(time.elapsed());
    }
    mat.clear();
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

  ajusteFactorial(mu,tiemposReales,a0,a1);

  calcularTiemposEstimadosFactorial(mu,tiemposReales,a0,a1,tiemposEstimados);

  escribirFichero(mu,tiemposReales,tiemposEstimados);

}

double calculaMedia(const vector <double> v){

	double sum = 0;

	for(int i = 0 ; i< v.size(); i++){
		sum=sum+v[i];
	}

	sum= sum/(int)v.size();

	return sum;
}

void ajusteFactorial(const vector <double> &n, const vector <double> &tiemposReales, double &a0, double &a1){


  	vector <double> z;

	for(int i=0;i< (int) n.size();i++){

		z.push_back(calcularFactorial(n[i]));

	}

  	a1=  (((int)n.size()*calcularSumatorio(z,tiemposReales,1,1)) - (calcularSumatorio(z,tiemposReales,1,0) * calcularSumatorio(z,tiemposReales,0,1) ))
		/ ( ((int)n.size()*calcularSumatorio(z,tiemposReales,2,0)) -  pow( calcularSumatorio(z,tiemposReales,1,0) , 2) ) ;

	a0= calculaMedia(tiemposReales) - (a1 * calculaMedia(z));
	


}


double calcularFactorial(double n){
	if(n<2){
		return 1;
	}
	else{
		return calcularFactorial(n-1) *n;
	}
}

void escribirFichero(const vector <double> &n, const vector <double> &tiemposReales,const vector <double> &tiemposEstimados){
	ofstream fs("Datos.txt");

	for(int i=0;i< (int) n.size();i++){

	fs << n[i] << " " << tiemposReales[i] << " " << tiemposEstimados[i] <<endl;

	}

	fs.close();
}

void calcularTiemposEstimadosFactorial(vector <double> n, const vector <double> &tiemposReales, 
	const double &a0, const double &a1, vector<double> &tiemposEstimados){

		for(int i=0; i < (int) n.size() ; i++){
			tiemposEstimados.push_back( a0 + (a1 *  calcularFactorial(n[i])) ) ;
		}

}