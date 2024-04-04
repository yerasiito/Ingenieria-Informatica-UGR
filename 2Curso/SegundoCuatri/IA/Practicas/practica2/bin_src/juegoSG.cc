#include "motorlib.hpp"
#include <fstream>

MonitorJuego monitor;

int main(int argc, char ** argv){
  list<pair<int,int>> listo;

  if (argc <6){
    cout << "Faltan parametros..." << endl;
    cout << "Se necesita indicar: " << endl;
    cout << "1) Mapa" << endl << "2) Semilla" << endl << "3) Nivel (1, 2, 3 o 4)" << endl;
    cout << "4) Origen (F)" << endl << "5) Origen (C)" << "6) Orientacion " << endl;
    cout << "7) Destino (F)" << endl << "8) Destino (C)" << endl;
    cout << "...) Destino (F)" << endl << "...) Destino (C)" << endl;
  }
  else {
    // 1 -> mapa
    // 2 -> semilla
    // 3 -> nivel
    // 4,5 -> origen
    // 6 -> origentacion (0= norte, 1=este, 2=sur, 3=oeste)
    // 6,7 -> destino1
    // 8,9 -> destino2
    // ...
    monitor.setMapa(argv[1]);
    monitor.startGame(atoi(argv[3]));

    ifstream ifile;
    ifile.open(argv[1], ios::in);

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
    // Reviso si es una posicion valida
    if (atoi(argv[4])!=-1){
      if (mapAux[atoi(argv[4])][atoi(argv[5])] == 'P' or mapAux[atoi(argv[4])][atoi(argv[5])] == 'M'){
	       cout << "Posicion (" << argv[4] << "," << argv[5] << ") no es de tipo válido para el jugador" << endl;
         return 0;
       }
     }

     int i = 7;



    if (argv[3] != "3"){
      while (argc > i+1) {
    // Reviso si es una posicion valida
        if (mapAux[atoi(argv[i])][atoi(argv[i+1])] == 'P' and mapAux[atoi(argv[i])][atoi(argv[i+1])] == 'M'){
          cout << "Posicion (" << argv[i] << "," << argv[i+1] << ") no es de tipo válido para el objetivo" << endl;
        }
        listo.push_back(pair<int,int>(atoi(argv[i]),atoi(argv[i+1])));
        i += 2;
      }
    }

    monitor.setListObj(listo);

    monitor.inicializar(atoi(argv[4]), atoi(argv[5]), atoi(argv[2]));
    monitor.get_entidad(0)->setOrientacion(static_cast<Orientacion>(atoi(argv[6])));
    monitor.get_entidad(0)->setBateria(3000);
    monitor.get_entidad(0)->Cogio_Bikini(false);
    monitor.get_entidad(0)->Cogio_Zapatillas(false);
    monitor.setPasos(3000);
    monitor.setRetardo(0);

    // Reviso si es una posicion valida
    //if (mapAux[atoi(argv[7])][atoi(argv[8])] == 'P' and mapAux[atoi(argv[7])][atoi(argv[8])] == 'M')
	  //   cout << "Posicion (" << argv[7] << "," << argv[8] << ") no es de tipo válido para el objetivo" << endl;

    //monitor.addObjetivo(atoi(argv[7]),atoi(argv[8]));
    //monitor.setObjFil(atoi(argv[7]));
    //monitor.setObjCol(atoi(argv[8]));



    monitor.juegoInicializado();

    lanzar_motor_juego2(monitor);
  }
  exit(EXIT_SUCCESS);
}
