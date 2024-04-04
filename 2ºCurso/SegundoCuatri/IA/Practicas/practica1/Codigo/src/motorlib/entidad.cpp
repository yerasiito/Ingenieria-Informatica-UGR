#include "motorlib/entidad.hpp"

void Entidad::resetEntidad()
{
  hitbox = false;
  if (tipo == jugador)
  {
    desactivado = 0;
  }
  else
  {
    desactivado = aleatorio(7) + 3;
  }

  colision = false;
  //colisiones = 0;
  reset = true;
  if (vida != 0)
    muertes_innecesarias++;
  // vida = 0;
  done = false;

  mensaje = false;
}

Action Entidad::think(int acc, vector<vector<unsigned char>> vision, int level)
{
  Action accion = actIDLE;
  Sensores sensor;

  if (desactivado == 0)
  {
    vida--;
    hitbox = true;

    sensor.nivel = level;

    sensor.vida = vida;
    sensor.bateria = bateria;

    sensor.colision = colision;
    sensor.reset = reset;

    if (tipo == jugador)
    {
      if (sensor.bateria == 0)
      {
        done = true;
        cout << "Se agoto la bateria!" << endl;
      }
      else if (sensor.vida == 0)
      {
        done = true;
        cout << "Se agotaron los instantes de simulacion" << endl;
      }
      else if (getTiempo() > getTiempoMaximo())
      {
        done = true;
        cout << "Se agoto el tiempo de deliberacion!" << endl;
      }
    }

    // Fijo los valores que se le pasan al sistema sensorial de la entidad
    sensor.posF = f;
    sensor.posC = c;
    sensor.sentido = orient;
    sensor.superficie = vision[1];
    sensor.terreno = vision[0];
    sensor.tiempo = getTiempo() / CLOCKS_PER_SEC;
    visionAux = vision;

    // Restringir los sensores segun el nivel del problema
    if (tipo == jugador)
    {
      if (!hasToNotify() and level >= 1)
      {
        sensor.posF = -1;
        sensor.posC = -1;
        setNotifyOff();
      }
      if (level >= 2)
      {
        if (getTiempo() >= 0 and !hasToNotify())
        {
          sensor.sentido = norte;
        }
      }
    }

    if (acc == -1)
      accion = comportamiento->think(sensor);
    else
      accion = static_cast<Action>(acc);

    colision = false;
    reset = false;
  }
  else
  {
    desactivado--;
  }

  return accion;
}

bool Entidad::interact(Action accion, int valor)
{
  bool out = false;
  int retorno = comportamiento->interact(accion, valor);

  if (retorno == 1)
  { // Desaparición temporal
    resetEntidad();
    out = true;
  }

  if (retorno == 2)
  { // Muerte
    hitbox = false;
    desactivado = -1;
    out = true;
  }

  if (retorno == 3)
  { // Revivir
    hitbox = true;
    desactivado = 0;
    out = true;
  }

  return out;
}

unsigned char Entidad::getSubTipoChar()
{
  unsigned char out = ' ';

  switch (subtipo)
  {
  case jugador_:
    out = 'j';
    break;
  case aldeano:
    out = 'a';
    break;
  case lobo:
    out = 'l';
    break;
  }

  return out;
}

string strAccion(int accion)
{
  string out = "";

  switch (accion)
  {
  case 0:
    out = "actFORWARD";
    break;
  case 1:
    out = "actTURN_L";
    break;
  case 2:
    out = "actTURN_R";
    break;
  case 3:
    out = "actIDLE";
    break;
  }

  return out;
}

string Entidad::toString()
{
  char aux[20];
  string saux;

  string str;

  sprintf(aux, "%d", vida);
  saux = aux;
  str += "Ciclos restantes: " + saux + "\n";

  sprintf(aux, "%d", bateria);
  saux = aux;
  str += "Bateria: " + saux + "\n";

  string paDonde;
  switch (getOrientacion())
  {
  case norte:
    paDonde = "norte";
    break;
  case este:
    paDonde = "este ";
    break;
  case sur:
    paDonde = "sur  ";
    break;
  case oeste:
    paDonde = "oeste";
    break;
  }

  str += "Posicion actual: (F ";
  sprintf(aux, "%d", getFil());
  saux = aux;
  str += saux;
  str += " , C ";
  sprintf(aux, "%d", getCol());
  saux = aux;
  str += saux;
  str += " | ";
  str += paDonde;
  str += ")";
  str += "\n";

  str += "Ultima Accion: " + strAccion(last_action) + "\n";

  sprintf(aux, "%3.3f", tiempo / CLOCKS_PER_SEC);
  saux = aux;

  str += "Tiempo Consumido: " + saux + "\n";

  string saux2;
  if (Has_Zapatillas())
  {
    saux2 = "ZAPATILLAS ON   |";
  }
  else
  {
    saux2 = "ZAPATILLAS OFF  |";
  }

  if (Has_Bikini())
  {
    saux2 = saux2 + "   BIKINI ON \n";
  }
  else
  {
    saux2 = saux2 + "   BIKINI OFF\n";
  }
  str += saux2;

  sprintf(aux, "%d", getMisiones());
  // str += "Objetivos: ";
  str += "";
  // saux = aux;
  // str += saux;
  str += "\n";

  if (visionAux.size() > 0)
  {
    str += "************ Vision **************\n";

    for (unsigned int i = 0; i < visionAux[1].size(); i++)
    {
      str += visionAux[1][i];
      str += " ";
    }

    str += "\n";

    for (unsigned int i = 0; i < visionAux[0].size(); i++)
    {
      str += visionAux[0][i];
      str += " ";
    }

    str += "\n";
  }

  return str;
}

void Entidad::fixTiempo_sig_accion(unsigned char celda)
{
  tiempo_sig_accion = 1;
}

int Entidad::fixBateria_sig_accion(unsigned char celda, Action accion)
{
  bateria_sig_accion = 1;
  switch (accion)
  {
  case actIDLE:
    bateria_sig_accion = 0;
    break;
  case actFORWARD:
    switch (celda)
    {
    case 'A':
      if (Has_Bikini()) // Bikini
        bateria_sig_accion = 10;
      else
        bateria_sig_accion = 200;
      break;
    case 'B':
      if (Has_Zapatillas()) // Zapatillas
        bateria_sig_accion = 15;
      else
        bateria_sig_accion = 100;
      break;
    case 'T':
      bateria_sig_accion = 2;
      break;
    default:
      bateria_sig_accion = 1;
      break;
    } // Fin switch celda
    break;
  case actTURN_L:
  case actTURN_R:
    switch (celda)
    {
    case 'A':
      if (Has_Bikini()) // Bikini
        bateria_sig_accion = 5;
      else
        bateria_sig_accion = 500;
      break;
    case 'B':
      if (Has_Zapatillas()) // Zapatillas
        bateria_sig_accion = 1;
      else
        bateria_sig_accion = 3;
      break;
    case 'T':
      bateria_sig_accion = 2;
      break;
    default:
      bateria_sig_accion = 1;
      break;
    } // Fin switch celda
    break;
  }
  return bateria_sig_accion;
}

void Entidad::decBateria_sig_accion()
{
  bateria -= bateria_sig_accion;
  if (bateria < 0)
    bateria = 0;
}
