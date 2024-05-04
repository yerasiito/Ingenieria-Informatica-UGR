package civitas;

class GestorEstados {
  EstadoJuego estadoInicial() {
    return (EstadoJuego.INICIO_TURNO);
  }
  
  OperacionJuego siguienteOperacion(Jugador jugador, EstadoJuego estado) {
    OperacionJuego op = null;

    switch (estado) {
      case INICIO_TURNO :
          op = OperacionJuego.AVANZAR;
        break;

      case DESPUES_AVANZAR :
        if (jugador.getPuedeComprar())
          op = OperacionJuego.COMPRAR;
        else if (jugador.tieneAlgoQueGestionar())
          op = OperacionJuego.GESTIONAR;
        else
          op = OperacionJuego.PASAR_TURNO;
        break;

      case DESPUES_COMPRAR :
        if (jugador.tieneAlgoQueGestionar())
          op = OperacionJuego.GESTIONAR;
        else
          op = OperacionJuego.PASAR_TURNO;
        break;

      case DESPUES_GESTIONAR :
        op = OperacionJuego.PASAR_TURNO;
        break;        
    }
    return op;
  }
  
  EstadoJuego siguienteEstado (Jugador jugador, EstadoJuego estado, OperacionJuego operacion) {
    EstadoJuego siguiente = null;

    switch (estado) {
      case INICIO_TURNO :
        if (operacion==OperacionJuego.AVANZAR)
          siguiente = EstadoJuego.DESPUES_AVANZAR;
        break;

      case DESPUES_AVANZAR :
        switch (operacion) {
          case PASAR_TURNO :
            siguiente = EstadoJuego.INICIO_TURNO;
            break;
          case COMPRAR :
            siguiente = EstadoJuego.DESPUES_COMPRAR;
            break;
          case GESTIONAR :
            siguiente = EstadoJuego.DESPUES_GESTIONAR;
            break;
        }
        break;

      case DESPUES_COMPRAR :
        if (operacion==OperacionJuego.GESTIONAR)
          siguiente = EstadoJuego.DESPUES_GESTIONAR;
        else if (operacion==OperacionJuego.PASAR_TURNO)
          siguiente = EstadoJuego.INICIO_TURNO;
        break;

      case DESPUES_GESTIONAR :
        if (operacion==OperacionJuego.PASAR_TURNO)
          siguiente = EstadoJuego.INICIO_TURNO;
        break;
    }

    Diario.getInstance().ocurreEvento("De: "+estado.toString()+ " con "+operacion.toString()+ " sale: "+siguiente.toString());

    return siguiente;
  }

}