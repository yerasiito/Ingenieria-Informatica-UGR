#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
#include <queue>
using namespace std;

class ComportamientoJugador : public Comportamiento{

  public:

    //Imprime en la terminal los datos que recibimos
    void informar();

    //Comprueba si está en una casilla "especial"
    bool enCasillaEspecial();

    //Devuelve si el mapa en las posiciones dadas se desconoce
    bool casillaDesconocida(int posF, int posC);

    //Auxiliar de vision
    void reconocimiento(int sentido, bool lateral);

    //Imprime en mapaResultado lo que ve
    void vision();

    //Actualiza la brujula en cada iteración
    void actualizaBrujula();

    //Se mueve X casillas hacia adelante
    void goForward(int num = 1);

    //Se desplaza num casillas a la izquierda manteniendo orientacion
    void desplazaIzquierda();

    //Se desplaza num casillas a la derecha manteniendo orientacion
    void desplazaDerecha();

    //Da media vuelta
    void mediaVuelta();

    bool encuentraCasilla(char casillaABuscar, int & pos);

    //Explora el mapa de forma aleatoria
    void explorar();

    //Busca casillas de interés y devuelve su distancia en columnas
    void CasillaInteres();

    //Va a por la casilla indicada
    bool veAPorCasilla(char casilla, bool camino=0);

    //Va a la posicion de la vision indicada
    void veAPos(int pos, bool camino=0);

    //Toma las decisiones para ir a una casilla dentro de su vision
    void decide(int pos, bool camino = 0); //camino = 0 -> avanza y luego desplaza, viceversa para 1

    //Toma las decisiones para ir a una casilla del mapa
    void decideMatriz(int filCasilla, int colCasilla, bool camino = 0);

    void orientarseACasilla(int filCasilla, int colCasilla);

    //Comprueba si una casilla está en el vector casillaDescubierta
    bool esPosDescubierta(char casilla);

    //Evalúa si ha sido reiniciado
    void checkReset();

    //Evalua los objetos que tiene
    void checkObjects();

    //Comprueba si funcionan los sensores(niveles)
    void checkSensores();

    //Comprueba si puede ir hacia delante(o si le interesa)
    bool transitable();

    bool impenetrable(char casilla);

    //Comprueba si puede pasar por una casilla dada
    bool casillaTransitable(char casilla);

    //Comprueba si está rodeado de agua o bosque sin su objeto
    bool encerrado();

    //Recuerda lo que tiene a sus lados y atras
    void memoriaVision(Action accion);

    //Desaburrirse
    void dejaDeAburrirse(const Action & accion);

    //va a por una casilla del mapa
    void casillaEnMatriz(int filCasilla, int colCasilla);

    //Guarda la posicion de ciertas casillas
    void guardaPos(char casilla, int posF, int posC);

    //Busca los huecos de los muros y va hacia ellos
    void findEntrada();

    //Imprime el contenido de la cola
    void imprimeContenedor();

    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      // Constructor de la clase
      fil = col = 99;
      brujula = 0;
      ultimaAccion = actIDLE;
      girar_derecha = bien_situado = descubriendoMapa = zapatillas = bikini = interes = false;
      aburrimiento = dist = distLateral = wait = 0;

      //Inicializa la matriz con los precipicios
      for(int i = 0; i < 3; i++){
          for(int j = 0; j < mapaResultado[0].size(); j++){
              mapaResultado[i][j] = 'P';
              mapaResultado[j][i] = 'P';
          }
      }

      for(int i = mapaResultado[0].size()-1; i > (mapaResultado[0].size()-4); i--){
          for(int j = 0; j < mapaResultado[0].size(); j++){
              mapaResultado[i][j] = 'P';
              mapaResultado[j][i] = 'P';
          }
      }
      // Dar el valor inicial a las variables de estado
    }

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);

  private:

  // Declarar aquí las variables de estado
    Sensores sensorActual;
    pair<int, int> puntoRecarga = {};
    int fil, col, brujula, aburrimiento, dist, distLateral, umbralAburrimiento, wait;
    Action ultimaAccion;
    bool girar_derecha, bien_situado, descubriendoMapa, zapatillas, bikini, interes;
    queue<Action> ejecutor {};
    vector <int> izquierda = {1,4,5,9,10,11},
                 derecha = {3,7,8,13,14,15},
                 frente = {2,6,12},
                 posDescubiertas{},
                 distanciaLateral = {0,1,0,1,2,1,0,1,2,3,2,1,0,1,2,3},
                 distancia = {0,1,1,1,2,2,2,2,2,3,3,3,3,3,3,3};
    vector <char> lateral = {'?','?'}, //laterales[0] es izquierda y el otro derecha
                  atras = {'?', '?', '?'}; // 0 es terreno[-1], 1 es la casilla de atrás y 2 es terreno[-3]
};

#endif
