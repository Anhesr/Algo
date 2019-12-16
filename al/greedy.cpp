void GreedyMethod::apply()
{
  //Completar

	//Summations are calculated
	calculateSummations();

	//Collinear points are eliminated
	collinearPointsElimination();


	int jump;

	jump = (int) ((getOriginalCurve().getNumberPointsDigitalCurve()) / (getNumberPointsPolygonalApproximation() - 1)); // GENERO EL SALTO


	vector <int> newDominantPointPosition; 

	for (int i = 0; i < getOriginalCurve().getNumberPointsDigitalCurve()-1; i = i+jump) // HASTA N-1 PARA NO COGER EL ÚLTIMO AUNQUE COINCIDA
	{																					// YA QUE LO AÑADO ABAJO SI O SI
		newDominantPointPosition.push_back(i); // VOY METIENDO LOS PUNTOS CORRESPONDIENTES AL SALTO
	}

	newDominantPointPosition.push_back(getOriginalCurve().getNumberPointsDigitalCurve()-1); // AÑADO AL FINAL EL PRIMER/ULTIMO PUNTO PARA CERRAR EL CICLO

	int aux1, aux2;

	long double errorT = 999999, error;

	while(abs(errorT) != abs(getISE())){ // SI EL ERROR TOTAL NO CAMBIA SE SALE DE LA ITERACCIÓN (PARTE OPCIONAL)
		errorT = abs(getISE()); // ACTUALIZO EL ERROR ANTERIOR
		for (int i = 0; i < newDominantPointPosition.size()-2; ++i) // HASTA N-2 PARA NO HACER VIOLACION DE SEGMENTO EN AUX2 DE ABAJO
		{
			aux1 = newDominantPointPosition[i];
			aux2 = newDominantPointPosition[i+2]; // COGO LOS DOS PUNTOS DOMINANTES DE LOS EXTREMOS DE LA COMPARACION
			error = abs(calculateISEValue(aux1, newDominantPointPosition[i+1])) + abs(calculateISEValue(newDominantPointPosition[i+1], aux2));
			for (int j = aux1+1; j < aux2; ++j) // Y DOY A ERROR EL VALOR ACTUAL DE LOS PUNTOS DOMINANTES
			{ // VOY COMPARANDO CON TODOS LOS PUNTOS INTERMEDIOS DE i e i+2 EL ERROR
				if(abs(error) > abs(calculateISEValue(aux1, j)) + abs(calculateISEValue(j, aux2))){
					error = abs(calculateISEValue(aux1, j)) + abs(calculateISEValue(j, aux2)); // SI ES MENOR ACTUALIZO EL ERROR
					newDominantPointPosition[i+1] = j; // Y ACTUALIZO EL PUNTO DOMINANTE
				}
			}
		}
		
	}	

	setDominantPointsPosition(newDominantPointPosition); // ACTUALIZO EL VECTOR
	//Obtaining polygonal approximattion
	calculatePolygonalApproximation();

	//Set the number of points of the polygonal approximation
	setNumberPointsPolygonalApproximation(newDominantPointPosition.size());

}