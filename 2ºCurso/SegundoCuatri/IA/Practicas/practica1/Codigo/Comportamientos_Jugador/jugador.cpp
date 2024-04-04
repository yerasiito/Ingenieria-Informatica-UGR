#include "../Comportamientos_Jugador/jugador.hpp"
#include "aldeano.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

//Funcion aux
void clearEjecutor(queue<Action> & toEmpty){
    queue<Action> empty;
    swap(toEmpty, empty);
}

//Funciones de la clase
void ComportamientoJugador::informar(){
    cout << endl << "Posicion: fila " << sensorActual.posF << " columna " << sensorActual.posC << " ";
    switch(sensorActual.sentido){
            case 0: cout << "Norte" << endl; break;
            case 1: cout << "Este" << endl; break;
            case 2: cout << "Sur " << endl; break;
            case 3: cout << "Oeste" << endl; break;
    }
    cout << "Terreno: ";
    cout << lateral[0]  << atras[0] << atras[1] << atras[2] << lateral[1] << " | ";
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

bool ComportamientoJugador::enCasillaEspecial(){
    return(sensorActual.terreno[0] == 'K'
            or sensorActual.terreno[0] == 'D'
            or sensorActual.terreno[0] == 'X'
            or sensorActual.terreno[0] == 'G');
}

bool ComportamientoJugador::casillaDesconocida(int posF, int posC){
    if(mapaResultado[posF][posC] == '?')
        descubriendoMapa = true;

    return descubriendoMapa;
}

//El factor siempre es opuesto al valor de i
void ComportamientoJugador::reconocimiento(int sentido, bool lateral){
    descubriendoMapa = false;
    posDescubiertas.clear();

    int i = 0, contador = 0;
    while(contador < 16){
        for(int j = i; abs(j) <= abs(i); j-=sentido){
            if(!lateral && casillaDesconocida(fil+i,col+j)){
                mapaResultado[fil+i][col+j] = sensorActual.terreno[contador]; //recorre columnas
                guardaPos(sensorActual.terreno[contador], fil+i, col+j);
                posDescubiertas.push_back(contador);
            }
            else if(lateral && casillaDesconocida(fil-j,col+i)){
                mapaResultado[fil-j][col+i] = sensorActual.terreno[contador]; //recorre filas
                guardaPos(sensorActual.terreno[contador], fil-j, col+i);
                posDescubiertas.push_back(contador);
            }

            contador++;
        }
        i+=sentido; //-1 o +1
    }
}

void ComportamientoJugador::vision(){
    if(bien_situado){
        switch(brujula){
            case 0: //Norte
                reconocimiento(-1, false);
                break;
            case 1: //Este
                reconocimiento(+1, true);
                break;
            case 2: //Sur
                reconocimiento(+1, false);
                break;
            case 3: //Oeste
                reconocimiento(-1, true);
                break;
        }
    }
}

void ComportamientoJugador::actualizaBrujula(){
    switch(ultimaAccion){
        case actFORWARD:
            switch (brujula){
                case 0: fil --; break;
                case 1: col ++; break;
                case 2: fil ++; break;
                case 3: col --; break;
            }
            break;
        case actTURN_L:
            brujula = (brujula+3)%4;
            break;
        case actTURN_R:
            brujula = (brujula+1)%4;
            break;
    }
}

bool ComportamientoJugador::encuentraCasilla(char casillaABuscar, int & pos){
    int posAux = -1;
    bool encontrada = false, frontal = false, sinDescubrir = false;

    for(int i = 1; i < sensorActual.terreno.size() && ((!frontal && i < 13) || !sinDescubrir); i++){
        if(sensorActual.terreno[i] == casillaABuscar){
            if(find(frente.begin(), frente.end(), i) != frente.end()) //Preferencia por las casillas frontales
                frontal = true;
            else if(find(posDescubiertas.begin(), posDescubiertas.end(), i) != posDescubiertas.end()){ //Preferencia recien descubierta
                sinDescubrir = true;
                posAux = i;
            }
            pos = i;
            encontrada = true;
        }

    }

    if(sinDescubrir and !frontal)
        pos = posAux;

    if(encontrada){
        distLateral = distanciaLateral[pos];
        dist = distancia[pos];
    }

    return encontrada;
}

void ComportamientoJugador::veAPos(int pos, bool camino){
    distLateral = distanciaLateral[pos];
    dist = distancia[pos];
    decide(pos, camino);
}

void ComportamientoJugador::goForward(int num){
    for(int i = 0; i < num; i++){
        if(!impenetrable(sensorActual.terreno[2])){
            if(interes or transitable())
                ejecutor.push(actFORWARD);
        }
        else
            explorar();
    }
}

void ComportamientoJugador::desplazaIzquierda(){
    ejecutor.push(actTURN_L);
    goForward(distLateral);
    ejecutor.push(actTURN_R);
}

void ComportamientoJugador::desplazaDerecha(){

    ejecutor.push(actTURN_R);
    goForward(distLateral);
    ejecutor.push(actTURN_L);
}

void ComportamientoJugador::mediaVuelta(){
    static Action giro = actTURN_L;

    ejecutor.push(giro);
    ejecutor.push(giro);

    //cambia el giro cada vez que se ejecuta
    if(giro == actTURN_L)
        giro = actTURN_R;
    else
        giro = actTURN_L;
}

void ComportamientoJugador::decide(int pos, bool camino){

    if(find(derecha.begin(), derecha.end(), pos) != derecha.end()){
        if(camino)
            goForward(dist);
        desplazaDerecha();
    }
    else if(find(izquierda.begin(), izquierda.end(), pos) != izquierda.end()){
        if(camino)
            goForward(dist);
        desplazaIzquierda();
    }
    else
        goForward(dist);
}

void ComportamientoJugador::decideMatriz(int filCasilla, int colCasilla, bool camino){
    //Se orienta hacia la casillanano
    orientarseACasilla(filCasilla, colCasilla);

    //Desplazarse hacia la casilla
    if(camino)
        goForward(dist);

    if(col < colCasilla)
        desplazaDerecha();
    else if(col > colCasilla)
        desplazaIzquierda();

    if(!camino)
        goForward();

//    if(fil < filCasilla){
//        if(col < colCasilla)
//            desplazaIzquierda();
//        else if(col > colCasilla)
//            desplazaDerecha();
//        else
//            goForward(dist);
//    }
//    else if(fil > filCasilla){
//        if(col < colCasilla)
//            desplazaDerecha();
//        else if(col > colCasilla)
//            desplazaIzquierda();
//        else
//            goForward(dist);
//    }
//    else
//        goForward(distLateral);
}

void ComportamientoJugador::orientarseACasilla(int filCasilla, int colCasilla){
    //corregimos la orientacion para tenerla delante

    switch(brujula){
        case 0:
            if(fil < filCasilla){
                mediaVuelta();
            }
            else if(fil == filCasilla and col != colCasilla){
                if(col < colCasilla){
                    ejecutor.push(actTURN_R);
                }
                else
                    ejecutor.push(actTURN_L);
            }
            break;
        case 1:
            if(fil < filCasilla){
                ejecutor.push(actTURN_R);
            }
            else if(fil > filCasilla){
                ejecutor.push(actTURN_L);
            }
            else if(fil == filCasilla and col != colCasilla){
                if(col > colCasilla){
                    mediaVuelta();
                }
            }
            break;
        case 2:
            if(fil > filCasilla){
                mediaVuelta();
            }
            else if(fil == filCasilla and col != colCasilla){
                if(col < colCasilla){
                    ejecutor.push(actTURN_L);
                }
                else
                    ejecutor.push(actTURN_R);
            }
            break;
        case 3:
            if(fil < filCasilla){
                ejecutor.push(actTURN_L);
            }
            else if(fil > filCasilla){
                ejecutor.push(actTURN_R);
            }
            else if(fil == filCasilla and col != colCasilla){
                if(col < colCasilla){
                    mediaVuelta();
                }
            }
            break;
    }

}

bool ComportamientoJugador::veAPorCasilla(char casilla, bool camino){
    bool encontrada = false;
    int pos = -1;
    if(encuentraCasilla(casilla, pos)){
        encontrada = true;
        cout << "POSICION" << pos << endl;
        decide(pos, camino);
    }
    return encontrada;
}

void ComportamientoJugador::explorar(){
    cout << "Modo Exploracion" << endl;

    //Vacía la cola entera
    clearEjecutor(ejecutor);

    if(!impenetrable(sensorActual.terreno[2]) and transitable() and aburrimiento < umbralAburrimiento){
        ejecutor.push(actFORWARD);
        if(!descubriendoMapa)
            aburrimiento++;
    }
    else{
        if(casillaTransitable(lateral[0]) and casillaTransitable(lateral[1]) ){
            if(!girar_derecha){
                ejecutor.push(actTURN_L);
                girar_derecha = (rand()%2 == 0);
            }
            else{
                ejecutor.push(actTURN_R);
                girar_derecha = (rand()%2 == 0);

            }
        }
        else{
            if(casillaTransitable(lateral[0])){
                ejecutor.push(actTURN_L);
            }
            else{
                ejecutor.push(actTURN_R);
            }
        }
    }
}

void ComportamientoJugador::CasillaInteres(){
    interes = false;
    int pos = 0;

    if( (encuentraCasilla('X',pos) and wait <= 0)
        or (!bikini and encuentraCasilla('K', pos))
        or (!zapatillas and encuentraCasilla('D', pos))
        or (!bien_situado and encuentraCasilla('G', pos)) )
            interes = true;

    if(interes){
        decide(pos);
        dist = distancia[pos];
        distLateral = distanciaLateral[pos];
    }
}

void ComportamientoJugador::checkReset(){
    if(sensorActual.reset){
        brujula = 0;
        bien_situado = false;
        bikini = false;
        zapatillas = false;
    }
}

void ComportamientoJugador::checkObjects(){
        if(sensorActual.terreno[0] == 'K'){
            bikini = true;
        }
        if(sensorActual.terreno[0] == 'D'){
            zapatillas = true;
        }
}

void ComportamientoJugador::checkSensores(){
    if(sensorActual.nivel < 2 and !bien_situado){
        brujula = sensorActual.sentido;
    }

    if( (sensorActual.posC != -1 and sensorActual.posF != -1) or (sensorActual.terreno[0] == 'G' and !bien_situado ) ){
        fil = sensorActual.posF;
        col = sensorActual.posC;
        bien_situado = true;
    }

}

bool ComportamientoJugador::impenetrable(char casilla){
    return (casilla == 'M'
            or casilla == 'P');
}

bool ComportamientoJugador::transitable(){
    return (casillaTransitable(sensorActual.terreno[2]) and sensorActual.superficie[2] == '_');
}

bool ComportamientoJugador::casillaTransitable(char casilla){
    return (!impenetrable(casilla) and (umbralAburrimiento > 10 or (casilla == 'B' && zapatillas)
            or (casilla == 'A' && bikini && descubriendoMapa)
            or casilla == 'S' or casilla == 'T' or casilla == 'K'
            or casilla == 'D' or casilla == 'X' or casilla == 'G'
            or casilla == '?') );
}

void ComportamientoJugador::dejaDeAburrirse(const Action & accion){
    if(enCasillaEspecial() or descubriendoMapa){
        aburrimiento = 0;
        umbralAburrimiento = 3;
    }
    else if(accion != actFORWARD){
        aburrimiento = 0;
        umbralAburrimiento++;
    }

}

void ComportamientoJugador::memoriaVision(Action accion){
    //Recuerda las tres casillas de atrás
    if(accion == actFORWARD){
        atras[0] = lateral[0];
        atras[1] = sensorActual.terreno[0];
        atras[2] = lateral[1];
    }
    else if(accion == actTURN_L){
        atras[0] = atras[2];
        atras[1] = lateral[1];
        atras[2] = sensorActual.terreno[3];
    }
    else{
        atras[2] = atras[0];
        atras[1] = lateral[0];
        atras[0] = sensorActual.terreno[1];
    }

    //Recuerda lo que tiene a sus lados
    if(accion == actFORWARD){
        lateral[0] = sensorActual.terreno[1]; //izquierda
        lateral[1] = sensorActual.terreno[3]; //derecha
    }
    else if(accion == actTURN_L){
        lateral[0] = atras[1];
        lateral[1] = sensorActual.terreno[2];
    }
    else{
        lateral[0] = sensorActual.terreno[2];
        lateral[1] = atras[1];
    }
}

bool ComportamientoJugador::esPosDescubierta(char casilla){
    bool descubierta = false;
    for(int i = 0; i < posDescubiertas.size() and !descubierta; i++){
        if(sensorActual.terreno[posDescubiertas[i]] == casilla)
            descubierta = true;
    }
    cout << endl;
    return descubierta;
}

void ComportamientoJugador::imprimeContenedor(){
        cout << "El contenedor tiene: ";
        queue<Action> aux = ejecutor;
        while(!aux.empty()){
            cout << aux.front() << " ";
            aux.pop();
        }
        cout << "/" << endl;
}

void ComportamientoJugador::casillaEnMatriz(int filCasilla, int colCasilla){
    clearEjecutor(ejecutor);
    distLateral = abs(col - colCasilla);
    dist = abs(fil - filCasilla);
    decideMatriz(filCasilla, colCasilla); //Presupone que la tiene delante
}

void ComportamientoJugador::guardaPos(char casilla, int posF, int posC){
    if( (puntoRecarga.first == 0 and puntoRecarga.second == 0) and casilla == 'X'){
        puntoRecarga = make_pair(posF,posC);
        cout << "La batería está en " << puntoRecarga.first << " " << puntoRecarga.second << endl;
    }
}

void ComportamientoJugador::findEntrada(){
    bool encontrada = false;
    for(int i = 1; i < 16 and !encontrada; i++){
        if(i == 2 or i == 7 or i == 14) //Se salta las 2 ultimas
            i+=2;
        if(impenetrable(sensorActual.terreno[i])
                and !impenetrable(sensorActual.terreno[i+1])
                and impenetrable(sensorActual.terreno[i+2]) ){
            encontrada = true;
            veAPos(i+1);
        }
    }

    if(!encontrada){
        if(impenetrable(lateral[0]) and !impenetrable(sensorActual.terreno[1]) and impenetrable(sensorActual.terreno[5])){
            encontrada = true;
            veAPos(1);
        }
        else if(impenetrable(lateral[0]) and !impenetrable(sensorActual.terreno[1]) and impenetrable(sensorActual.terreno[5])){
            encontrada = true;
            veAPos(3);
        }
        else if(impenetrable(sensorActual.terreno[1])
                and !impenetrable(sensorActual.terreno[5])
                and impenetrable(sensorActual.terreno[11])){
            encontrada = true;
            veAPos(5,1);
        }
        else if(impenetrable(sensorActual.terreno[3])
                and !impenetrable(sensorActual.terreno[7])
                and impenetrable(sensorActual.terreno[13])){
            encontrada = true;
            veAPos(7,1);
            }
    }

    if(encontrada){
        ejecutor.push(actFORWARD);
    }

}

bool ComportamientoJugador::encerrado(){
    bool encerrado = false;
    if( (!casillaTransitable(sensorActual.terreno[2]) or impenetrable(sensorActual.terreno[2]))
        and ( !casillaTransitable(lateral[0]) or impenetrable(lateral[0]) )
        and ( !casillaTransitable(atras[1]) or impenetrable(atras[1]) )
        and (!casillaTransitable(lateral[1]) or impenetrable(lateral[1])) ){
        encerrado = true;
        interes = true;
   }
    wait = 5;
    return encerrado;
}

Action ComportamientoJugador::think(Sensores sensores){

//#ARREGLAR EL BUG DE CUANDO SE ENCIERRA EN TERRENO INTRANSITABLE
//#BUSCAR CAMINOS EN DIAGONAL

	Action accion = actIDLE;
        sensorActual = sensores;

        //Actualiza la brujula en funcion de la acción anterior
        actualizaBrujula();

        //Comprueba si ha sido reiniciado
        checkReset();

        //Visiona el mapa
        vision();

        //Si funcionan los sensores o está en la casilla pos
        checkSensores();

        //Comprueba si está en una casilla especial
        if(enCasillaEspecial()){
            interes = false;
            checkObjects();
        }

	//Decidir la nueva accion

//        cout << "Antes de entrar el if decision" << endl;
//        imprimeContenedor();

//        static bool test = false;

        if(sensores.colision){
            interes = false;
            wait = 5;
            clearEjecutor(ejecutor);
        }

        cout << "WAIT " << wait << endl;

        if(ejecutor.empty()){
            findEntrada(); //Permite ir a por los huecos


//            if(sensores.bateria < 5000 and !test){
//                if(wait <= 0){
//                    clearEjecutor(ejecutor);
//                    casillaEnMatriz(25,17);
//                    test = true;
//                }
//                else
//                    wait--;
//            }

            if(puntoRecarga.first != 0 and puntoRecarga.second != 0 and sensores.bateria < 1000
                    and sensores.vida > 500 and ejecutor.empty() and wait <= 0){
                interes = true;
                casillaEnMatriz(puntoRecarga.first, puntoRecarga.second);
            }
            
            if(sensores.terreno[0] == 'X' and sensores.bateria < 4000 and sensores.vida > 500){
                clearEjecutor(ejecutor);
                ejecutor.push(actIDLE);
            }
            
            if(ejecutor.empty() and wait <= 0){
                CasillaInteres();
            }

            if(ejecutor.empty())
                explorar();
        }

        //EN CASO DE FORWARD, COMPROBAR QUE SE PUEDE PASAR
        if(ejecutor.front() == actFORWARD){
            if(impenetrable(sensores.terreno[2]) or (!interes and !transitable()) ){
                interes = false;
                explorar(); //Borra la cola y explora de nuevo
                wait = 7; //Espera 5 iteraciones hasta volver a interesarse
            }
        }

        cout << "Antes de entrar el if ejecutor" << endl;
        imprimeContenedor();


        //EJECUTOR
        if(!ejecutor.empty()){
            accion = ejecutor.front();
            ejecutor.pop();
        }

        //Actualiza la variable aburrimiento
        dejaDeAburrirse(accion);

	// Recordar la última acción
	ultimaAccion = accion;

        //Recordar la vision trasera
        memoriaVision(accion);

        //Imprime datos en la terminal
        informar();

        cout << "Accion final " << accion << endl;
        cout << "----------------------------------------" << endl;

        if(wait > 0)
            wait--;

        return accion;
}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}
