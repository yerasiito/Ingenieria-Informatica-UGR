#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <algorithm>
#include <cmath>
#include <set>
#include <stack>
#include <deque>
#include <queue>
#include <map>
#include <chrono>

string ActionToString(const Action & accion){
    string accionS;
    switch(accion){
        case(0):
            accionS = "actFORWARD";
            break;
        case(1):
            accionS = "actTURN_L";
            break;
        case(2):
            accionS = "actTURN_R";
            break;
        case(3):
            accionS = "actSEMITURN_L";
            break;
        case(4):
            accionS = "actSEMITURN_R";
            break;
        case(5):
            accionS = "actWHEREIS";
            break;
        case(6):
            accionS = "actIDLE";
            break;
    }
    return accionS;
}

void ComportamientoJugador::checkObjetivo(list<estado> & objetivos, const estado & actual){
    if(!objetivos.empty() and !recargando){
        estado aux = objetivos.front();
        if(aux.fila == actual.fila and aux.columna == actual.columna){
            objetivos.pop_front();
            cout << "OBJETIVO COMPLETADO" << endl;
        }
    }

}

void ComportamientoJugador::informar(){
    cout << "Posicion según sensores: fila " << sensorActual.posF << " columna " << sensorActual.posC << " ";
    switch(sensorActual.sentido){
            case 0: cout << "Norte" << endl; break;
            case 1: cout << "Noreste" << endl; break;
            case 2: cout << "Este " << endl; break;
            case 3: cout << "Sureste" << endl; break;
            case 4: cout << "Sur" << endl; break;
            case 5: cout << "Suroeste" << endl; break;
            case 6: cout << "Oeste" << endl; break;
            case 7: cout << "Noroeste" << endl; break;
    }
    cout << "Posicion del agente (calculada): ";
    cout << "Fila: " << actual.fila;;
    cout << " Col : " << actual.columna;
    cout << " Ori : " << actual.orientacion << endl;
        
    cout << "Terreno: ";
    for (int i=0; i<sensorActual.terreno.size(); i++)
            cout << sensorActual.terreno[i];
    cout << endl;

    cout << "Superficie: ";
    for (int i=0; i<sensorActual.superficie.size(); i++)
            cout << sensorActual.superficie[i];
    cout << endl;

    cout << "Colisión: " << sensorActual.colision << endl;
    cout << "Reset: " << sensorActual.reset << endl;
    cout << "Vida: " << sensorActual.vida << endl;
    cout << endl;
}

// Este es el método principal que se piden en la practica.
// Tiene como entrada la información de los sensores y devuelve la acción a realizar.
// Para ver los distintos sensores mirar fichero "comportamiento.hpp"
Action ComportamientoJugador::think(Sensores sensores)
{       
	Action accion = actIDLE;
        sensorActual = sensores;
        
        //Funciones de checkeo e inicializacion de variables
        
        checkReset(accion);
        
        checkSensores(accion);
        
        checkObjects();
        
        actualizaOrientacion();
        
        vision(sensores);
        
        setZonaPeligro();
             
        //Comprueba que está en su objetivo o no
        checkObjetivo(objetivos, actual);
                
        capturaDestinos();

        checkBateria();
        
        if(sensores.nivel < 3){
            if(!hayPlan)
                hayPlan = pathFinding(sensores.nivel, actual, objetivos, plan);
        }
        else{
            if( (!hayPlan or (descubriendoMapa and !objetivoBateria)) and !recargando)
                hayPlan = pathFinding(sensores.nivel, actual, objetivos, plan);
        }
        
        //Ejecuta el plan del agente
        if(hayPlan and plan.size() > 0){
            accion = plan.front();
            plan.erase(plan.begin());
            if(plan.empty())
                hayPlan = false;
        }
        else{
            cout << "No se pudo encontrar un plan" << endl;
        }
        
        //Imprime datos en la terminal
        informar();
        
	// Recordar la última acción
	ultimaAccion = accion;
        
        cout << "Accion final " << ActionToString(accion) << endl;
        cout << "--------------------------------------------------------------" << endl;

	return accion;
}
    
void ComportamientoJugador::capturaDestinos(){
    //El nivel 3 genera sus "objetivos"
    if(sensorActual.nivel == 3){
        //Checkea que el objetivo actual no sea un obstaculo
        if(!objetivos.empty() and porDescubrir){ 
            while(EsObstaculo(mapaResultado[objetivos.front().fila][objetivos.front().columna]) or
                (mapaResultado[objetivos.front().fila][objetivos.front().columna] == 'A' and actual.item != Objetos::BIKINI or
                mapaResultado[objetivos.front().fila][objetivos.front().columna] == 'B' and actual.item != Objetos::ZAPATILLAS)){
                objetivos.pop_front();
                    porDescubrir = pathFindingNivel3(actual);
            }
        }
        else if(porDescubrir){
            porDescubrir = pathFindingNivel3(actual);
        }
    } //El resto de niveles leen los parametros de destino
    else{
        if(objetivos.empty()){
            for (int i = 0; i < sensorActual.num_destinos; i++){
                estado aux;
                aux.fila = sensorActual.destino[2 * i];
                aux.columna = sensorActual.destino[2 * i + 1];
                objetivos.push_back(aux);
            }
        }
    }
}

void ComportamientoJugador::checkBateria(){
    objetivoBateria = (objetivos.front().fila == puntoRecarga.fila and objetivos.front().columna == puntoRecarga.columna);
        if(sensorActual.terreno[0] == 'X'){
            if(sensorActual.bateria < 2990){
                hayPlan = false;
                recargando = true;
            }
            else{
                recargando = false;
                cout << "Objetivos.size " << objetivos.size() << endl;
                if(objetivoBateria)
                    objetivos.pop_front(); //Quita el objetivo bateria
            }
        }
        else
            vaAPorBateria();
}

void ComportamientoJugador::vaAPorBateria(){
    if(!recargando and puntoRecarga.fila != 0 and sensorActual.bateria < 1000 and sensorActual.vida > 750
            and objetivos.front().fila != puntoRecarga.fila and objetivos.front().columna != puntoRecarga.columna){
        objetivos.push_front(puntoRecarga); //Añade el punto de recarga
        plan.clear(); //Termina el plan
        
        hayPlan = pathFinding(sensorActual.nivel, actual, objetivos, plan);
    }
}

// Llama al algoritmo de busqueda que se usara en cada comportamiento del agente
// Level representa el comportamiento en el que fue iniciado el agente.
bool ComportamientoJugador::pathFinding(int level, const estado &origen, const list<estado> &destino, list<Action> &plan)
{
        estado un_objetivo;
	switch (level)
	{
	case 0:
		cout << "Demo\n";
		un_objetivo = objetivos.front();
		cout << "Fila objetivo: " << un_objetivo.fila << ". Columna Objetivo: " << un_objetivo.columna << endl;
		return pathFinding_Profundidad(origen, un_objetivo, plan);
		break;
	case 1:
		cout << "Optimo numero de acciones\n";
		// Incluir aqui la llamada al busqueda en anchura
		un_objetivo = objetivos.front();
		cout << "Fila objetivo: " << un_objetivo.fila << ". Columna Objetivo: " << un_objetivo.columna << endl;
		return pathFinding_Anchura(origen, un_objetivo, plan);
		break;
	case 2:
		cout << "Optimo en coste\n";
		// Incluir aqui la llamada al busqueda de costo uniforme/A*
		un_objetivo = objetivos.front();
		cout << "Fila objetivo: " << un_objetivo.fila << ". Columna Objetivo: " << un_objetivo.columna << endl;
		return pathFinding_CostoUniforme(origen, un_objetivo, plan);
		break;
	case 3:
                if(porDescubrir){
                    cout << "Reto 1: Descubrir el mapa\n";
                    un_objetivo = objetivos.front();
                    cout << "Fila objetivo: " << un_objetivo.fila << " Columna Objetivo:" << un_objetivo.columna << endl;
                    return pathFinding_CostoUniforme(origen, un_objetivo, plan);
                }
		break;
	case 4:
		cout << "Reto 2: Maximizar objetivos\n";
		// Incluir aqui la llamada al algoritmo de busqueda para el Reto 2
                un_objetivo = objetivos.front();
                if(EsPeligro(un_objetivo.fila, un_objetivo.columna)){ //Si el objetivo está campeado por un lobo o aldeano, elige otro
                    objetivos.pop_front();
                    objetivos.push_back(un_objetivo);
                    un_objetivo = objetivos.front();
                }
		cout << "Fila objetivo: " << un_objetivo.fila << " Columna Objetivo:" << un_objetivo.columna << endl;
		return pathFinding_CostoUniforme(origen, un_objetivo, plan);
		break;
	}
	return false;
}

//---------------------- Implementación de la busqueda en profundidad ---------------------------

// Dado el codigo en caracter de una casilla del mapa dice si se puede
// pasar por ella sin riegos de morir o chocar.
bool ComportamientoJugador::EsObstaculo(unsigned char casilla)
{
	if (casilla == 'P' or casilla == 'M' or sensorActual.superficie[2] == 'a' or sensorActual.superficie[2] == 'l')
		return true;
	else
		return false;
}

void ComportamientoJugador::MatrizPeligro(int fil, int col, bool entidad){
    estado aux;
    int dist = 1;
    
    if(entidad) //Si es lobo, aumentar distancia
        dist = 1;
    
    for(int i = fil-dist; i < fil+dist+1; i++){
        for(int j = col; j < col+dist+1; j++){
            aux.fila = i;
            aux.columna = j;
            if(fil != actual.fila and col != actual.columna) //No incluye la posicion del jugador
                zonaPeligro.push_back(aux);
        }
    }
}

    
bool ComportamientoJugador::EsPeligro(int fila, int columna){
    estado aux;
    bool peligro = false;
    for(auto it : zonaPeligro){
        aux = it;
        if(aux.fila == fila and aux.columna == columna)
            peligro = true;
    }
    
    return peligro;
}

void ComportamientoJugador::setZonaPeligro(){
    estado aux;
    zonaPeligro.clear();
    while(!aldeanos.empty()){
        MatrizPeligro(aldeanos.front().fila, aldeanos.front().columna, 0);
        aldeanos.pop_front();
    }        
    while(!lobos.empty()){
        MatrizPeligro(lobos.front().fila, lobos.front().columna, 1);
        lobos.pop_front();
    }               
}

//Testeo nivel 3
//void ComportamientoJugador::testeoLevel3(){
//    estado aux;
//    do{
//        objetivos.clear();
//        aux.fila = 3 + rand() % (mapaResultado.size() - 6);
//        aux.columna = 3 + rand() % (mapaResultado.size() - 6);
//        objetivos.push_back(aux);                
//    }
//    while(EsObstaculo(mapaResultado[objetivos.front().fila][objetivos.front().columna]));
//
//}

// Comprueba si la casilla que hay delante es un obstaculo. Si es un
// obstaculo devuelve true. Si no es un obstaculo, devuelve false y
// modifica st con la posición de la casilla del avance.
bool ComportamientoJugador::HayObstaculoDelante(estado &st)
{
	int fil = st.fila, col = st.columna;

	// calculo cual es la casilla de delante del agente
	switch (st.orientacion)
	{
	case 0:
		fil--;
		break;
	case 1:
		fil--;
		col++;
		break;
	case 2:
		col++;
		break;
	case 3:
		fil++;
		col++;
		break;
	case 4:
		fil++;
		break;
	case 5:
		fil++;
		col--;
		break;
	case 6:
		col--;
		break;
	case 7:
		fil--;
		col--;
		break;
	}

	// Compruebo que no me salgo fuera del rango del mapa
	if (fil < 0 or fil >= mapaResultado.size())
		return true;
	if (col < 0 or col >= mapaResultado[0].size())
		return true;

	// Miro si en esa casilla hay un obstaculo infranqueable
	if (!EsObstaculo(mapaResultado[fil][col]) and !EsPeligro(fil, col))
	{
		// No hay obstaculo, actualizo el parametro st poniendo la casilla de delante.
		st.fila = fil;
		st.columna = col;
		return false;
	}
        else
                return true;
}

// Implementación de la busqueda en profundidad.
// Entran los puntos origen y destino y devuelve la
// secuencia de acciones en plan, una lista de acciones.
bool ComportamientoJugador::pathFinding_Profundidad(const estado &origen, const estado &destino, list<Action> &plan)
{
	// Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado, ComparaEstados> Cerrados; // Lista de Cerrados
	stack<nodo> Abiertos;                 // Lista de Abiertos

	nodo current;
	current.st = origen;
	current.secuencia.empty();

	Abiertos.push(current);

	while (!Abiertos.empty() and (current.st.fila != destino.fila or current.st.columna != destino.columna))
	{
		Abiertos.pop();
		Cerrados.insert(current.st);

		// Generar descendiente de girar a la derecha 90 grados
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion + 2) % 8;

                if (Cerrados.find(hijoTurnR.st) == Cerrados.end())
		{
			hijoTurnR.secuencia.push_back(actTURN_R);
			Abiertos.push(hijoTurnR);
		}

		// Generar descendiente de girar a la derecha 45 grados
		nodo hijoSEMITurnR = current;
		hijoSEMITurnR.st.orientacion = (hijoSEMITurnR.st.orientacion + 1) % 8;
		if (Cerrados.find(hijoSEMITurnR.st) == Cerrados.end())
		{
			hijoSEMITurnR.secuencia.push_back(actSEMITURN_R);
			Abiertos.push(hijoSEMITurnR);
		}

		// Generar descendiente de girar a la izquierda 90 grados
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion + 6) % 8;
		if (Cerrados.find(hijoTurnL.st) == Cerrados.end())
		{
			hijoTurnL.secuencia.push_back(actTURN_L);
			Abiertos.push(hijoTurnL);
		}

		// Generar descendiente de girar a la izquierda 45 grados
		nodo hijoSEMITurnL = current;
		hijoSEMITurnL.st.orientacion = (hijoSEMITurnL.st.orientacion + 7) % 8;
		if (Cerrados.find(hijoSEMITurnL.st) == Cerrados.end())
		{
			hijoSEMITurnL.secuencia.push_back(actSEMITURN_L);
			Abiertos.push(hijoSEMITurnL);
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st))
		{
			if (Cerrados.find(hijoForward.st) == Cerrados.end())
			{
				hijoForward.secuencia.push_back(actFORWARD);
				Abiertos.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la Abiertos
		if (!Abiertos.empty())
		{
			current = Abiertos.top();
		}
	}

//	cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna)
	{
//		cout << "Cargando el plan\n";
		plan = current.secuencia;
                cout << "Plan: ";
		PintaPlan(plan);
		cout << " (longitud " << plan.size() << ")" << endl;
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

//---------------------- Implementación de la busqueda en anchura ---------------------------

// Implementación de la busqueda en profundidad.
// Entran los puntos origen y destino y devuelve la
// secuencia de acciones en plan, una lista de acciones.
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

//	cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna)
	{
//		cout << "Cargando el plan\n";
		plan = current.secuencia;
                cout << "Plan: ";
		PintaPlan(plan);
		cout << " (longitud " << plan.size() << ")" << endl;
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


int ComportamientoJugador::calcularCoste(estado & st, const Action & accion){
    int coste = 0;
    char casilla = mapaResultado[st.fila][st.columna];
    
    if(casilla == 'K'){
        st.item = Objetos::BIKINI;
    }
    if(casilla == 'D'){
        st.item = Objetos::ZAPATILLAS;
    }
    
    if(accion == actFORWARD){
        switch(casilla){
            case 'A':
                if(st.item == Objetos::BIKINI)
                    coste = 10;
                else
                    coste = 200;
                break;
            case 'B':
                if(st.item == Objetos::ZAPATILLAS)
                    coste = 15;
                else
                    coste = 100;
                break;
            case 'T':
                coste = 2;
                break;
            default:
                coste = 1;
        }
    }
    else if(accion == actTURN_L or accion == actTURN_R){
        switch(casilla){
            case 'A':
                if(st.item == Objetos::BIKINI)
                    coste = 5;
                else
                    coste = 500;
                break;
            case 'B':
                if(st.item == Objetos::ZAPATILLAS)
                    coste = 1;
                else
                    coste = 3;
                break;
            case 'T':
                coste = 2;
                break;
            default:
                coste = 1;
        }
    }
    else if(accion == actSEMITURN_L or accion == actSEMITURN_R){
        switch(casilla){
            case 'A':
                if(st.item == Objetos::BIKINI)
                    coste = 2;
                else
                    coste = 300;
                break;
            case 'B':
                if(st.item == Objetos::ZAPATILLAS)
                    coste = 1;
                else
                    coste = 2;
                break;
            case 'T':
                coste = 1;
                break;
            default:
                coste = 1;
        }
    }
    
    if(casilla == '?')
        coste = 10;
    
    return coste;
}

bool find(priority_queue<nodo> cola_pri, nodo aBuscar){
    bool encontrado = false;
    while(!cola_pri.empty() and !encontrado){
        if(cola_pri.top() == aBuscar)
            encontrado = true;
        cola_pri.pop();
    }
    return encontrado;
}

//---------------------- Implementación del costo uniforme ---------------------------

// Implementación de la busqueda en profundidad.
// Entran los puntos origen y destino y devuelve la
// secuencia de acciones en plan, una lista de acciones.
bool ComportamientoJugador::pathFinding_CostoUniforme(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	plan.clear();
	set<estado,ComparaEstados> explorados; // Lista de Cerrados
	map<estado, int, ComparaEstados> frontera;
	priority_queue<nodo> abiertos // Lista de Abiertos
	
	nodo current;
	current.st = origen;
	current.secuencia.empty();
	current.coste = 1;

	abiertos.push(current);
	frontera[current.st] = current.coste;

	while (bien_situado and !abiertos.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		abiertos.pop();
		explorados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+2) % 8;
		hijoTurnR.coste += calcularCoste(hijoTurnR.st, actTURN_R);
		if (explorados.find(hijoTurnR.st) == explorados.end())
		{
			if (frontera.find(hijoTurnR.st) == frontera.end())
			{
				hijoTurnR.secuencia.push_back(actTURN_R);
				abiertos.push(hijoTurnR);
				frontera[hijoTurnR.st] = hijoTurnR.coste;
			}
			else if (hijoTurnR.coste < frontera[hijoTurnR.st]) {
                                hijoTurnR.secuencia.push_back(actTURN_R);
                                abiertos.push(hijoTurnR);
                                frontera[hijoTurnR.st] = hijoTurnR.coste;
                        }
		}
                
		// Generar descendiente de girar a la derecha 45 grados
		nodo hijoSEMITurnR = current;
		hijoSEMITurnR.st.orientacion = (hijoSEMITurnR.st.orientacion + 1) % 8;
		hijoSEMITurnR.coste += calcularCoste(hijoSEMITurnR.st, actSEMITURN_R);
		if (explorados.find(hijoSEMITurnR.st) == explorados.end())
		{
			if (frontera.find(hijoSEMITurnR.st) == frontera.end())
			{
				hijoSEMITurnR.secuencia.push_back(actSEMITURN_R);
				abiertos.push(hijoSEMITurnR);
				frontera[hijoSEMITurnR.st] = hijoSEMITurnR.coste;
			}
			else if (hijoSEMITurnR.coste < frontera[hijoSEMITurnR.st])
                        {
                                hijoSEMITurnR.secuencia.push_back(actSEMITURN_R);
                                abiertos.push(hijoSEMITurnR);
                                frontera[hijoSEMITurnR.st] = hijoSEMITurnR.coste;
			}
		}

		// Generar descendiente de girar a la izquierda
		nodo hijoTurnL = current;
		hijoTurnL.coste += calcularCoste(hijoTurnL.st, actTURN_L);
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+6)%8;
		if (explorados.find(hijoTurnL.st) == explorados.end())
		{
			if (frontera.find(hijoTurnL.st) == frontera.end())
			{
				hijoTurnL.secuencia.push_back(actTURN_L);
				abiertos.push(hijoTurnL);
				frontera[hijoTurnL.st] = hijoTurnL.coste;
			}
			else if (hijoTurnL.coste < frontera[hijoTurnL.st])
			{
                                hijoTurnL.secuencia.push_back(actTURN_L);
                                abiertos.push(hijoTurnL);
                                frontera[hijoTurnL.st] = hijoTurnL.coste;
			}
		}
                
		// Generar descendiente de girar a la izquierda 45 grados
		nodo hijoSEMITurnL = current;
		hijoSEMITurnL.st.orientacion = (hijoSEMITurnL.st.orientacion + 7) % 8;
		hijoSEMITurnL.coste += calcularCoste(hijoSEMITurnL.st, actSEMITURN_L);;
		if (explorados.find(hijoSEMITurnL.st) == explorados.end())
		{
			if (frontera.find(hijoSEMITurnL.st) == frontera.end())
			{
				hijoSEMITurnL.secuencia.push_back(actSEMITURN_L);
				abiertos.push(hijoSEMITurnL);
				frontera[hijoSEMITurnL.st] = hijoSEMITurnL.coste;
			}
			else if (hijoSEMITurnL.coste < frontera[hijoSEMITurnL.st])
			{
                                hijoSEMITurnL.secuencia.push_back(actSEMITURN_L);
                                abiertos.push(hijoSEMITurnL);
                                frontera[hijoSEMITurnL.st] = hijoSEMITurnL.coste;
			}
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			hijoForward.coste += calcularCoste(hijoForward.st, actFORWARD);
			if (explorados.find(hijoForward.st) == explorados.end())
			{
				if (frontera.find(hijoForward.st) == frontera.end())
				{
					hijoForward.secuencia.push_back(actFORWARD);
					abiertos.push(hijoForward);
					frontera[hijoForward.st] = hijoForward.coste;
				}
				else if (hijoForward.coste < frontera[hijoForward.st])
				{
                                        hijoForward.secuencia.push_back(actFORWARD);
                                        abiertos.push(hijoForward);
                                        frontera[hijoForward.st] = hijoForward.coste;
				}
			}
		}

		// Tomo el siguiente valor de la abiertos
		if (!abiertos.empty()){
			current = abiertos.top();
		}
	}

//	cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
//		cout << "Cargando el plan\n";
		plan = current.secuencia;
                cout << "Plan: ";
		PintaPlan(plan);
		cout << " (longitud " << plan.size() << ")" << endl;
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}


	return false;
}

bool ComportamientoJugador::pathFindingNivel3(const estado &origen) {
	//Borro la lista
	cout << "Calculando objetivos\n";
	set<estado,ComparaEstados> explorados; // Lista de Cerrados
	map<estado, int, ComparaEstados> frontera;
	priority_queue<nodo> abiertos;											// Lista de Abiertos
	
	nodo current;
	current.st = origen;
	current.secuencia.empty();
	current.coste = 1;

	abiertos.push(current);
	frontera[current.st] = current.coste;

	while (!abiertos.empty() and (mapaResultado[current.st.fila][current.st.columna]!='?')){

		abiertos.pop();
		explorados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+2) % 8;
		hijoTurnR.coste += calcularCoste(hijoTurnR.st, actTURN_R);
		if (explorados.find(hijoTurnR.st) == explorados.end())
		{
			if (frontera.find(hijoTurnR.st) == frontera.end())
			{
				hijoTurnR.secuencia.push_back(actTURN_R);
				abiertos.push(hijoTurnR);
				frontera[hijoTurnR.st] = hijoTurnR.coste;
			}
			else if (hijoTurnR.coste < frontera[hijoTurnR.st]) {
                                hijoTurnR.secuencia.push_back(actTURN_R);
                                abiertos.push(hijoTurnR);
                                frontera[hijoTurnR.st] = hijoTurnR.coste;
                        }
		}
                
		// Generar descendiente de girar a la derecha 45 grados
		nodo hijoSEMITurnR = current;
		hijoSEMITurnR.st.orientacion = (hijoSEMITurnR.st.orientacion + 1) % 8;
		hijoSEMITurnR.coste += calcularCoste(hijoSEMITurnR.st, actSEMITURN_R);
		if (explorados.find(hijoSEMITurnR.st) == explorados.end())
		{
			if (frontera.find(hijoSEMITurnR.st) == frontera.end())
			{
				hijoSEMITurnR.secuencia.push_back(actSEMITURN_R);
				abiertos.push(hijoSEMITurnR);
				frontera[hijoSEMITurnR.st] = hijoSEMITurnR.coste;
			}
			else if (hijoSEMITurnR.coste < frontera[hijoSEMITurnR.st])
                        {
                                hijoSEMITurnR.secuencia.push_back(actSEMITURN_R);
                                abiertos.push(hijoSEMITurnR);
                                frontera[hijoSEMITurnR.st] = hijoSEMITurnR.coste;
			}
		}

		// Generar descendiente de girar a la izquierda
		nodo hijoTurnL = current;
		hijoTurnL.coste += calcularCoste(hijoTurnL.st, actTURN_L);
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+6)%8;
		if (explorados.find(hijoTurnL.st) == explorados.end())
		{
			if (frontera.find(hijoTurnL.st) == frontera.end())
			{
				hijoTurnL.secuencia.push_back(actTURN_L);
				abiertos.push(hijoTurnL);
				frontera[hijoTurnL.st] = hijoTurnL.coste;
			}
			else if (hijoTurnL.coste < frontera[hijoTurnL.st])
			{
                                hijoTurnL.secuencia.push_back(actTURN_L);
                                abiertos.push(hijoTurnL);
                                frontera[hijoTurnL.st] = hijoTurnL.coste;
			}
		}
                
		// Generar descendiente de girar a la izquierda 45 grados
		nodo hijoSEMITurnL = current;
		hijoSEMITurnL.st.orientacion = (hijoSEMITurnL.st.orientacion + 7) % 8;
		hijoSEMITurnL.coste += calcularCoste(hijoSEMITurnL.st, actSEMITURN_L);;
		if (explorados.find(hijoSEMITurnL.st) == explorados.end())
		{
			if (frontera.find(hijoSEMITurnL.st) == frontera.end())
			{
				hijoSEMITurnL.secuencia.push_back(actSEMITURN_L);
				abiertos.push(hijoSEMITurnL);
				frontera[hijoSEMITurnL.st] = hijoSEMITurnL.coste;
			}
			else if (hijoSEMITurnL.coste < frontera[hijoSEMITurnL.st])
			{
                                hijoSEMITurnL.secuencia.push_back(actSEMITURN_L);
                                abiertos.push(hijoSEMITurnL);
                                frontera[hijoSEMITurnL.st] = hijoSEMITurnL.coste;
			}
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			hijoForward.coste += calcularCoste(hijoForward.st, actFORWARD);
			if (explorados.find(hijoForward.st) == explorados.end())
			{
				if (frontera.find(hijoForward.st) == frontera.end())
				{
					hijoForward.secuencia.push_back(actFORWARD);
					abiertos.push(hijoForward);
					frontera[hijoForward.st] = hijoForward.coste;
				}
				else if (hijoForward.coste < frontera[hijoForward.st])
				{
                                        hijoForward.secuencia.push_back(actFORWARD);
                                        abiertos.push(hijoForward);
                                        frontera[hijoForward.st] = hijoForward.coste;
				}
			}
		}

		// Tomo el siguiente valor de la abiertos
		if (!abiertos.empty()){
			current = abiertos.top();
		}
	}

//	cout << "Terminada la busqueda\n";

	if (mapaResultado[current.st.fila][current.st.columna] == '?'){
		cout << "Cargando el objetivo\n";
                objetivos.push_back(current.st);
		// ver el plan en el mapa
		return true;
	}
	else {
		cout << "No encontrado objetivo\n";
	}


	return false;
}


// Sacar por la consola la secuencia del plan obtenido
void ComportamientoJugador::PintaPlan(list<Action> plan)
{
    int fil = actual.fila, col = actual.columna, ori = actual.orientacion;
       auto it = plan.begin();
	while (it != plan.end())
	{
		if (*it == actFORWARD)
		{
			cout << "A ";
                    	switch (ori)
                        {
                        case 0:
                                fil--;
                                break;
                        case 1:
                                fil--;
                                col++;
                                break;
                        case 2:
                                col++;
                                break;
                        case 3:
                                fil++;
                                col++;
                                break;
                        case 4:
                                fil++;
                                break;
                        case 5:
                                fil++;
                                col--;
                                break;
                        case 6:
                                col--;
                                break;
                        case 7:
                                fil--;
                                col--;
                                break;
                        }
		}
		else if (*it == actTURN_R)
		{
			cout << "D ";
                        ori = (ori + 2) % 8; 
		}
		else if (*it == actSEMITURN_R)
		{
			cout << "d ";
                        ori = (ori + 1) % 8; 
		}
		else if (*it == actTURN_L)
		{
			cout << "I ";
                        ori = (ori + 6) % 8; 
		}
		else if (*it == actSEMITURN_L)
		{
			cout << "i "; //pequeño error, era I
                        ori = (ori + 7) % 8; 
		}
		else
		{
			cout << "- ";
		}
		it++;
	}
}

// Funcion auxiliar para poner a 0 todas las casillas de una matriz
void AnularMatriz(vector<vector<unsigned char>> &m)
{
	for (int i = 0; i < m[0].size(); i++)
	{
		for (int j = 0; j < m.size(); j++)
		{
			m[i][j] = 0;
		}
	}
}

// Pinta sobre el mapa del juego el plan obtenido
void ComportamientoJugador::VisualizaPlan(const estado &st, const list<Action> &plan)
{
	AnularMatriz(mapaConPlan);
	estado cst = st;

	auto it = plan.begin();
	while (it != plan.end())
	{
		if (*it == actFORWARD)
		{
			switch (cst.orientacion)
			{
			case 0:
				cst.fila--;
				break;
			case 1:
				cst.fila--;
				cst.columna++;
				break;
			case 2:
				cst.columna++;
				break;
			case 3:
				cst.fila++;
				cst.columna++;
				break;
			case 4:
				cst.fila++;
				break;
			case 5:
				cst.fila++;
				cst.columna--;
				break;
			case 6:
				cst.columna--;
				break;
			case 7:
				cst.fila--;
				cst.columna--;
				break;
			}
			mapaConPlan[cst.fila][cst.columna] = 1;
		}
		else if (*it == actTURN_R)
		{
			cst.orientacion = (cst.orientacion + 2) % 8;
		}
		else if (*it == actSEMITURN_R)
		{
			cst.orientacion = (cst.orientacion + 1) % 8;
		}
		else if (*it == actTURN_L)
		{
			cst.orientacion = (cst.orientacion + 6) % 8;
		}
		else if (*it == actSEMITURN_L)
		{
			cst.orientacion = (cst.orientacion + 7) % 8;
		}
		it++;
	}
}

//---------------------------Metodos Reactivos----------------------------------

bool ComportamientoJugador::casillaDesconocida(int posF, int posC){
    if(mapaResultado[posF][posC] == '?')
        descubriendoMapa = true;

    return descubriendoMapa;
}

void ComportamientoJugador::guardaPos(char casilla, int posF, int posC){
    if( (puntoRecarga.fila == 0 and puntoRecarga.columna == 0) and casilla == 'X'){
        puntoRecarga.fila = posF;
        puntoRecarga.columna = posC;
    }
}



void ComportamientoJugador::vision(Sensores sensores){
    int contador = 0, saltos;
    descubriendoMapa = false;
    if(bien_situado){
        mapaResultado[actual.fila][actual.columna] = sensores.terreno[0];
        switch(actual.orientacion){
            case 0: //Norte
                saltos=1;
                for(int i = 1; i < sensores.terreno.size();){
                    for(int j = -1*saltos; j < saltos+1; j++){
                        guardaEntidad(sensores.superficie[i], actual.fila-saltos, actual.columna+j);
                        if(casillaDesconocida(actual.fila-saltos, actual.columna+j)){
                            guardaPos(sensores.terreno[i], actual.fila-saltos, actual.columna+j);
                            mapaResultado[actual.fila-saltos][actual.columna+j] = sensores.terreno[i++];
                        }
                        else
                            i++;
                    }
                    saltos++;
                }
                break;        
            case 1: //Noreste

                contador = 2, saltos = 0;
                for(int i = 1; i < sensores.terreno.size();){
                    for(int j = 0; j < contador*2; j++){
                        if(j < contador){
                            guardaEntidad(sensores.superficie[i], actual.fila-contador+1, actual.columna+j);
                            if(casillaDesconocida(actual.fila-contador+1, actual.columna+j)){
                                guardaPos(sensores.terreno[i], actual.fila-contador+1, actual.columna+j);
                                mapaResultado[actual.fila-contador+1][actual.columna+j] = sensores.terreno[i++];
                            }
                            else
                                i++;
                        }
                        else if(j < contador*2-1){
                            guardaEntidad(sensores.superficie[i], actual.fila-contador+j-saltos, actual.columna+contador-1);
                            if(casillaDesconocida(actual.fila-contador+j-saltos, actual.columna+contador-1)){
                                guardaPos(sensores.terreno[i], actual.fila-contador+j-saltos, actual.columna+contador-1);
                                mapaResultado[actual.fila-contador+j-saltos][actual.columna+contador-1] = sensores.terreno[i++];
                            }
                            else
                                i++;
                        }
                    }
                    contador++;
                    saltos++;
                }
                break;
            case 2: //Este
                saltos=1;
                for(int i = 1; i < sensores.terreno.size();){
                    for(int j = -1*saltos; j < saltos+1; j++){
                        guardaEntidad(sensores.superficie[i], actual.fila+j, actual.columna+saltos);
                        if(casillaDesconocida(actual.fila+j, actual.columna+saltos)){
                            guardaPos(sensores.terreno[i], actual.fila+j, actual.columna+saltos);
                            mapaResultado[actual.fila+j][actual.columna+saltos] = sensores.terreno[i++];
                        }
                        else
                            i++;
                    }
                    saltos++;
                }
                break;
            case 3: //Sureste
                contador = 2, saltos = 0;
                for(int i = 1; i < sensores.terreno.size();){
                    for(int j = 0; j < contador*2; j++){
                        if(j < contador){
                            guardaEntidad(sensores.superficie[i], actual.fila+j, actual.columna+contador-1);
                            if(casillaDesconocida(actual.fila+j, actual.columna+contador-1)){
                                guardaPos(sensores.terreno[i], actual.fila+j, actual.columna+contador-1);
                                mapaResultado[actual.fila+j][actual.columna+contador-1] = sensores.terreno[i++];
                            }
                            else
                                i++;
                        }
                        else if(j < contador*2-1){
                            guardaEntidad(sensores.superficie[i], actual.fila+contador-1, actual.columna+contador-j + saltos);
                            if(casillaDesconocida(actual.fila+contador-1, actual.columna+contador-j + saltos)){
                                guardaPos(sensores.terreno[i], actual.fila+contador-1, actual.columna+contador-j + saltos);
                                mapaResultado[actual.fila+contador-1][actual.columna+contador-j + saltos] = sensores.terreno[i++];
                            }
                            else
                                i++;
                        }
                    }
                    contador++;
                    saltos++;
                }
                break;
            case 4: //Sur
                saltos=1;
                for(int i = 1; i < sensores.terreno.size();){
                    for(int j = 1*saltos; j > -saltos-1; j--){
                        guardaEntidad(sensores.superficie[i], actual.fila+saltos, actual.columna+j);
                        if(casillaDesconocida(actual.fila+saltos, actual.columna+j)){
                            guardaPos(sensores.terreno[i], actual.fila+saltos, actual.columna+j);
                            mapaResultado[actual.fila+saltos][actual.columna+j] = sensores.terreno[i++];
                        }
                        else
                            i++;
                    }
                    saltos++;
                }
                break;
            case 5: //Suroeste
                contador = 2, saltos = 0;
                for(int i = 1; i < sensores.terreno.size();){
                    for(int j = 0; j < contador*2; j++){
                        if(j < contador){
                            guardaEntidad(sensores.superficie[i], actual.fila+contador-1, actual.columna-j);
                            if(casillaDesconocida(actual.fila+contador-1, actual.columna-j)){
                                guardaPos(sensores.terreno[i], actual.fila+contador-1, actual.columna-j);
                                mapaResultado[actual.fila+contador-1][actual.columna-j] = sensores.terreno[i++];
                            }
                            else
                                i++;
                        }
                        else if(j < contador*2-1){
                            guardaEntidad(sensores.superficie[i], actual.fila+contador-j + saltos, actual.columna-contador+1);
                            if(casillaDesconocida(actual.fila+contador-j + saltos, actual.columna-contador+1)){
                                guardaPos(sensores.terreno[i], actual.fila+contador-j + saltos, actual.columna-contador+1);
                                mapaResultado[actual.fila+contador-j + saltos][actual.columna-contador+1] = sensores.terreno[i++];
                            }
                            else
                                i++;
                        }
                    }
                    contador++;
                    saltos++;
                }
                break;
            case 6: //Oeste
                saltos=1;
                for(int i = 1; i < sensores.terreno.size();){
                    for(int j = 1*saltos; j > -saltos-1; j--){
                        guardaEntidad(sensores.superficie[i], actual.fila+j, actual.columna-saltos);
                        if(casillaDesconocida(actual.fila+j, actual.columna-saltos)){
                            guardaPos(sensores.terreno[i], actual.fila+j, actual.columna-saltos);
                            mapaResultado[actual.fila+j][actual.columna-saltos] = sensores.terreno[i++];
                        }
                        else
                            i++;
                    }
                    saltos++;
                }
                break;
            case 7: //Noroeste
                contador = 2, saltos = 0;
                for(int i = 1; i < sensores.terreno.size();){
                    for(int j = 0; j < contador*2; j++){
                        if(j < contador){
                            guardaEntidad(sensores.superficie[i], actual.fila-j, actual.columna-contador+1);
                            if(casillaDesconocida(actual.fila-j, actual.columna-contador+1)){
                                guardaPos(sensores.terreno[i], actual.fila-j, actual.columna-contador+1);
                                mapaResultado[actual.fila-j][actual.columna-contador+1] = sensores.terreno[i++];
                            }
                            else
                                i++;
                        }
                        else if(j < contador*2-1){
                            guardaEntidad(sensores.superficie[i], actual.fila-contador+1, actual.columna-contador+j - saltos);
                            if(casillaDesconocida(actual.fila-contador+1, actual.columna-contador+j - saltos)){
                                guardaPos(sensores.terreno[i], actual.fila-contador+1, actual.columna-contador+j - saltos);
                                mapaResultado[actual.fila-contador+1][actual.columna-contador+j - saltos] = sensores.terreno[i++];
                            }
                            else
                                i++;
                        }
                    }
                    contador++;
                    saltos++;
                }
                break;
        }
    }
}

void ComportamientoJugador::actualizaOrientacion(){
    switch(ultimaAccion){
        case actFORWARD:
            switch (actual.orientacion){
                case 0: actual.fila--; break; //Norte
                case 1: actual.fila--; actual.columna++; break; //Noreste
                case 2: actual.columna++; break; //Este
                case 3: actual.fila++; actual.columna++; break; //Sureste
                case 4: actual.fila++; break; //Sur
                case 5: actual.fila++; actual.columna--; break; //Suroeste
                case 6: actual.columna--; break; //Oeste
                case 7: actual.fila--; actual.columna--; break; //Noroeste
            }
            break;
        case actSEMITURN_R:
            actual.orientacion = (actual.orientacion + 1) % 8;
            break;
        case actTURN_R:
            actual.orientacion = (actual.orientacion + 2) % 8;
            break;
        case actTURN_L:
            actual.orientacion = (actual.orientacion + 6) % 8;
            break;
        case actSEMITURN_L:
            actual.orientacion = (actual.orientacion + 7) % 8;
            break;
    }
}

void ComportamientoJugador::checkSensores(Action & accion){
    if(sensorActual.vida == 3000-1 and sensorActual.nivel < 4){
        actual.fila = sensorActual.posF;
        actual.columna = sensorActual.posC;
        actual.orientacion = sensorActual.sentido;
        bien_situado = true;
    }

    if(ultimaAccion == actWHEREIS){
        actual.fila = sensorActual.posF;
        actual.columna = sensorActual.posC;
        actual.orientacion = sensorActual.sentido;
        bien_situado = true;
    }
    
    if(!bien_situado){
        accion = actWHEREIS;
    }
}

void ComportamientoJugador::checkObjects(){
        if(sensorActual.terreno[0] == 'K'){
            actual.item = Objetos::BIKINI;
        }
        if(sensorActual.terreno[0] == 'D'){
            actual.item = Objetos::ZAPATILLAS;
        }
}

void ComportamientoJugador::guardaEntidad(char entidad, int fil, int col){ //0 aldeano, 1 lobo
    estado aux;
    if(entidad == 'a'){
        aux.fila = fil;
        aux.columna = col;
        aldeanos.push_back(aux);
    }
    else if(entidad == 'l'){
        aux.fila = fil;
        aux.columna = col;
        lobos.push_back(aux);
    }
}

void ComportamientoJugador::checkReset(Action & accion){
    if(sensorActual.colision){
        actual.clear();
        plan.clear();
        objetivos.clear();
        hayPlan = bien_situado = false;
        accion = actWHEREIS;
    }
}

int ComportamientoJugador::interact(Action accion, int valor)
{
	return false;
}
