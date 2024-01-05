/**
  * @file ahorcado.cpp
  * @brief Programa para jugar al ahorcado en consola
  *
  * @author Yeray López Ramírez y Mario Guisado García
  * @date Enero-2020
  *
  * El programa implementa una versión básica del juego del ahorcado como
  * ejercicio de uso de clases simples.
  *
  * El objetivo que se pretende es programar el juego en base a una clase "Ahorcado"
  * que resuelva las operaciones que se tienen que realizar. El programa principal
  * deberá declarar un objeto de esta clase y llamar a los distintos métodos hasta
  * el final de la partida.
  *
  * Para hacerse una idea de qué componentes formarán parte de la clase:
  *
  * - Un objeto de esta clase, deberá tener información sobre:
  *    - La frase o palabra que hay que acertar.
  *    - La plantilla con el estado actual de la partida (la palabra con guiones).
  *    - El número de intentos que quedan.
  *    - Las letras que ya se han dicho hasta el momento.
  *
  * - Para que la clase controle el proceso de la partida, deberá tener operaciones para:
  *    - Consultar el estado actual de la plantilla (la cadena de letras/guiones actual)
  *    - Consultar el número de intentos que quedan.
  *    - Consultar la cadena de letras que ya se han usado.
  *    - Saber si la partida se ha terminado.
  *    - Saber si una letra se puede decir o no.
  *    - Saber si se ha ganado la partida.
  *    - Procesar una nueva letra seleccionada por el jugador, teniendo en cuenta que si
  *      se da en mayúscula también debe funcionar. La función devolverá si se ha procesado
  *      correctamente, es decir, si la letra tenía sentido y no se había usado antes. Por
  *      ejemplo, si le da un carácter que no es una letra no se puede procesar.
  *
  * Para hacer el programa más interesante, el juego debería "inventarse" una palabra. Para
  * resolver esto, creamos una clase con la responsabilidad de seleccionar una palabra
  * aleatoria. El diseño que se propone es crear una nueva clase "Bolsa" que nos hace de
  * generador aleatorio.
  *
  * Para hacerse una idea de qué componenetes formarán parte de la clase, tenga en cuenta
  * que deberá tener múltiples palabras y nos debería permitir "sacar palabras" en un orden
  * arbitrario. Para ello, puede considerar
  *     - Deberá contener un vector privado con las palabras que hay en la bolsa.
  *     - El constructor debería cargar ese vector privado con múltiples palabras en un
  *       orden aleatorio.
  *     - Debería tener un método para seleccionar una nueva palabra.
  *
  * Ya que es una bolsa, podemos realizar el siguiente comportamiento:
  *     - Cuando se declara un objeto de la bolsa, se cargan las palabras y se barajan.
  *     - Se puede pedir la siguiente palabra, dando lugar a una secuencia de palabras que
  *       surgen con un orden aleatorio según hayan quedado ordenadas al construir la bolsa.
  *     - Si se llegan a pedir todas las palabras, pedir la siguiente palabra implicará volver
  *       a barajar la bolsa y comenzar con la primera de ellas.
  *
  * Para simplificar el problema sin entrar en soluciones que impliquen pedir palabras desde
  * cin, puede declarar un vector con un contenido predeterminado en el constructor y que nos
  * permite inicializar la bolsa. Si quiere, puede usar:
  *       "caballero",  "Dulcinea",   "historia",   "escudero",
  *       "rocinante",  "adelante",   "gobernador", "andantes",
  *       "voluntad",   "capitulo",   "menester",   "doncella",
  *       "caballeria", "castillo",   "Fernando",   "finalmente",
  *       "aventura",   "hermosura",  "palabras",   "gobierno",
  *       "intencion",  "cardenio",   "pensamientos", "Luscinda",
  *       "lagrimas",   "aposento",   "aventuras",  "quisiera",
  *       "libertad",   "desgracia",  "entendimiento", "pensamiento",
  *       "licencia",   "Mercedes",   "semejantes", "silencio",
  *       "valeroso",   "doncellas",  "labrador",   "caballerias",
  *       "cristiano",  "cristianos", "discreto",   "hicieron",
  *       "llegaron",   "quisiere",   "espaldas",   "muestras",
  *       "escuderos",  "discurso",   "grandeza",   "altisidora",
  *       "princesa",   "haciendo",   "renegado",   "provecho",
  *       "quedaron",   "resolucion", "presente",   "encantadores",
  *       "enamorado",  "valiente",   "encantado",  "molino",
  *       "licenciado", "necesidad",  "responder",  "discrecion",
  *       "ejercicio",  "hacienda",   "posadero",   "Rocinante",
  *       "presencia",  "historias",  "presentes",  "verdadero"
  *
  * Observe que una vez que tenga las dos clases, puede declarar una bolsa de palabras y después
  * inicializar un objeto de la clase Ahorcado con una palabra aleatoria, ya que la palabra se pide
  * al objeto "Bolsa".
  *
  * Para programar el juego, puede definir la clase "Ahorcado" e inicializar el objeto con una palabra
  * fija y conocida (por ejemplo, en el constructor). Una vez que ya lo ha depurado y obtenido
  * una solución que funciona, puede añadir la clase bolsa y crear un programa que juega varias
  * partidas del ahorcado.
  *
  * En concreto, el programa pedirá cuántas palabras quiere adivinar y repetirá el juevo con un
  * bucle que permita al usuario jugar varias partidas. Note que declarará una Bolsa al principio del
  * main y el bucle que repite las partidas pedirá a dicha bolsa una nueva palabra para cada nueva partida.
  *
  */

//Juego del ahorcado

#include<iostream>
#include<string>
#include<cstdlib>
#include <stdlib.h>
#include <time.h>

using namespace std;

void Separador(){
   cout << "\n";
   for(int i = 0; i < 25; i++)
      cout << "*";
}

class Ahorcado{
private:
   
	string inicial, palabra, car_introducidos;
   int intentos = 5, tamanio;
   
public:
   
	void SeleccionarPalabra(string candidato){
   	palabra = candidato;
   	tamanio = palabra.size() + 1;
   }

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
   
   void ReiniciarIntentos(){
   	intentos = 5;
   }

   string Inicio(){
      for(int i = 1; i <= tamanio ; i++)
         inicial.push_back('_');
	
	return inicial;
   }

   void ImprimeInicial(){
      
		cout << endl;
      
		for(int i = 0; i <= tamanio; i++)
   		cout << inicial[i] << " ";
     
		cout << endl;
   }

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
      bool esletra;
      if  ((car >= 'A' && car <= 'Z') || (car >= 'a' && car <= 'z') )
         esletra = true;
      return esletra;
   }

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
      
		if(!encontrado && !introducido && es_valido){
         intentos--;
         cout << "No está!";
      }
      if(!es_valido)
         cout << "No es una letra!";
      if(introducido)
         cout << "La letra ya ha sido introducida";
   }

   bool Victoria(){
      bool win = true;
      for(int i = 0; i < tamanio && win; i++)
         if(inicial[i] != palabra[i])
            win = false;

      if(win)
         cout << endl << "HAS GANADO!";

   return win;
   }

   bool Derrota(){
      bool game_over;

      if(intentos == 0){
         game_over = true;
         cout << endl << "HAS MUERTO" << endl;
      }
   return game_over;
   }

};

class Bolsa{	

private:
	string palabras[76] =  { "Dulcinea",   "historia",   "escudero",
		"rocinante",  "adelante",   "gobernador", "andantes",
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
      "ejercicio",  "hacienda",   "posadero",   "rocinante",
      "presencia",  "historias",  "presentes",  "verdadero" };
   
	string palabra_seleccionada;
	int numero_aleatorio;
   
public:	
	
	void PalabraAleatoria(){
		numero_aleatorio = rand () % 75;
		palabra_seleccionada = palabras[numero_aleatorio];
	}
	
	string GetPalabra(){
		return palabra_seleccionada;
	}	
	
};

int main(){
   
	bool victoria = false, derrota = false;
   char car;

   cout << "\nJuego del Ahorcado." << endl;

   Ahorcado juego1;
	Bolsa bolsa1;

	int partidas;
	
	cout << "\nIntroduzca el número de partidas que desea jugar: ";
	cin >> partidas;
	
	srand(time(NULL));
	
	for(int i = 0; i < partidas; i++){
	
		bolsa1.PalabraAleatoria();
		juego1.SeleccionarPalabra(bolsa1.GetPalabra()), juego1.Inicio(), juego1.ImprimeInicial();
		
		while(!victoria && !derrota){
		
      cout << "\n\nQuedan " << juego1.Intentos() << " intentos";
      cout << endl << "\nIntroduce una letra: ";
      cin >> car;
      
		juego1.Ronda(car), juego1.ImprimeInicial();

      victoria = juego1.Victoria();
      derrota = juego1.Derrota();

      Separador();
   	}
   	
   	if (derrota)
   		i = partidas;
   	else{
   		juego1.ReiniciarIntentos();
   		victoria = false;
   	}
   	
   }

}
































