/**
 * @author Yeray Lopez Ramirez
 * @date 15 de diciembre de 2021
 * @file usoguia.h
 * @brief Archivo para probar el TDA guiatlf. CUIDADO, aqui el archivo se pasa como parametro y no se redirige como en el diccionario. Ejecucion: ./usoguia archivodatos
 */
#include "guiatlf.h"
#include <fstream>
int main(int argc , char * argv[]){
   if (argc!=2){
      cout<<"Dime el nombre del fichero con la guia"<<endl;
   return 0;
   }
   ifstream f(argv[1]);
   if (!f){
      cout<<"No puedo abrir el fichero "<<argv[1]<<endl;
      return 0;
   }
   Guia_Tlf g;

   f>>g;
   cout<<"La guia insertada: " << endl << g<<endl;
   cin.clear();
   cout<<"Dime un nombre sobre el que quieres obtener el telefono[Escribe 'quit' o 'q' para no buscar]"<<endl;
   string n;
   bool seguirleyendo = true;

   getline(cin,n);
   if(n == "quit" || n == "q")
      seguirleyendo = false;
   //Busca nombre en la guia para obtener su tlf
   while (seguirleyendo){
      cout<<"Buscando "<<n<<"...."<<endl;
      string tlf = g.gettelefono(n);
      if (tlf=="")
         cout<<"No existe ese nombre en la guia"<<endl;
      else
         cout<<"El telefono es "<<tlf<<endl;

      cout<<"[Escribe 'quit' o 'q' para salir del bucle] Dime un nombre sobre el que quieres obtener el telefono"<<endl;
      getline(cin,n);
      if(n == "quit" || n == "q")
         seguirleyendo = false;
   }
   seguirleyendo = true;

   //Modifica el tlf de un contacto
   string tlf;
   cout<<"Dime un nombre y su telefono para modificarlo[Escribe 'quit' o 'q' para no modificar]:"<<endl;
   getline(cin,n);
   if(n == "quit" || n == "q")
      seguirleyendo = false;
   else
      getline(cin,tlf);

   while (seguirleyendo){
      cout<<"Modificando tlf de "<<n<<"...."<<endl;
      string tlfO = g.gettelefono(n);
      if (tlfO=="")
         cout<<"No existe ese nombre en la guia"<<endl;
      else{
         g.modificarTlf(n, tlf);
         cout<<"El telefono original era "<<tlfO<< " y ahora es " << g.gettelefono(n) << endl;
      }
      cout<<"[Escribe 'quit' o 'q' para dejar de modificar]Dime un nombre y su telefono para modificarlo:"<<endl;
      getline(cin,n);
      if(n == "quit" || n == "q")
         seguirleyendo = false;
      else
         getline(cin,tlf);
   }
   seguirleyendo = true;
   //Saca telefonos de nombres que empiezen por una letra
   Guia_Tlf entreLetras;
   char letra;
   cout << "Introduce la letra por la que buscar telefonos cuyos nombres empiecen por esa letra:[Escribe 'q' para no buscar]" << endl;
   cin.clear();
   cin >> letra;
   if(letra == 'q')
      seguirleyendo = false;
   while (seguirleyendo){
      cout<<"Buscando tlfs cuyos nombres asociados empiezan por '" << letra <<"' ...."<<endl;
      entreLetras = g.TlfsPorLetra(letra);
      if (entreLetras.size()==0)
         cout<<"No existe numeros cuyos nombres empiecen por '" << letra << "'" << endl;
      else
            cout << entreLetras << endl;
      cout<<"[Escribe 'q' para salir]Dime una letra para listar numeros cuyos nombres empiecen por esa letra:"<<endl;
      cin >> letra;
      if(letra == 'q')
         seguirleyendo = false;
   }
   //Saca telefonos entre dos nombres
   string nombre1,nombre2;
   cout << "Dime entre que nombres quieres quieres sacar la guia: " << endl;
   cin.ignore(); //Ignoramos el \n del cin anterior
   getline(cin,nombre1);
   getline(cin,nombre2);
   Guia_Tlf entreNombres = g.TelfsEntreNombres(nombre1,nombre2);
   cout << "Los telefonos entre " << nombre1 << " y " << nombre2 << " es: " << endl << entreNombres << endl;

   //Lista la guia final
   cout<<"Listando la guia resultante con iteradores:"<<endl;
   Guia_Tlf::iterator it;
   for (it=g.begin(); it!=g.end(); ++it)
      cout<<*it<<endl;

}
