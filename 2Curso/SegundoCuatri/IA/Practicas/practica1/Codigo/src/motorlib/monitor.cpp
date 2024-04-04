#include "motorlib/monitor.hpp"

#include <fstream>

void MonitorJuego::cambiarOrientacion(unsigned char entidad, unsigned char orientacion)
{
  Orientacion aux;
  switch (orientacion)
  {
  case 0:
    aux = norte;
    break;

  case 1:
    aux = este;
    break;

  case 2:
    aux = sur;
    break;

  case 3:
    aux = oeste;
    break;
  }
  entidades[entidad]->setOrientacion(aux);
}

void MonitorJuego::setMapa(const char *file)
{
  ifstream ifile;
  ifile.open(file, ios::in);

  unsigned int colSize, filSize;
  ifile >> colSize;
  ifile >> filSize;

  vector<vector<unsigned char>> mapAux;
  vector<unsigned char> colAux(colSize);

  for (unsigned int i = 0; i < filSize; i++)
  {
    mapAux.push_back(colAux);
  }

  for (unsigned int i = 0; i < filSize; i++)
  {
    for (unsigned int j = 0; j < colSize; j++)
    {
      ifile >> mapAux[i][j];
    }
  }
  ifile.close();

  mapa = new Mapa(mapAux, &entidades);
}

bool MonitorJuego::inicializarJuego()
{
  bool aux = empezarJuego;
  if (empezarJuego)
  {
    empezarJuego = false;
    resultados = false;
  }
  return aux;
}

void MonitorJuego::generate_a_valid_cell(int &pos_fila, int &pos_col, int &ori)
{
  pos_col = -1;
  pos_fila = -1;
  char celdaRand = '_';
  do
  {
    pos_fila = aleatorio(getMapa()->getNFils() - 1);
    pos_col = aleatorio(getMapa()->getNCols() - 1);

    celdaRand = getMapa()->getCelda(pos_fila, pos_col);
  } while ((celdaRand == 'P' or celdaRand == 'M'));
  ori = aleatorio(3);
}

bool MonitorJuego::is_a_valid_cell_like_goal(int f, int c)
{
  if (f < 0 or f >= getMapa()->getNFils())
    return false;
  if (c < 0 or c >= getMapa()->getNCols())
    return false;
  char cell = getMapa()->getCelda(f, c);
  if (cell == 'M' or cell == 'P')
    return false;
  return true;
}

void MonitorJuego::decPasos()
{
  if (get_entidad(0)->fin())
  {
    jugando = false;
    resultados = true;
  }
  else
  {
    if (pasos > 0)
    {
      pasos--;
      pasosTotales++;
    }

    if (!get_entidad(0)->vivo() or get_entidad(0)->getBateria() == 0)
    {
      jugando = false;
      resultados = true;
    }
  }
}

void MonitorJuego::inicializar(int pos_fila, int pos_col, int bruj, int seed)
{
  clear(); // Elimina el verctor de entidades
  srand(seed);
  // cout << "Estoy en MonitorJuego::inicializar\n";
  int tama = getMapa()->getNCols();

  // Si es la primera vez que se llama se fija el numero de lobos y aldeanos al 10 % del numero de columnas
  if (get_n_aldeanos() == -1)
  {
    set_n_aldeanos(tama / 10);
    set_n_lobos(tama / 10);
  }

  unsigned char celdaRand;

  // Primero SIEMPRE se coloca al jugador. SIEMPRE.
  if ((pos_fila == -1) or (pos_col == -1))
  {
    do
    {
      pos_fila = aleatorio(getMapa()->getNFils() - 1);
      pos_col = aleatorio(getMapa()->getNCols() - 1);
      celdaRand = getMapa()->getCelda(pos_fila, pos_col);
    } while ((celdaRand == 'P') or (celdaRand == 'M') or (getMapa()->entidadEnCelda(pos_fila, pos_col) != '_'));
  }

  if (nivel < 2)
  {
    if (bruj == -1)
      bruj = rand() % 4;
    nueva_entidad(new Entidad(jugador, jugador_, static_cast<Orientacion>(bruj), pos_fila, pos_col, new Jugador3D(""), new ComportamientoJugador(getMapa()->getNFils()), 3000));
  }
  else
  {
    nueva_entidad(new Entidad(jugador, jugador_, norte, pos_fila, pos_col, new Jugador3D(""), new ComportamientoJugador(getMapa()->getNFils()), 3000));
  }
  // Para los niveles 3 y 4 genero los aldeanos
  if (nivel >= 3)
  {
    for (int i = 0; i < get_n_aldeanos(); i++)
    {
      do
      {
        pos_fila = aleatorio(getMapa()->getNFils() - 1);
        pos_col = aleatorio(getMapa()->getNCols() - 1);
        celdaRand = getMapa()->getCelda(pos_fila, pos_col);
      } while ((celdaRand == 'P') or (celdaRand == 'M') or (getMapa()->entidadEnCelda(pos_fila, pos_col) != '_'));
      bruj = rand() % 4;
      nueva_entidad(new Entidad(npc, aldeano, static_cast<Orientacion>(bruj), pos_fila, pos_col, new Aldeano3D(""), new ComportamientoAldeano(), 3000));
    }
  }

  // Para el nivel 4 genero los lobos
  if (nivel >= 4)
  {
    for (int i = 0; i < get_n_lobos(); i++)
    {
      do
      {
        pos_fila = aleatorio(getMapa()->getNFils() - 1);
        pos_col = aleatorio(getMapa()->getNCols() - 1);
        celdaRand = getMapa()->getCelda(pos_fila, pos_col);
      } while ((celdaRand == 'P') or (celdaRand == 'M') or (getMapa()->entidadEnCelda(pos_fila, pos_col) != '_'));
      bruj = rand() % 4;
      nueva_entidad(new Entidad(npc, lobo, static_cast<Orientacion>(bruj), pos_fila, pos_col, new Perro3D(), new ComportamientoPerro(), 3000));
    }
  }

  get_entidad(0)->setVision(getMapa()->vision(0));

  srand(seed);
  /* quitar esto una vez verificado */
  // PintaEstadoMonitor();
}

double MonitorJuego::CoincidenciaConElMapa()
{
  unsigned int aciertos = 0, totalCasillas = 0;

  for (unsigned int i = 0; i < getMapa()->getNFils(); i++)
  {
    for (unsigned int j = 0; j < getMapa()->getNCols(); j++)
    {
      if (getMapa()->getCelda(i, j) == get_entidad(0)->getMapaResultado()[i][j])
      {
        aciertos++;
      }
      totalCasillas++;
    }
  }
  return (aciertos * 100.0 / totalCasillas);
}

void MonitorJuego::PintaEstadoMonitor()
{
  cout << "*********************************************\n";
  cout << "Pos Fil: " << get_entidad(0)->getFil() << endl;
  cout << "Pos Col: " << get_entidad(0)->getCol() << endl;
  cout << "Brujula: " << get_entidad(0)->getOrientacion() << endl;
  cout << "aldeanos: " << numero_entidades() << endl;
  for (int i = 1; i < numero_entidades(); i++)
  {
    cout << "     Tipo: " << get_entidad(i)->getSubTipo() << endl;
    cout << "  Pos Fil: " << get_entidad(i)->getFil() << endl;
    cout << "  Pos Col: " << get_entidad(i)->getCol() << endl;
    cout << "  Brujula: " << get_entidad(i)->getOrientacion() << endl
         << endl;
  }
  cout << "*********************************************\n";
}

void MonitorJuego::init_casillas_especiales(unsigned int f, unsigned int c){
  unsigned char celda_inicial;
  celda_inicial = getMapa()->getCelda(f, c);
  if (celda_inicial == 'D'){
    get_entidad(0)->Cogio_Zapatillas(true);
  }
  else if (celda_inicial == 'K'){
    get_entidad(0)->Cogio_Bikini(true);
  }
  else if (celda_inicial == 'G'){
    get_entidad(0)->notify();
  }
}
