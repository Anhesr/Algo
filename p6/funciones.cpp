bool lugar(int k ,vector <int >x){
	for (int i = 1; i < k; ++i)
	{
		if(x[i]==x[k] || x[i]-x[k]==i-k )
			return false;
	}
	return true;
}

void bactracking(int n ,vector< vector <int> > mat){
	vector<int> x(n+1);
	x[1]=0;
	int k=1;
	while(k>0){
		x[k]=x[k]+1
		while(x[k]<=n && !lugar(k,x) ){
			x[k]=x[k]+1
		}
		if(x[k] <= n){
			if(k==n){
				mat.push_back(k);
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
void lasVegas(int n,vector <int>x, bool exito){
	x.resize(n+1);
	srand(time(NULL));
	vector<int> ok(n+1);
	int cont;
	for (int i = 1; i <=n; ++i)
	{
		x[i]=0;
	}
	for (int i = 1; i <=n ; ++i)
	{
		cont=0;
		for (int  j= 1; j <=n; ++j)
		{
			x[i]=j;
			if(lugar(i,x)){
				cont=cont+1;
				ok[cont]=j;
			}
		}
		if(cont==0){
			exito=false;
			return;
		}
		x[i]=ok[(rand()%cont)+1];
	}
	if(cont==0){
		exito=false;
	}
	else{
		exito=true;
	}
}

void dynamicprogrammingmethod::apply(){

	calculateSummations();

	int N=getOriginalCurve().getNumberPointsDigitalCurve();
	int M=getNumberPointsPolinomialAproximation();

	vector <vector <int> > E(N+1,vector<int>(M+1));
	vector <vector <int> > Father(N+1,vector<int>(M+1));
	vector <int> domain;

	double min;

	for (int i = 2; i <=N; ++i)
	{
		for (int j = 1; j < M; ++j)
		{
			E[i][j]=99999999;
		}
	}

	E[1][1]=0;

	for (int m= 2; m <= M; ++m)
	{
		for (int n = m; n < N; ++n)
		{
			for (int k = m-1; k < n-1; ++k)
			{
				min=E[k][m-1]+calculateISEvalue(k-1,n-1);
				if(min < E[n][m]){
					E[n][m]=min;
					Father[n][m]=k;
				}
			}
		}
	}

	domain.clear();
	int sig=N;
	domain.insert(domain.begin(),sig-1);

	for(int i=M;i>1;i--){
		sig=Father[sig][i];
		domain.insert(domain.begin(),sig-1);
	}

	setDomainPointsPosition(domain);

	calculatePolinomialAproximation();

}

void greedyMethod::Apply(){
	calculateSummations();

	collinearPointsElimination();

	getDomi

	int jump(n/M-1)
}

void ajuste(vector <int > n,vector<double>treales,a0,a1){
	vector<vector <double> >A(2,vector<double>(2));
	vector<vector <double> >B(2,vector<double>(1));
	vector<vector <double> >X(2,vector<double>(1));

	vector<double>z;

	for (int i = 0; i < n.size(); ++i)
	{
		z.push_back(factorial(n[i]));
	}

	for (int i = 0; i < 2; ++i)
	{
		B[i][0]=calcularSumatorio(z,i,treales,1);
		for (int j = 0; j < 2; ++j)
		{
			A[i][j]
		}
	}
}