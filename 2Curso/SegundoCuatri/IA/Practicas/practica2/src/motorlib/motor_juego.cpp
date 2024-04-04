#include "motorlib.hpp"

#include <unistd.h>

extern MonitorJuego monitor;

bool actuacionJugador(unsigned char celda_inicial, unsigned char celda_fin, Action accion, unsigned int x, unsigned int y)
{
  unsigned int mix, miy;
  unsigned char celdaRand;
  bool salida = false;

  int gasto = monitor.get_entidad(0)->fixBateria_sig_accion(celda_inicial, accion);
  if (gasto > monitor.get_entidad(0)->getBateria())
  {
    monitor.get_entidad(0)->setBateria(0);
    return false;
  }

  //monitor.get_entidad(0)->fixBateria_default();
  switch (accion)
  {
  case actFORWARD:
    if (monitor.getMapa()->casillaOcupada(0) == -1)
    {
      switch (celda_fin)
      {         // Casilla destino desocupada
      case 'M': // Muro
        monitor.get_entidad(0)->seAostio();
        break;
        break;
      case 'P': // Precipicio
        cout << "Se cayo por un precipicio\n";
        monitor.get_entidad(0)->resetEntidad();
        monitor.get_entidad(0)->setHitbox(true);
        monitor.finalizarJuego();
        monitor.setMostrarResultados(true);

        break;
      case 'X': // Casilla Rosa (Recarga)
        //monitor.get_entidad(0)->increaseBateria(10);
        monitor.get_entidad(0)->setPosicion(x, y);
        salida = true;
        break;
      case 'D': // Casilla Morada (Zapatillas)
        // tomo la zapatilla
        monitor.get_entidad(0)->Cogio_Zapatillas(true);
        // pierdo el bikini
        monitor.get_entidad(0)->Cogio_Bikini(false);
        monitor.get_entidad(0)->setPosicion(x, y);
        salida = true;
        break;
      case 'K': // Casilla Amarilla (Bikini)
        // tomo el bikini
        monitor.get_entidad(0)->Cogio_Bikini(true);
        // pierdo las zapatillas
        monitor.get_entidad(0)->Cogio_Zapatillas(false);
        monitor.get_entidad(0)->setPosicion(x, y);
        salida = true;
        break;
      case 'G': // Casilla celeste claro (GPS)
        monitor.get_entidad(0)->notify();
        monitor.get_entidad(0)->setPosicion(x, y);
        salida = true;
        break;

      case 'B': // Arbol
      case 'A': // Agua
      default:
        monitor.get_entidad(0)->setPosicion(x, y);
        salida = true;
        break;
      }
      if (monitor.get_entidad(0)->isMemberObjetivo(x, y) != -1 and monitor.get_entidad(0)->allLessOneObjetivosAlcanzados())
      {
        // acaba de completar todos los objetivos.
        monitor.get_entidad(0)->setCompletoLosObjetivos();
        if (monitor.getLevel() == 4)
        {
          monitor.put_active_objetivos(3);
          monitor.get_entidad(0)->anularAlcanzados();
          monitor.get_entidad(0)->setObjetivos(monitor.get_active_objetivos());
        }
      }
      //monitor.get_entidad(0)->fixBateria_sig_accion(celda_inicial, accion);
    }
    else
    {
      // Choca contra una entidad
      monitor.get_entidad(0)->seAostio();
      if (monitor.get_entidad(monitor.getMapa()->casillaOcupada(0))->getSubTipo() == aldeano)
      {
        monitor.get_entidad(0)->perderPV(1);
      }
      else if (monitor.get_entidad(monitor.getMapa()->casillaOcupada(0))->getSubTipo() == lobo)
      {
        // Opcion reiniciarse en otro punto del mapa
        /*do
        {
          mix = aleatorio(monitor.getMapa()->getNFils() - 1);
          miy = aleatorio(monitor.getMapa()->getNCols() - 1);

          celdaRand = monitor.getMapa()->getCelda(mix, miy);
        } while (celdaRand == 'P' or celdaRand == 'M' or monitor.getMapa()->entidadEnCelda(mix, miy) != '_');

        monitor.get_entidad(0)->resetEntidad();
        monitor.get_entidad(0)->setPosicion(mix, miy);
        monitor.get_entidad(0)->setOrientacion(static_cast<Orientacion>(aleatorio(7)));
        monitor.get_entidad(0)->setHitbox(true);
        monitor.get_entidad(0)->Cogio_Bikini(false);
        monitor.get_entidad(0)->Cogio_Zapatillas(false);*/

        // Opcion simplemente choca contra el lobo
        monitor.get_entidad(0)->perderPV(1);
      }
      salida = false;
    }
    break;

  case actTURN_R:
    monitor.get_entidad(0)->giroDch();
    monitor.girarJugadorDerecha(90);
    //monitor.get_entidad(0)->fixBateria_sig_accion(celda_inicial, accion);
    salida = true;
    break;

  case actSEMITURN_R:
    monitor.get_entidad(0)->giro45Dch();
    monitor.girarJugadorDerecha(45);
    //monitor.get_entidad(0)->fixBateria_sig_accion(celda_inicial, accion);
    salida = true;
    break;

  case actTURN_L:
    monitor.get_entidad(0)->giroIzq();
    monitor.girarJugadorIzquierda(90);
    //monitor.get_entidad(0)->fixBateria_sig_accion(celda_inicial, accion);
    salida = true;
    break;

  case actSEMITURN_L:
    monitor.get_entidad(0)->giro45Izq();
    monitor.girarJugadorIzquierda(45);
    //monitor.get_entidad(0)->fixBateria_sig_accion(celda_inicial, accion);
    salida = true;
    break;

  case actWHEREIS:
    monitor.get_entidad(0)->notify();
    monitor.get_entidad(0)->fixBateria_sig_accion(celda_inicial, accion);
    salida = true;
    break;

  case actIDLE:
    if (celda_inicial == 'X')
    { // Casilla Rosa (Recarga)
      monitor.get_entidad(0)->increaseBateria(10);
    }
    //monitor.get_entidad(0)->fixBateria_sig_accion(celda_inicial, accion);

    salida = true;
    break;
  }

  return salida;
}

bool actuacionNPC(unsigned int entidad, unsigned char celda, Action accion, unsigned int x, unsigned int y)
{
  bool out = false;
  switch (monitor.get_entidad(entidad)->getSubTipo())
  {
  case aldeano: // Acciones para el aldeano
    switch (accion)
    {
    case actFORWARD:
      if ((celda != 'P' and celda != 'M') and monitor.getMapa()->casillaOcupada(entidad) == -1)
      {
        monitor.get_entidad(entidad)->setPosicion(x, y);
        out = true;
      }
      break;

    case actTURN_R:
      monitor.get_entidad(entidad)->giroDch();
      out = true;
      break;

    case actTURN_L:
      monitor.get_entidad(entidad)->giroIzq();
      out = true;
      break;

    case actSEMITURN_R:
      monitor.get_entidad(entidad)->giro45Dch();
      out = true;
      break;

    case actSEMITURN_L:
      monitor.get_entidad(entidad)->giro45Izq();
      out = true;
      break;
    }

  case lobo: // Acciones para el lobo
    switch (accion)
    {
    case actFORWARD:
      if ((celda != 'P' and celda != 'M') and monitor.getMapa()->casillaOcupada(entidad) == -1)
      {
        monitor.get_entidad(entidad)->setPosicion(x, y);
        out = true;
      }
      break;

    case actTURN_R:
      monitor.get_entidad(entidad)->giroDch();
      out = true;
      break;

    case actTURN_L:
      monitor.get_entidad(entidad)->giroIzq();
      out = true;
      break;

    case actSEMITURN_R:
      monitor.get_entidad(entidad)->giro45Dch();
      out = true;
      break;

    case actSEMITURN_L:
      monitor.get_entidad(entidad)->giro45Izq();
      out = true;
      break;

    case actWHEREIS: //Esta accion para un lobo es empujar equivalente a un actPUSH
      cout << "Recibido un empujon por un lobo\n";
      bool esta_jugador_delante = monitor.getMapa()->casillaOcupada(entidad) == 0;
      monitor.get_entidad(0)->seAostio();
      if (esta_jugador_delante){
        pair <int,int> casilla = monitor.getMapa()->NCasillasDelante(entidad,2);
        if (monitor.getMapa()->QuienEnCasilla(casilla.first,casilla.second) == -1 and 
            monitor.getMapa()->getCelda(casilla.first,casilla.second) != 'M' and
            monitor.getMapa()->getCelda(casilla.first,casilla.second) != 'P')
            if (aleatorio(2) == 1){ //Solo ocurre la mitad de las veces que el lobo lo intenta.
              monitor.get_entidad(0)->setPosicion(casilla.first, casilla.second);
              monitor.get_entidad(0)->Increment_Empujones();
              monitor.get_entidad(entidad)->giroIzq();
              monitor.get_entidad(entidad)->giro45Izq();
            }
      }
      out = true;
      break;

    }
  }

  return out;
}

bool actuacion(unsigned int entidad, Action accion)
{
  bool out = false;
  unsigned char celda_inicial, celda_fin, objetivo;
  unsigned int f, c;

  f = monitor.get_entidad(entidad)->getFil();
  c = monitor.get_entidad(entidad)->getCol();

  celda_inicial = monitor.getMapa()->getCelda(f, c);
  // Calculamos cual es la celda justo frente a la entidad
  switch (monitor.get_entidad(entidad)->getOrientacion())
  {
  case norte:
    f = f - 1;
    c = c;
    break;

  case noreste:
    f = f - 1;
    c = c + 1;
    break;

  case este:
    f = f;
    c = c + 1;
    break;

  case sureste:
    f = f + 1;
    c = c + 1;
    break;

  case sur:
    f = f + 1;
    c = c;
    break;

  case suroeste:
    f = f + 1;
    c = c - 1;
    break;

  case oeste:
    f = f;
    c = c - 1;
    break;


  case noroeste:
    f = f - 1;
    c = c - 1;
    break;
  }

  celda_fin = monitor.getMapa()->getCelda(f, c);

  // Dependiendo el tipo de la entidad actuamos de una forma u otra
  switch (monitor.get_entidad(entidad)->getTipo())
  {
  case jugador:
    out = actuacionJugador(celda_inicial, celda_fin, accion, f, c);
    break;

  case npc:
    out = actuacionNPC(entidad, celda_fin, accion, f, c);
    break;
  }

  return out;
}

void nucleo_motor_juego(MonitorJuego &monitor, int acc)
{
  Action accion;
  unsigned char celdaRand;

  vector<vector<vector<unsigned char>>> estado;

  estado.clear();

  for (unsigned int i = 0; i < monitor.numero_entidades(); i++)
  {
    estado.push_back(monitor.getMapa()->vision(i));
  }

  if (monitor.get_entidad(0)->ready())
  {
    clock_t t0 = clock();
    accion = monitor.get_entidad(0)->think(acc, estado[0], monitor.getLevel());
    clock_t t1 = clock();

    monitor.get_entidad(0)->addTiempo(t1 - t0);
    monitor.get_entidad(0)->getLastAction(accion);
    actuacion(0, accion);
    monitor.get_entidad(0)->setVision(monitor.getMapa()->vision(0));
  }
  else
  {
    monitor.get_entidad(0)->perderPV(1);
  }

  for (unsigned int i = 1; i < monitor.numero_entidades(); i++)
  {
    clock_t t0 = clock();
    accion = monitor.get_entidad(i)->think(-1, estado[i], monitor.getLevel());
    clock_t t1 = clock();

    monitor.get_entidad(i)->addTiempo(t1 - t0);
    actuacion(i, accion);
    monitor.get_entidad(i)->setVision(monitor.getMapa()->vision(i));
  }

  monitor.get_entidad(0)->decBateria_sig_accion();
  monitor.decPasos();

  if (acc != -1)
  {
    // sleep(monitor.getRetardo() / 10);
  }
}

bool lanzar_motor_juego(int &colisiones, int acc)
{
  bool out = false;

  if (monitor.continuarBelkan())
  {
    if (monitor.jugar())
    {
      if ((monitor.getPasos() != 0) and (!monitor.finJuego()))
      {
        nucleo_motor_juego(monitor, acc);
      }
    }

    if (monitor.mostrarResultados())
    {
    cout << "Instantes de simulacion no consumidos: " << monitor.get_entidad(0)->getInstantesPendientes() << endl;
    cout << "Tiempo Consumido: " << 1.0 * monitor.get_entidad(0)->getTiempo() / CLOCKS_PER_SEC << endl;
    cout << "Nivel Final de Bateria: " << monitor.get_entidad(0)->getBateria() << endl;
    cout << "Colisiones: " << monitor.get_entidad(0)->getColisiones() << endl;
    cout << "Empujones: " << monitor.get_entidad(0)->getEmpujones() << endl;
    cout << "Porcentaje de mapa descubierto: " << monitor.CoincidenciaConElMapa() << endl;
    cout << "Objetivos encontrados: " << monitor.get_entidad(0)->getMisiones() << endl;
    monitor.setMostrarResultados(false);

      out = true;
    }
  }
  return out;
}

void lanzar_motor_juego2(MonitorJuego &monitor)
{

  // monitor.get_entidad(0)->setObjetivo(monitor.getObjFil(), monitor.getObjCol());

  while (!monitor.finJuego() && monitor.jugar())
  {
    nucleo_motor_juego(monitor, -1);
  }

  if (monitor.mostrarResultados() and monitor.getLevel() < 2)
  {
    cout << "Longitud del camino: " << 3001 - monitor.get_entidad(0)->getInstantesPendientes() << endl;
    monitor.setMostrarResultados(false);
  }
  else if (monitor.mostrarResultados() and monitor.getLevel() == 2)
  {
    cout << "Coste de Bateria: " << 3000 - monitor.get_entidad(0)->getBateria() << endl;
    monitor.setMostrarResultados(false);
  }
  else if (monitor.mostrarResultados() and monitor.getLevel() == 3)
  {
    cout << "Porcentaje de mapa descubierto: " << monitor.CoincidenciaConElMapa() << endl;
    monitor.setMostrarResultados(false);
  }
  else if (monitor.mostrarResultados())
  {
    cout << "Instantes de simulacion no consumidos: " << monitor.get_entidad(0)->getInstantesPendientes() << endl;
    cout << "Tiempo Consumido: " << 1.0 * monitor.get_entidad(0)->getTiempo() / CLOCKS_PER_SEC << endl;
    cout << "Nivel Final de Bateria: " << monitor.get_entidad(0)->getBateria() << endl;
    cout << "Colisiones: " << monitor.get_entidad(0)->getColisiones() << endl;
    cout << "Empujones: " << monitor.get_entidad(0)->getEmpujones() << endl;
    cout << "Porcentaje de mapa descubierto: " << monitor.CoincidenciaConElMapa() << endl;
    cout << "Objetivos encontrados: " << monitor.get_entidad(0)->getMisiones() << endl;
    monitor.setMostrarResultados(false);
  }
}
