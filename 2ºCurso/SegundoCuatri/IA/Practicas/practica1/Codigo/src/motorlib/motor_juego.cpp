#include "motorlib.hpp"

#include <unistd.h>

extern MonitorJuego monitor;

bool actuacionJugador(unsigned char celda_inicial, unsigned char celda_fin, Action accion, unsigned int x, unsigned int y)
{
  unsigned int mix, miy;
  unsigned char celdaRand;
  bool salida = false;

  if (accion != actIDLE)
  {
    int gasto = monitor.get_entidad(0)->fixBateria_sig_accion(celda_inicial, accion);
    if (gasto > monitor.get_entidad(0)->getBateria())
    {
      monitor.get_entidad(0)->setBateria(0);
      return false;
    }
  }

  monitor.get_entidad(0)->fixBateria_default();
  switch (accion)
  {
  case actFORWARD:
    if (monitor.getMapa()->casillaOcupada(0) == -1)
    { // Casilla destino desocupada
      switch (celda_fin)
      {
      case 'M': // Muro
        monitor.get_entidad(0)->seAostio();
        break;
        break;
      case 'P': // Precipicio
        cout << "Se cayo por un precipicio\n";
        do
        {
          mix = aleatorio(monitor.getMapa()->getNFils() - 1);
          miy = aleatorio(monitor.getMapa()->getNCols() - 1);

          celdaRand = monitor.getMapa()->getCelda(mix, miy);
        } while (celdaRand == 'P' or celdaRand == 'M' or monitor.getMapa()->entidadEnCelda(mix, miy) != '_');

        //cout << "fila: " << mix << " col: " << miy << endl;
        monitor.get_entidad(0)->resetEntidad();
        monitor.get_entidad(0)->setPosicion(mix, miy);
        monitor.get_entidad(0)->setOrientacion(norte);
        monitor.get_entidad(0)->setHitbox(true);
        monitor.get_entidad(0)->Cogio_Bikini(false);
        monitor.get_entidad(0)->Cogio_Zapatillas(false);
        // monitor.finalizarJuego();
        // monitor.setMostrarResultados(true);

        break;
      case 'G': // Casilla celeste claro (GPS)
        monitor.get_entidad(0)->notify();
        monitor.get_entidad(0)->setPosicion(x, y);
        salida = true;
        break;
      case 'X': // Casilla Rosa (Recarga)
        monitor.get_entidad(0)->increaseBateria(10);
        monitor.get_entidad(0)->setPosicion(x, y);
        salida = true;
        break;
      case 'D': // Casilla Morada (Zapatillas)
        // tomo la zapatilla
        monitor.get_entidad(0)->Cogio_Zapatillas(true);
        monitor.get_entidad(0)->setPosicion(x, y);
        salida = true;
        break;
      case 'K': // Casilla Amarilla (Bikini)
        // tomo el bikini
        monitor.get_entidad(0)->Cogio_Bikini(true);
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
      monitor.get_entidad(0)->fixBateria_sig_accion(celda_inicial, accion);
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
        do
        {
          mix = aleatorio(monitor.getMapa()->getNFils() - 1);
          miy = aleatorio(monitor.getMapa()->getNCols() - 1);

          celdaRand = monitor.getMapa()->getCelda(mix, miy);
        } while (celdaRand == 'P' or celdaRand == 'M' or monitor.getMapa()->entidadEnCelda(mix, miy) != '_');

        monitor.get_entidad(0)->resetEntidad();
        monitor.get_entidad(0)->setPosicion(mix, miy);
        monitor.get_entidad(0)->setOrientacion(norte);
        monitor.get_entidad(0)->setHitbox(true);
        monitor.get_entidad(0)->Cogio_Bikini(false);
        monitor.get_entidad(0)->Cogio_Zapatillas(false);
      }
      salida = false;
    }
    break;

  case actTURN_R:
    if (celda_inicial == 'X')
    { // Casilla Rosa (Recarga)
      monitor.get_entidad(0)->increaseBateria(10);
    }

    switch (monitor.get_entidad(0)->getOrientacion())
    {
    case norte:
      monitor.get_entidad(0)->setOrientacion(este);
      break;

    case este:
      monitor.get_entidad(0)->setOrientacion(sur);
      break;

    case sur:
      monitor.get_entidad(0)->setOrientacion(oeste);
      break;

    case oeste:
      monitor.get_entidad(0)->setOrientacion(norte);
      break;
    }
    monitor.girarJugadorDerecha();
    salida = true;
    monitor.get_entidad(0)->fixBateria_sig_accion(celda_inicial, accion);
    break;

  case actTURN_L:
    if (celda_inicial == 'X')
    { // Casilla Rosa (Recarga)
      monitor.get_entidad(0)->increaseBateria(10);
    }

    switch (monitor.get_entidad(0)->getOrientacion())
    {
    case norte:
      monitor.get_entidad(0)->setOrientacion(oeste);
      break;

    case este:
      monitor.get_entidad(0)->setOrientacion(norte);
      break;

    case sur:
      monitor.get_entidad(0)->setOrientacion(este);
      break;

    case oeste:
      monitor.get_entidad(0)->setOrientacion(sur);
      break;
    }
    monitor.get_entidad(0)->fixBateria_sig_accion(celda_inicial, accion);
    monitor.girarJugadorIzquierda();
    salida = true;
    break;

  case actIDLE:
    if (celda_inicial == 'X')
    { // Casilla Rosa (Recarga)
      monitor.get_entidad(0)->increaseBateria(10);
    }
    monitor.get_entidad(0)->fixBateria_sig_accion(celda_inicial, accion);

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
  case lobo:    // Acciones para el lobo
    switch (accion)
    {
    case actFORWARD:
      if ((celda != 'P' and celda != 'M') and monitor.getMapa()->casillaOcupada(entidad) == -1)
      {
        monitor.get_entidad(entidad)->setPosicion(x, y);
        out = true;
      }
      else if (monitor.get_entidad(entidad)->getSubTipo() == lobo and monitor.getMapa()->casillaOcupada(entidad) == 0)
      {
        // cout << "atacado por un lobo\n";
        int mix, miy;
        unsigned char celdaRand;
        do
        {
          mix = aleatorio(monitor.getMapa()->getNFils() - 1);
          miy = aleatorio(monitor.getMapa()->getNCols() - 1);

          celdaRand = monitor.getMapa()->getCelda(mix, miy);
        } while (celdaRand == 'P' or celdaRand == 'M' or monitor.getMapa()->entidadEnCelda(mix, miy) != '_');

        monitor.get_entidad(0)->resetEntidad();
        monitor.get_entidad(0)->setPosicion(mix, miy);
        monitor.get_entidad(0)->setOrientacion(norte);
        monitor.get_entidad(0)->setHitbox(true);
        monitor.get_entidad(0)->Cogio_Bikini(false);
        monitor.get_entidad(0)->Cogio_Zapatillas(false);
      }
      break;

    case actTURN_R:
      switch (monitor.get_entidad(entidad)->getOrientacion())
      {
      case norte:
        monitor.get_entidad(entidad)->setOrientacion(este);
        break;

      case este:
        monitor.get_entidad(entidad)->setOrientacion(sur);
        break;

      case sur:
        monitor.get_entidad(entidad)->setOrientacion(oeste);
        break;

      case oeste:
        monitor.get_entidad(entidad)->setOrientacion(norte);
        break;
      }
      out = true;
      break;

    case actTURN_L:
      switch (monitor.get_entidad(entidad)->getOrientacion())
      {
      case norte:
        monitor.get_entidad(entidad)->setOrientacion(oeste);
        break;

      case este:
        monitor.get_entidad(entidad)->setOrientacion(norte);
        break;

      case sur:
        monitor.get_entidad(entidad)->setOrientacion(este);
        break;

      case oeste:
        monitor.get_entidad(entidad)->setOrientacion(sur);
        break;
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

  case sur:
    f = f + 1;
    c = c;
    break;

  case este:
    f = f;
    c = c + 1;
    break;

  case oeste:
    f = f;
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
      cout << "Reinicios: " << monitor.get_entidad(0)->getMuertesI() << endl;
      cout << "Porcentaje de mapa descubierto: " << monitor.CoincidenciaConElMapa() << endl;
      monitor.setMostrarResultados(false);

      out = true;
    }
  }
  return out;
}

void lanzar_motor_juego2(MonitorJuego &monitor)
{

  while (!monitor.finJuego() && monitor.jugar())
  {
    nucleo_motor_juego(monitor, -1);
  }

  if (monitor.mostrarResultados())
  {
    cout << "Instantes de simulacion no consumidos: " << monitor.get_entidad(0)->getInstantesPendientes() << endl;
    cout << "Tiempo Consumido: " << 1.0 * monitor.get_entidad(0)->getTiempo() / CLOCKS_PER_SEC << endl;
    cout << "Nivel Final de Bateria: " << monitor.get_entidad(0)->getBateria() << endl;
    cout << "Colisiones: " << monitor.get_entidad(0)->getColisiones() << endl;
    cout << "Reinicios: " << monitor.get_entidad(0)->getMuertesI() << endl;
    cout << "Porcentaje de mapa descubierto: " << monitor.CoincidenciaConElMapa() << endl;
    monitor.setMostrarResultados(false);
  }
}
