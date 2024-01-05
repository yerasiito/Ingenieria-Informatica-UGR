//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////

//Interfaz Secuencia Caracteres
/*
Se quiere definir una clase SecuenciaCaracteres similar a la clase string para
manipular secuencias de caracteres (de datos de tipo char).
Esto es una secuencia de caracteres
Como dato miembro privado, se recomienda usar un vector de caracteres. Ya sabemos
que debemos reservar memoria suficiente. Supondremos que el máximo será 100. En
vez de usar el literal 100, mejor usamos una constante. En ese caso, C++ obliga a que
sea una constante estática (si aún no ha visto las constantes estáticas en clase de
Teoría, no se preocupe ya que no se le pide que el programa compile). Nos quedaría
lo siguiente:

private:
   static const int TAM = 100;
   char caracteres[TAM];
Se proponen dos alternativas para marcar el bloque del vector que se va a usar:
• Usar un terminador fijo, por ejemplo, #, al final del bloque usado. En el ejemplo
anterior, el vector caracteres contendría:
'E' 's' 't' 'o' ' ' 'e' 's' .... 'r 'e' 's' '#' ? ? .... ?
• Usar un dato miembro privado utilizados que nos diga cuántos elementos
estamos usando en cada momento. En el ejemplo anterior, utilizados valdría
35.
¿Qué opción le parece más adecuada? ¿Por qué?
El mejor es el segundo ya que el util es más manejable que el TERMINADOR
¿Qué métodos definiría para manipular la secuencia? Al menos debe definir las cabeceras de los métodos para realizar lo siguiente:
a) Método Aniade para añadir un carácter al final de la secuencia.
Tenga en cuenta que a una variable cadena de tipo string se le puede asignar
directamente cadena = "Hola". Sin embargo, eso no lo sabemos hacer por
ahora con objetos de nuestras propias clases. Por lo tanto, la única forma de
añadir caracteres a un objeto de la clase SecuenciaCaracteres sería hacerlo
de uno en uno. Así pues, llamando a un método Aniade, añadiríamos la 'H',
luego la 'o' y así sucesivamente.
b) Método Utilizados para obtener la longitud actual de la secuencia (el número
de caracteres que contiene)
c) Método Invierte para invertir la secuencia. En el ejemplo anterior, la secuencia
se quedaría en:
seretcarac ed aicneuces anu se otsE
d) Método PrimeraOcurrencia para buscar la primera ocurrencia de un carácter.
e) Método EliminaOcurrencias para eliminar las ocurrencias de un carácter.
Por ejemplo, después de eliminar el carácter 'a', la secuencia quedaría así:
Esto es un secuenci de crcteres
*/
#include <iostream>
using namespace std;

class SecuenciaCaracteres{
private:
   static const int TAMANIO = 100;
   char caracteres[TAMANIO];
   int utilizados = 0;
public:
   void Aniade(char car){
      caracteres[utilizados] = car;
      utilizados++;
   }

   int Utilizados(){
      return utilizados;
   }

   char Elemento(int posicion){
      return caracteres[posicion];
   }

   void Invierte(){
      char secuencia[TAMANIO];
      int pos;
      for(int i = 0; i <= utilizados; i++)
         secuencia[i] = caracteres[i];

      pos = 0;
      for(int j = utilizados-1; j >= 0; j--){
         caracteres[pos] = secuencia[j];
         pos++;
      }
      cout << "\n";
      for(int i = 0; i < utilizados; i++)
         cout << caracteres[i];
   }

   int PrimeraOcurrencia(char car){
      bool encontrado = 0;
      int pos_ocurrencia = -1;
      for(int i = 0; i < utilizados && ! encontrado; i++){
         if(caracteres[i] == car){
            pos_ocurrencia = i+1;
            encontrado = true;
         }
      }
   return pos_ocurrencia;
   }
   void EliminaOcurrencias(char a_borrar){
      char secuencia[TAMANIO];
      int pos;

      pos = 0;
      for(int i = 0; i < utilizados; i++){
         if(caracteres[i] != a_borrar ){
            secuencia[pos] = caracteres[i];
            pos++;
         }
      }
      utilizados = pos;
      cout << "\n";
      for(int i = 0; i < utilizados; i++){
         caracteres[i] = secuencia[i];
         cout << caracteres[i];
      }
   }

   void ImprimeSecuencia(){
      for(int i=0; i<utilizados; i++)
         cout << caracteres[i];
   }

};

int main(){

   SecuenciaCaracteres Prueba;

   Prueba.Aniade('H');
   Prueba.Aniade('o');
   Prueba.Aniade('l');
   Prueba.Aniade('a');

   Prueba.ImprimeSecuencia();

   Prueba.EliminaOcurrencias('H');

   return 0;
}
