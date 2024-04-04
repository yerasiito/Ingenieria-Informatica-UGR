#ifndef COMPORTAMIENTOPERRO_H
#define COMPORTAMIENTOPERRO_H

#include "comportamientos/comportamiento.hpp"

class ComportamientoPerro : public Comportamiento{

  public:
    ComportamientoPerro(unsigned int size = 0) : Comportamiento(size){
      last_action = actIDLE;
      girando = false;
    }
    ComportamientoPerro(const ComportamientoPerro & comport) : Comportamiento(comport){}
    ~ComportamientoPerro(){}

    Action think(Sensores sensores);

    int interact(Action accion, int valor);


    ComportamientoPerro * clone(){return new ComportamientoPerro(*this);}

  private:
    Action last_action;
    bool girando;
};


#endif
