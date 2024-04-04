#include <fstream>
#include "motorlib.hpp"

bool fileExists( std::string const& name )
{
    ifstream f(name.c_str());
    return f.good();
}


int main(int argc, char ** argv) {
  EnLinea argumentos;

  if (argc < 2){
    srand(1);
    lanzar_motor_grafico(argc, argv);
  }
  else {
    srand(atoi(argv[1]));
    argumentos.ubicacion_mapa = argv[1];
    if (!fileExists(argumentos.ubicacion_mapa)){
      std::cout << "El mapa no existe\n";
      exit(1);
    }
    argumentos.semilla = atoi(argv[2]);
    argumentos.level = atoi(argv[3]);
    argumentos.fil_inicial = atoi(argv[4]);
    argumentos.col_inicial = atoi(argv[5]);
    argumentos.ori_inicial = atoi(argv[6]);
    int i = 7;

    lanzar_motor_grafico_verOnline(argc, argv, argumentos);
  }

  exit(EXIT_SUCCESS);
}
