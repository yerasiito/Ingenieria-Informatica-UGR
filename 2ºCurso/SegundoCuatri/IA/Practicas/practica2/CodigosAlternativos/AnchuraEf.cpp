bool ComportamientoJugador::pathFinding_Anchura(const estado &origen, const estado &destino, list<Action> &plan){
	// Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado, ComparaEstados> explorados, frontera; // Lista de Cerrados
	queue<nodo> Abiertos;                 // Lista de Abiertos

	nodo current;
	current.st = origen;
	current.secuencia.empty();

        Abiertos.push(current);
	frontera.insert(current.st);

	while (!Abiertos.empty() and (current.st.fila != destino.fila or current.st.columna != destino.columna))
	{
		Abiertos.pop();
		explorados.insert(current.st);

		// Generar descendiente de girar a la derecha 90 grados
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion + 2) % 8;

		if (explorados.find(hijoTurnR.st) == explorados.end())
		{
                    if(frontera.find(hijoTurnR.st) == frontera.end()){
			hijoTurnR.secuencia.push_back(actTURN_R);
			Abiertos.push(hijoTurnR);
                        frontera.insert(hijoTurnR.st);
                    }
		}

		// Generar descendiente de girar a la derecha 45 grados
		nodo hijoSEMITurnR = current;
		hijoSEMITurnR.st.orientacion = (hijoSEMITurnR.st.orientacion + 1) % 8;
		if (explorados.find(hijoSEMITurnR.st) == explorados.end())
		{
                    if(frontera.find(hijoSEMITurnR.st) == frontera.end()){
			hijoSEMITurnR.secuencia.push_back(actSEMITURN_R);
			Abiertos.push(hijoSEMITurnR);
                        frontera.insert(hijoSEMITurnR.st);
                    }
		}

		// Generar descendiente de girar a la izquierda 90 grados
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion + 6) % 8;
		if (explorados.find(hijoTurnL.st) == explorados.end())
		{
                    if(frontera.find(hijoTurnL.st) == frontera.end()){
			hijoTurnL.secuencia.push_back(actTURN_L);
			Abiertos.push(hijoTurnL);
                        frontera.insert(hijoTurnL.st);
                    }
		}

		// Generar descendiente de girar a la izquierda 45 grados
		nodo hijoSEMITurnL = current;
		hijoSEMITurnL.st.orientacion = (hijoSEMITurnL.st.orientacion + 7) % 8;
		if (explorados.find(hijoSEMITurnL.st) == explorados.end())
		{
                    if(frontera.find(hijoSEMITurnL.st) == frontera.end()){
			hijoSEMITurnL.secuencia.push_back(actSEMITURN_L);
			Abiertos.push(hijoSEMITurnL);
                        frontera.insert(hijoSEMITurnL.st);
                    }
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st))
		{
			if (explorados.find(hijoForward.st) == explorados.end())
			{
				if(frontera.find(hijoForward.st) == frontera.end()){
				hijoForward.secuencia.push_back(actFORWARD);
				Abiertos.push(hijoForward);
                                frontera.insert(hijoForward.st);
				}
			}
		}

		// Tomo el siguiente valor de la Abiertos
		if (!Abiertos.empty())
		{
			current = Abiertos.front();
		}
	}

	cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna)
	{
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else
	{
		cout << "No encontrado plan\n";
	}

	return false;
}
