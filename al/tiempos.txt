void tiemposBacktracking(){
	int min, max, incremento, rep;
	cout << "Introduzca el valor mínimo de n:\n\n\t";
	cin >> min;
	fflush(stdin);
	system("clear");

	cout << "Introduzca el valor máximo de n:\n\n\t";
	cin >> max;
	fflush(stdin);
	system("clear");

	cout << "Introduzca el incremento del valor de n:\n\n\t";
	cin >> incremento;
	fflush(stdin);
	system("clear");

	cout << "Introduzca el número de veces que se repetirá la operación para cada valor de n:\n\n\t";
	cin >> rep;
	fflush(stdin);
	system("clear");

	if(comprobacion(min, max, incremento, rep) == -1)
		return;

	cout << "Realizando calculos. Porfavor, espere..." << endl;

	Clock time;
	vector<double> tiempos;
	vector <int> n;
	vector <double> t;
	tiempos.resize(rep);
	vector< vector <int> > sol;

	for(int i=min; i<=max; i=i+incremento){
		for(int j=0; j<rep; j++){
			time.start();
			n_Reinas_backtracking(i, sol);
			if (time.isStarted())
			{
				time.stop();
				tiempos[j]=time.elapsed();
			}
			sol.resize(0);
		}
		n.push_back(i);
		t.push_back(media(tiempos));
	}

	double a0, a1;
	vector<double> tiemposEstimados;

	ajuste(n, t, a0, a1);
	
	calcularTiemposEstimados(n, t, a0, a1, tiemposEstimados);

	ofstream fs("Datos.txt"); 

	for (int i = 0; i < n.size(); ++i)
	{
		fs << n[i] << " " << t[i] << " " << tiemposEstimados[i] << endl;
	}
	
	fs.close();
	cout << endl;
	system("clear");
	cout << "Resultados escritos con exito en Datos.txt" << endl;
	cout << "con la siguiente estructura:\n" << endl;
	cout << "n tiempoReal tiempoEstimado\n" << endl;
}

int factorial(int n){
	if(n < 2){
		return 1;
	}
	return factorial(n-1) * n;
}

void calcularTiemposEstimados(const vector <int> &n, const vector <double> &tiemposReales, const double &a0, const double &a1, vector <double> &tiemposEstimados){
	for (int i = 0; i < n.size(); ++i){
		tiemposEstimados.push_back(a0 + (a1* factorial(n[i])));
	}
}

double sumatorio(const vector<double> x, const vector<double> y, int expx, int expy){
	double suma = 0;
	for (int i = 0; i < x.size() && i < y.size(); ++i)
	{
		suma = suma + ((pow(x[i],expx))*(pow(y[i], expy)));
	}
	return suma;
}

void ajuste(const vector <int> &n, const vector <double> &tiemposReales, double &a0, double &a1)
{
	vector <double> z;
	for (int i = 0; i < n.size(); ++i){
		z.push_back(factorial(n[i]));
	}
	double aux;
	aux=(n.size()*sumatorio(z,tiemposReales))-(sumatorio(z,z,1,0)*sumatorio(tiemposReales,z,1,0));
	a1=aux/((n.size()*sumatorio(z,z,2,0))-(pow(sumatorio(z,z,1,0), 2)));

	a0=((media(tiemposReales))-(a1*media(z)));
	
}

double media(const vector <double> &v){
	double suma = 0;
	for(int i=0; i < (int) v.size(); i++){
		suma = suma + v[i];
	}
	return (double) (suma/(int)v.size());
}

int comprobacion(int min, int max, int incremento, int rep){
	if(min > max){
		cout << "Error, el minimo introducido es mayor que el máximo" << endl;
		return -1;
	}
	if(max <= 0){
		cout << "Error, el maximo es menor o igual a 0" << endl;
		return -1;
	}
	if(min <= 0){
		cout << "Error, el minimo es menor o igual a 0" << endl;
		return -1;
	}
	if(incremento <= 0){
		cout << "Error, el incremento es menor o igual a 0" << endl;
		return -1;
	}
	if(rep <= 0){
		cout << "Error, la repeticion es menor o igual a 0" << endl;
		return -1;
	}
	return 1;
}