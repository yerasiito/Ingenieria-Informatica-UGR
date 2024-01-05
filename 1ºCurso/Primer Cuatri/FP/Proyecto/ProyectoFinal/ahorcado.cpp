/*
  Autores: Don Oreo y el compa mamado
  Fecha: Enero-2020
 */

//Juego del ahorcado

#include<iostream>
#include<string>
#include <stdlib.h>
#include <time.h>

using namespace std;

void Separador(){
   cout << "\n";
   for(int i = 0; i < 25; i++)
      cout << "*";
}

//Crea un minijuego donde hay que introducir letras para acertar una palabra aleatoria

class Ahorcado{

/*
  El formato del juego es:

   _ _ _ _ _ _ //Cada raya representa una letra de la palabra a acertar

   Nº de intentos:_
*/

private:
	string inicial, palabra, car_introducidos;
   int intentos = 5, tamanio;

public:
   //Para quitar los "warnings". Esto no es estrictamente necesario hacerlo
   Ahorcado()
   :inicial(""),palabra(""),car_introducidos(""),tamanio(0)
   {
   }

   //Toma la palabra a acertar de la clase bolsa
	void SeleccionarPalabra(string candidato){
   	palabra = candidato;
   	tamanio = palabra.size();
   }

   //Inicia la partida
   string Inicio(){
      /*Inicializa todos las variables que se usaran en la partida
        Crea la plantilla inicial con los guiones necesarios
      */
      intentos = 5;
      inicial = "";
      car_introducidos = "";
      for(int i = 1; i <= tamanio ; i++)
         inicial.push_back('_');

	return inicial;
   }

   /*Metodos que devuelven los valores de los miembros de la clase*/

   string Inicial(){
      return inicial;
   }

   string Palabra(){
      return palabra;
   }

   string Car_Introducidos(){
      return car_introducidos;
   }

   int Intentos(){
      return intentos;
   }

   /*Metodos que imprimen el estado actual del juego*/

   void ImprimeInicial(int num_partida){
		cout << "\nPartida " << num_partida << endl;

      for(int i = 0; i < tamanio; i++)
         if(palabra[i] != ' ')
            cout << inicial[i] << " ";
         else
            cout << "\t";

		cout << endl;
   }

   void ImprimeLetrasIntroducidas(){
      cout << car_introducidos << endl;
   }

   /*Metodos para comprobar la validez del caracter introducido*/

   bool LetrasIntroducidas(char car){
	   bool introducida;

		if(car_introducidos.find(car) <= car_introducidos.size())
         introducida = true;
      else{
         car_introducidos.push_back(tolower(car));
         car_introducidos.push_back(toupper(car));
      }

      return introducida;
   }

   bool EsLetra(char car){
      bool esletra = false;
      if ((car >= 'A' && car <= 'Z') || (car >= 'a' && car <= 'z') || car == 'ñ'){
         esletra = true;
      }

      return esletra;
   }

   //Actualiza el estado de la partida segun el caracter introducido por el jugador
   void Ronda(char car){
		bool encontrado = false, introducido = false, es_valido;
      int pos_letra = 0;
      es_valido = EsLetra(car);

		if(es_valido)
         introducido = LetrasIntroducidas(car);

		while(pos_letra < tamanio && es_valido){
         if(tolower(car) == palabra[pos_letra] || toupper(car) == palabra[pos_letra]){
            inicial[pos_letra] = palabra[pos_letra];
            encontrado = true;
         }
         pos_letra++;
      }

      //En nuestro caso, NO penalizaremos si la letra ya habia sido introducida o no era válida
		if(es_valido && !encontrado && !introducido){
         intentos--;
         cout << "No está!";
      }

      if(es_valido && introducido)
         cout << "La letra ya ha sido introducida";

      if(!es_valido)
         cout << "No es una letra!";

   }

   /*Métodos que comprueban el estado final de la partida*/

   bool Victoria(){
      bool win = true;

      for(int i = 0; i < tamanio && win; i++){
         if(palabra[i] == ' ')
            i++;
         if(inicial[i] != palabra[i])
            win = false;
      }

   return win;
   }

   bool Derrota(){
      bool game_over = false;

      if(intentos == 0)
         game_over = true;


   return game_over;
   }

};

class Bolsa{

private:
	static const int TAMANIO = 76;
	string palabras[TAMANIO] = {
	   "caballero",  "Dulcinea",   "historia",   "escudero",
		"Rocinante",  "adelante",   "gobernador", "andantes",
      "voluntad",   "capitulo",   "menester",   "doncella",
      "caballeria", "castillo",   "Fernando",   "finalmente",
      "aventura",   "hermosura",  "palabras",   "gobierno",
      "intencion",  "cardenio",   "pensamientos", "Luscinda",
      "lagrimas",   "aposento",   "aventuras",  "quisiera",
      "libertad",   "desgracia",  "entendimiento", "pensamiento",
      "licencia",   "Mercedes",   "semejantes", "silencio",
      "valeroso",   "doncellas",  "labrador",   "caballerias",
      "cristiano",  "cristianos", "discreto",   "hicieron",
      "llegaron",   "quisiere",   "espaldas",   "muestras",
      "escuderos",  "discurso",   "grandeza",   "altisidora",
      "princesa",   "haciendo",   "renegado",   "provecho",
      "quedaron",   "resolucion", "presente",   "encantadores",
      "enamorado",  "valiente",   "encantado",  "molino",
      "licenciado", "necesidad",  "responder",  "discrecion",
      "ejercicio",  "hacienda",   "posadero",   "rocinantes",
      "presencia",  "historias",  "presentes",  "verdadero"
      };

/*   Nota:Rocinante = rocinante en nuestro codigo ya que segun la linea 31-32, el codigo debe aceptar mayusculas y minusculas
     Por tanto, hemos cambiado Rocinante por rocinantes para evitar una repeticion inesperada de esta palabra
*/

	string vector_aleatorio[TAMANIO];
	int num_generados[TAMANIO];

public:
   Bolsa()
   //Barajamos la bolsa cada vez que creamos un objeto bolsa
   {
      Barajar();
   }

   //Genera un vector aleatorio con las palabras de la bolsa
	void Barajar(){
	   int num_aleatorio;
      bool ya_generado = true;

      srand(time(NULL)); //Inicializa la funcion random

      for(int i = 0; i < TAMANIO; i++){
         while(ya_generado){
            ya_generado = false;
            num_aleatorio = rand () % TAMANIO;
            for(int j = 0; j < i+1 && !ya_generado; j++)
               if(num_aleatorio == num_generados[j])
                  ya_generado = true;
         }
         vector_aleatorio[i] = palabras[num_aleatorio];
         num_generados[i] = num_aleatorio;
         ya_generado = true;
      }
      //Muestra el vector aleatorio en pantalla. Solo uso de depuracion
      //for( int i = 0; i < TAMANIO; i++)
      //   cout << vector_aleatorio[i] << endl;
	}

	//Devuelve una palabra del vector aleatorio segun la posicion
	string Seleccionar_palabra(int pos){
	   while(pos>=TAMANIO)
         pos-=TAMANIO-1;

		return vector_aleatorio[pos];
	}

	int Tamanio(){
      return TAMANIO;
	}


};

int main(){

	bool victoria = false, derrota = false;
	char confirmacion, car;

   cout << "\nJuego del Ahorcado." << endl;

   Ahorcado juego;
   Bolsa bolsa;

	int partidas;

	cout << "\nIntroduzca el número de partidas que desea jugar: ";
	cin >> partidas;

	for(int i = 0; i < partidas && !derrota; i++){
      victoria = false;

		juego.SeleccionarPalabra(bolsa.Seleccionar_palabra(i)),juego.Inicio(), juego.ImprimeInicial(i);

		while(!victoria && !derrota){
      cout << "\n\nQuedan " << juego.Intentos() << " intentos";
      cout << endl << "\nIntroduce una letra: ";
      cin >> car;

		juego.Ronda(car), juego.ImprimeInicial(i);

      victoria = juego.Victoria();
      derrota = juego.Derrota();

      Separador();
   	}
      if(victoria)
         cout << endl << "HAS GANADO!" << endl;

   	if (derrota){
   		cout << endl << "HAS PERDIDO!" << endl;
   		cout << endl << "La palabra era: " << juego.Palabra() << endl;
   	}

      if(i % (bolsa.Tamanio() - 1) == 0 && i !=0){
         //Si bolsa es recorrida completamente tienes dos opciones:
         //-Seguir jugando barajando la bolsa otra ver
         //-Salir del juego

         cout << "\n¿Quieres seguir jugando? Se volverá a barajar la bolsa con las mismas palabras\n"
              << "Escribe Y/y para seguir, N/n para salir." << endl;

         while(confirmacion != 'y' && confirmacion != 'n'){
            cin >> confirmacion;
            confirmacion = tolower(confirmacion);
         }

         if(confirmacion == 'y')
            bolsa.Barajar();
         else
            derrota = true;

         confirmacion = ' ';
      }
   }

   return 0;
}
