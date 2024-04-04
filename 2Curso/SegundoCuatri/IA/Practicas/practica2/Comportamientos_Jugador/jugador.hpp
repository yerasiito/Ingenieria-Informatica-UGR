#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
#include <string>
#include <list>

enum Objetos{NADA, ZAPATILLAS, BIKINI};

struct estado {
  int fila = 0;
  int columna = 0;
  int orientacion;
  Objetos item = Objetos::NADA;
  
    bool operator==(const estado &st) const{ //Compara si son el mismo nodo
        return (columna == st.columna and fila == st.fila and orientacion
                and item == st.item);
    }
    
    void clear(){
        fila = 0;
        columna = 0;
        orientacion = 0;
        item = Objetos::NADA;
    }
    
    bool empty(){
        return (fila == 0 and columna == 0);
    }
};

class nodo {
public:
    estado st;
    list<Action> secuencia;
    int coste = 0;    
    
    bool isEmpty(){
        return secuencia.empty();
    }
    
    bool operator<(const nodo &a) const{
        return a.coste < coste;
    }
    
    bool operator()(const nodo &a, const nodo &b) const
    {
        return a.coste > b.coste;
    }
    
    bool operator==(const nodo &a) const{ //Compara si son el mismo nodo
        return st == a.st and secuencia == a.secuencia;
    }
};

struct ComparaEstados
{
    bool operator()(const estado &a, const estado &n) const
    {
            if ((a.fila > n.fila) or (a.fila == n.fila and a.columna > n.columna) or
                    (a.fila == n.fila and a.columna == n.columna and a.orientacion > n.orientacion) or
                    ((a.fila == n.fila and a.columna == n.columna and a.orientacion == n.orientacion and a.item > n.item))){
                return true;
            }
            else{
                return false;
            }
    }
};

class ComportamientoJugador : public Comportamiento {
  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size) { //Para nivel 3 y 4
        pintaPrecipicios();
        actual.fila = actual.columna = 99;
        actual.orientacion = 0;
        hayPlan = descubriendoMapa = bien_situado = recargando = objetivoBateria = false;
        porDescubrir = true;
        ultimaAccion = actIDLE;
    }
    ComportamientoJugador(std::vector< std::vector< unsigned char> > mapaR) : Comportamiento(mapaR) { //Para nivel 0,1,2
      // Inicializar Variables de Estado
        actual.fila = actual.columna = 99;
        actual.orientacion = 0;
        hayPlan = descubriendoMapa = bien_situado = recargando = objetivoBateria = false;
        porDescubrir = true;
        ultimaAccion = actIDLE;
    }
    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    void VisualizaPlan(const estado &st, const list<Action> &plan);
    ComportamientoJugador * clone(){return new ComportamientoJugador(*this);}
    
    
    //Imprime en la terminal los datos que recibimos
    void informar();
    int calcularCoste(estado & st, const Action & accion);

  private:
    // Declarar Variables de Estado
    Action ultimaAccion;
    estado actual;
    Sensores sensorActual;
    list<estado> objetivos, aldeanos, lobos, zonaPeligro;
    list<Action> plan;
    bool hayPlan, bien_situado, descubriendoMapa, porDescubrir, recargando, objetivoBateria;
    estado puntoRecarga;
    
    //----------------Métodos Deliberativos de la clase-------------------------
    bool pathFinding(int level, const estado &origen, const list<estado> &destino, list<Action> &plan);
    bool pathFinding_Profundidad(const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_Anchura(const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_CostoUniforme(const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFindingNivel3(const estado &origen);
    bool pathFindingNivel4(const estado &origen, const estado &destino, list<Action> &plan);
    
    //void testeoLevel3();
    
    //---------------------Metodos Reactivos------------------------------------
 
    //Guarda la posicion de ciertas casillas
    void guardaPos(char casilla, int posF, int posC);
    
    //Guarda la posicion de la entidad
    void guardaEntidad(char entidad, int fil, int col); //0 aldeano, 1 lobo

    //Devuelve si el mapa en las posiciones dadas se desconoce
    bool casillaDesconocida(int posF, int posC);
    
    //Imprime en mapaResultado lo que ve
    void vision(Sensores sensores);

    //Actualiza la brujula en cada iteración
    void actualizaOrientacion();
    
    //Comprueba si funcionan los sensores(niveles)
    void checkSensores(Action & accion);
    
    //Evalua los objetos que tiene
    void checkObjects();

    //Evalua los objetos que tiene
    void checkObjetivo(list<estado> & objetivos, const estado & actual);    

    void checkReset(Action & accion);
    
    void buscarEnMatriz();
    
    void checkBateria();
    void vaAPorBateria();
    
    void PintaPlan(list<Action> plan);
    bool HayObstaculoDelante(estado &st);
    bool EsObstaculo(unsigned char casilla);
    
    void capturaDestinos();
    
    //Comprueba que el nodo no se encuentra en una casilla con potencial peligro
    bool EsPeligro(int fil, int col);
    
    //Establece unas casillas de peligro por aldeanos o lobos
    void setZonaPeligro();
    
    //Genera las matrices de peligro
    void MatrizPeligro(int fil, int col, bool entidad); //0 aldeano, 1 lobo
    
    
    //Otras Funciones
    
    void pintaPrecipicios(){
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
    }
};

#endif
