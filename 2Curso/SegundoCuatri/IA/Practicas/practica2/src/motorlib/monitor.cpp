#include "motorlib/monitor.hpp"

#include <fstream>

void MonitorJuego::cambiarOrientacion(unsigned char entidad, unsigned char orientacion) {
  Orientacion aux;
  switch (orientacion) {
    case 0:
    	aux = norte;
    	break;
    case 1:
    	aux = noreste;
    	break;
    case 2:
    	aux = este;
    	break;
    case 3:
    	aux = sureste;
    	break;
    case 4:
    	aux = sur;
    	break;
    case 5:
    	aux = suroeste;
    	break;
    case 6:
    	aux = oeste;
    	break;
    case 7:
    	aux = noroeste;
    	break;
  }
  entidades[entidad]->setOrientacion(aux);
}

void MonitorJuego::setMapa(const char * file) {
  ifstream ifile;
  ifile.open(file, ios::in);

  unsigned int colSize, filSize;
  ifile >> colSize;
  ifile >> filSize;

  vector<vector<unsigned char> > mapAux;
  vector<unsigned char> colAux(colSize);

  for (unsigned int i = 0; i < filSize; i++) {
    mapAux.push_back(colAux);
  }

  for (unsigned int i = 0; i < filSize; i++) {
    for (unsigned int j = 0; j < colSize; j++) {
      ifile >> mapAux[i][j];
    }
  }
  ifile.close();

  mapa = new Mapa(mapAux, &entidades);
}

bool MonitorJuego::inicializarJuego() {
  bool aux = empezarJuego;
  if (empezarJuego) {
      empezarJuego = false;
      resultados = false;
  }
  return aux;
}



void MonitorJuego::generate_a_valid_cell(int &pos_fila, int &pos_col, int &ori){
  pos_col = -1;
  pos_fila = -1;
  char celdaRand = '_';
  do {
    pos_fila = aleatorio(getMapa()->getNFils()-1);
    pos_col = aleatorio(getMapa()->getNCols()-1);

    celdaRand = getMapa()->getCelda(pos_fila, pos_col);
  }
  while( (celdaRand == 'P' or celdaRand == 'M') );
  ori = aleatorio(7);
}

bool MonitorJuego::is_a_valid_cell_like_goal(int f, int c){
  if (f < 0 or f>=getMapa()->getNFils()) return false;
  if (c < 0 or c>=getMapa()->getNCols()) return false;
  char cell = getMapa()->getCelda(f,c);
  if (cell =='M' or cell =='P') return false;
  return true;
}



void MonitorJuego::generate_a_objetive(){
  int pos_col = -1, pos_fila = -1;
  char celdaRand = '_';
  do {
    pos_fila = aleatorio(getMapa()->getNFils()-1);
    pos_col = aleatorio(getMapa()->getNCols()-1);

    celdaRand = getMapa()->getCelda(pos_fila, pos_col);
  }
  while( (celdaRand == 'P' or celdaRand == 'M') );

  pair<int,int> punto;
  punto.first = pos_fila;
  punto.second = pos_col;
  objetivos.push_back(punto);
}


void MonitorJuego::put_a_new_objetivo_front(int fila, int columna){
  pair<int,int> punto;
  punto.first = fila;
  punto.second = columna;
  objetivos.push_front(punto);
}


// Pasa de la lista de objetivos al vector de objetivos activos.
// 'number' establece el número de objetivos que se fijan simultáneamente
void MonitorJuego::put_active_objetivos(int number){
  vector<unsigned int> v;

  if (mapa!=0){
      while (objetivos.size()<number){
        generate_a_objetive();
      }
      for (int i=0; i<number; i++){
        auto it=objetivos.begin();
        v.push_back(it->first);
        v.push_back(it->second);
        objetivos.erase(objetivos.begin());
      }
  }
  else {
     v.push_back(3);
     v.push_back(3);
  }
  objetivosActivos = v;
}


void MonitorJuego::get_n_active_objetivo (int n,int &posFila, int &posCol){
  if (n<objetivosActivos.size()/2){
    posFila = objetivosActivos[2*n];
    posCol = objetivosActivos[2*n+1];
  }
}

void MonitorJuego::set_n_active_objetivo (int n, int posFila, int posCol){
  //if (n<objetivosActivos.size()/2){
  if (n<3){
    objetivosActivos[2*n] = posFila;
    objetivosActivos[2*n+1] = posCol;
  }
  if (numero_entidades()>0)
    get_entidad(0)->setObjetivos(objetivosActivos);
}

bool MonitorJuego::there_are_active_objetivo(){
  return (objetivosActivos.size()>0);
}

int MonitorJuego::get_number_active_objetivos(){
  return (objetivosActivos.size()/2);
}


vector<unsigned int> MonitorJuego::get_active_objetivos(){
  vector<unsigned int> copia = objetivosActivos;
  return copia;
}




void MonitorJuego::decPasos() {
  if (get_entidad(0)->fin()) {
    if (nivel < 4) {
      jugando = false;
      resultados = true;
    }
    else {
      // Nivel 4
      if (!get_entidad(0)->vivo()
           or get_entidad(0)->getBateria() == 0
           or get_entidad(0)->getTiempo() > get_entidad(0)->getTiempoMaximo()) {
        jugando = false;
        resultados = true;
      }
      else {
        // Nuevo destino
        if (get_entidad(0)->allObjetivosAlcanzados()){
          /*put_active_objetivos(3);
          get_entidad(0)->anularAlcanzados();
          get_entidad(0)->setObjetivos(get_active_objetivos());*/
          // setObjCol(pos_col);
          // setObjFil(pos_fila);
          // if (editPosC != NULL)
          // editPosC->set_int_val(pos_col);
          // if (editPosF != NULL)
          // editPosF->set_int_val(pos_fila);
          // cout << "Nuevo objetivo: (" << pos_fila << "," << pos_col << ")" << endl;
          get_entidad(0)->resetFin();
        }

        if (pasos > 0) {
          pasos--;
          pasosTotales++;
        }
      }
    }
  }
  else {
    if (pasos > 0) {
      pasos--;
      pasosTotales++;
    }

    if (!get_entidad(0)->vivo() or get_entidad(0)->getBateria() == 0) {
      jugando = false;
      resultados = true;
    }
  }
}



void MonitorJuego::inicializar(int pos_fila, int pos_col, int bruj, int seed) {
  clear();
  //srand(seed);
  //cout << "Estoy en MonitorJuego::inicializar\n";
  int tama = getMapa()->getNCols();

  int naldeanos = tama / 10;
  int nlobos = tama / 10;
  unsigned char celdaRand;

  //Se construye una lisa con 300 objetivos
  if (nivel == 4) {
    while (objetivos.size()<300){
      generate_a_objetive();
    }
  }

  //Primero SIEMPRE se coloca al jugador. SIEMPRE.
  if ((pos_fila == -1) or (pos_col == -1)) {
    do {
      pos_fila = aleatorio(getMapa()->getNFils()-1);
      pos_col = aleatorio(getMapa()->getNCols()-1);
      celdaRand = getMapa()->getCelda(pos_fila, pos_col);
    }
    while( (celdaRand == 'P') or (celdaRand == 'M') or (getMapa()->entidadEnCelda(pos_fila, pos_col) != '_') );
  }
  else {
    // para hacer que la secuencia de recogida de numeros aleatorios sea independiente si da o no las coordenadas al principio
    int kkx = aleatorio(getMapa()->getNFils()-1);
    int kky = aleatorio(getMapa()->getNCols()-1);

  }

  // Pongo los primeros objetivos objetivosActivos
  if (nivel <3 ){
    put_active_objetivos(1);
  }
  else if (nivel == 4){
    put_active_objetivos(3);
  }
  else {
    put_active_objetivos(0);
  }

  // Para los primeros niveles hago el mapa visible
  if ( (nivel==0) or (nivel == 1) or (nivel == 2) ) {
    vector< vector< unsigned char> > mAux(getMapa()->getNFils(), vector< unsigned char>(getMapa()->getNCols(), '?'));
    for (int i = 0; i < getMapa()->getNFils(); i++)
      for (int j = 0; j < getMapa()->getNCols(); j++)
        mAux[i][j] = getMapa()->getCelda(i, j);
    // Esto coloca al jugador en el mapa
    //cout << "bruj: " << bruj << endl;

      nueva_entidad(new Entidad(jugador, jugador_,static_cast<Orientacion>(bruj), pos_fila, pos_col, new Jugador3D(""), new ComportamientoJugador(mAux), 1, objetivosActivos, 3000));
  }
  else {
    // Esto coloca al jugador en el mapa
    if (bruj ==-1) bruj = rand() % 4;

    if (nivel == 3){
      nueva_entidad(new Entidad(jugador, jugador_, static_cast<Orientacion>(bruj), pos_fila, pos_col, new Jugador3D(""), new ComportamientoJugador(getMapa()->getNFils()), 0, objetivosActivos, 3000));
    }
    else {
      nueva_entidad(new Entidad(jugador, jugador_, static_cast<Orientacion>(bruj), pos_fila, pos_col, new Jugador3D(""), new ComportamientoJugador(getMapa()->getNFils()), objetivosActivos.size()/2, objetivosActivos, 3000));
    }

  }

  // Para el último nivel genero los aldeanos y lobos
  if (nivel == 4) {
    for (int i=0; i<naldeanos; i++) {
      do {
        pos_fila = aleatorio(getMapa()->getNFils()-1);
        pos_col = aleatorio(getMapa()->getNCols()-1);
        celdaRand = getMapa()->getCelda(pos_fila, pos_col);
      }
      while( (celdaRand == 'P') or (celdaRand == 'M') or (getMapa()->entidadEnCelda(pos_fila, pos_col) != '_') );
      nueva_entidad(new Entidad(npc, aldeano, static_cast<Orientacion>(aleatorio(7)), pos_fila, pos_col, new Aldeano3D(""), new ComportamientoAldeano(), 0, objetivosActivos, 3000));
    }

    for (int i=0; i<nlobos; i++) {
      do {
        pos_fila = aleatorio(getMapa()->getNFils()-1);
        pos_col = aleatorio(getMapa()->getNCols()-1);
        celdaRand = getMapa()->getCelda(pos_fila, pos_col);
      }
      while( (celdaRand == 'P') or (celdaRand == 'M') or (getMapa()->entidadEnCelda(pos_fila, pos_col) != '_') );
      nueva_entidad(new Entidad(npc, lobo, static_cast<Orientacion>(aleatorio(7)), pos_fila, pos_col, new Perro3D, new ComportamientoPerro(), 0, objetivosActivos, 3000));
    }
  }

  get_entidad(0)->setVision(getMapa()->vision(0));
  if ((nivel == 0) or (nivel == 1) or (nivel == 2) or (nivel == 3))
    get_entidad(0)->notify();

  //srand(seed);
  /* quitar esto una vez verificado */
  //PintaEstadoMonitor();

}



void MonitorJuego::PintaEstadoMonitor(){
  cout << "*********************************************\n";
  cout << "Pos Fil: " << get_entidad(0)->getFil() <<endl;
  cout << "Pos Col: " << get_entidad(0)->getCol() <<endl;
  cout << "Brujula: " << get_entidad(0)->getOrientacion() <<endl;
  for (int i=0; i<get_entidad(0)->getNumObj(); i++){
    cout << "Obj " << i <<" : F: " << get_entidad(0)->getObjFil(i) << "  C: " << get_entidad(0)->getObjCol(i) <<endl;
  }
  cout << "aldeanos: " << numero_entidades() << endl;
  for (int i=1; i<numero_entidades(); i++){
    cout << "  Pos Fil: " << get_entidad(i)->getFil() <<endl;
    cout << "  Pos Col: " << get_entidad(i)->getCol() <<endl;
    cout << "  Brujula: " << get_entidad(i)->getOrientacion() <<endl << endl;
  }
  cout << "*********************************************\n";
}

double MonitorJuego::CoincidenciaConElMapa()
{
  int aciertos = 0, totalCasillas = 0;

  for (unsigned int i = 0; i < getMapa()->getNFils(); i++)
  {
    for (unsigned int j = 0; j < getMapa()->getNCols(); j++)
    {
      if (getMapa()->getCelda(i, j) == get_entidad(0)->getMapaResultado()[i][j])
      {
        aciertos++;
      }
      else if (get_entidad(0)->getMapaResultado()[i][j] != '?'){ //Puso un valor distinto de desconocido en mapaResultado y no acertó
        aciertos--;
      }
      totalCasillas++;
    }
  }
  return (aciertos * 100.0 / totalCasillas);
}
