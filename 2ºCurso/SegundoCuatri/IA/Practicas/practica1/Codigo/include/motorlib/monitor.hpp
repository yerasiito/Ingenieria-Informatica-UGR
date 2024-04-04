#ifndef MONITOR_H
#define MONITOR_H

#include "motorlib/entidad.hpp"
#include "motorlib/mapa.hpp"
#include "motorlib/util.h"
#include <glui/glui.h>

// Clase para monitorizar y controlar la ejecucion de todo el juego
// Es necesaria si se quiere independizar el dibujado de los modelo del comportamiento de los agentes.

class MonitorJuego
{
private:
  int semilla;
  vector<Entidad *> entidades;
  int naldeanos = -1;
  int nlobos = -1;
  Mapa *mapa;

  bool apagarBelkan = false; // Notificar al motor de juego que sigua corriendo
  bool jugando = false;      // Notificar al motor de juego que haga los thinks
  bool empezarJuego = false; // Notificar al motor de juego que inicie un nuevo juego

  bool resultados = false;

  int pasos = 0;
  int pasosTotales = 0;
  int maxPasos = 3000;

  int retardo = 5;

  int nivel = 1;
  string currentMap = "Nothing";

public:
  MonitorJuego(int x = 3000) { maxPasos = x; }
  ~MonitorJuego() {}

  void nueva_entidad(Entidad *entidad) { entidades.push_back(entidad); }
  unsigned int numero_entidades() { return entidades.size(); }

  void clear() { entidades.clear(); }
  Entidad *get_entidad(unsigned entidad) { return entidades[entidad]; }
  vector<Entidad *> *get_entidades() { return &entidades; }
  void cambiarPosicion(unsigned char entidad, unsigned char x, unsigned char y) { entidades[entidad]->setPosicion(x, y); }
  void cambiarOrientacion(unsigned char entidad, unsigned char orientacion);

  Mapa *getMapa() { return mapa; }
  void setMapa(const char *file);

  void startGame(int valor = 1)
  { // Indica que hay un nuevo juego que inicializar
    empezarJuego = true;
    pasosTotales = 0;
    pasos = 0;
    nivel = valor;
  }
  bool inicializarJuego(); // Mira si tiene que inicializar un juego
  int juegoInicializado()
  {
    jugando = true;
    return mapa->getNFils();
  }

  bool continuarBelkan() { return !apagarBelkan; }
  void cerrarBelkan() { apagarBelkan = true; }

  bool mostrarResultados() { return resultados; }
  void setMostrarResultados(bool valor) { resultados = valor; }

  bool jugar() { return jugando; }

  void girarJugadorIzquierda() { mapa->girarCamaraIzquierda(); }
  void girarJugadorDerecha() { mapa->girarCamaraDerecha(); }

  void setPasos(int Npasos) { pasos = Npasos; }
  void decPasos();
  int getPasos() { return pasos; }

  bool finJuego() { return ((maxPasos - pasosTotales) <= 0); }
  void finalizarJuego() { pasosTotales = maxPasos; }

  void setRetardo(int tRetardo) { retardo = tRetardo; }
  int getRetardo() { return retardo; }

  int getLevel() { return nivel; }

  void generate_a_valid_cell(int &pos_fila, int &pos_col, int &ori);
  bool is_a_valid_cell_like_goal(int f, int c);

  void inicializar(int fila = -1, int columna = -1, int orienta = -1, int seed = 1);
  int get_semilla() const { return semilla; }
  void set_semilla(int seed) { semilla = seed; }

  int get_n_aldeanos() const { return naldeanos; }
  void set_n_aldeanos(int valor) { naldeanos = valor; }

  int get_n_lobos() const { return nlobos; }
  void set_n_lobos(int valor) { nlobos = valor; }

  string get_currentMap() { return currentMap; }
  void set_currentMap(const string &map) { currentMap = map; }

  double CoincidenciaConElMapa();
  void PintaEstadoMonitor();

  void init_casillas_especiales(unsigned int f, unsigned int c); 
};
#endif
