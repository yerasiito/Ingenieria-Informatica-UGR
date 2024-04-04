#include "obj3dlib/objrevolucion3d.h"
#include "obj3dlib/file_ply_stl.h"
#include <cmath>
#include <GL/glut.h>

#define PI 3.14159265359

RevolucionObj3D::RevolucionObj3D(std::string archivo, unsigned nCortes) : Objeto3D(){
  _file_ply ply;
  std::vector<float> vertAux;
  std::vector<unsigned int> carAux;

  char * cstr = new char[archivo.length() + 1];
  strcpy(cstr, archivo.c_str());

  ply.open(cstr)  ;
  ply.read(vertAux, carAux);
  ply.close();
  delete [] cstr;

  for (unsigned i=0;i<vertAux.size();i+=3){
    vertices.push_back( _vertex3<float> (vertAux[i],vertAux[i+1],vertAux[i+2]));
  }

  int nElem = vertices.size(); //Obtenemos el numero inicial vertices para calcular a partir de ellos el resto


  for(float i = (1.0/nCortes); i<=1; i += (1.0/nCortes)){ //Para cada seccion de la revolucion
    for (unsigned j = 0; j < nElem; j++){ //Calculamos para cada vertice el siguiente de la seccion
      /*
      Usaremos valores entre 0 y 1 cada calcular los angulos. Multiplicaremos 2PI por una fraccion
       y conseguiremos angulos entre 0 y 360º en radianes.

       x = radio*cos(&)
       y = y
       z = radio*sen(&)

       Como rotaremos sobre el 0,0,0 el radio es igual a la componente X

     */
     vertices.push_back(_vertex3<float> ((vertices[j].x)*cos(i*(2*PI)),vertices[j].y,(vertices[j].x)*sin(i*(2*PI))));
   }
 }
 int a,b,c; //Usaremos estas 3 variables para calcular los 3 vectores de cada cara
 for(unsigned i = 0; i<nCortes; i++){ //Para cada seccion
   for (unsigned j = 0; j<(nElem-1); j++){ //Y para cada elemento del vector
     /*Calculamos las caras pares e impares del objeto

     Cara par = Vi,j | Vi,j+1 | Vi+1,j
     Cara impar = Vi,j+1 | Vi+1,j+1 | Vi+1,j

     Usaremos el %vertices.size() para evitar desbordamientos
     */

     //Cara par
     a= ((i*nElem)+j)%vertices.size();
     b=((i*nElem)+(j+1))%vertices.size();
     c= (((i+1)*nElem)+j)%vertices.size();
     caras.push_back(_vertex3<unsigned int>(a,b,c));

    //Cara impar
    a= ((i*nElem)+(j+1))%vertices.size();
    b=(((i+1)*nElem)+(j+1))%vertices.size();
    c= (((i+1)*nElem)+j)%vertices.size();
    caras.push_back(_vertex3<unsigned int>(a,b,c));
  }
}

vertices.push_back(vertices[0]);
vertices.push_back(vertices[vertices.size()-2]);

/*Calculamos las tapas(1)
  Creamos un nuevo vertice en el centro con la altura del primero de vertices iniciales y lo incluimos en la coleccion
  Despues unimos dicho vertice con el primer vertice, y sus hijos
*/
for(unsigned i = 0; i<nCortes; i++){ //Cuidado: Las tapas hay que generarlas en el orden correcto
  a = vertices.size()-2; //El vertice central es el ultimo incluido en la coleccion
  c = (i*nElem)%(vertices.size()-2); // El segundo vertice es uno de los generados a partir del primer vertice de la coleccion
  b = ((i+1)*nElem)%(vertices.size()-2); //El tercer vertice es el adyacente al anterior
  caras.push_back(_vertex3<unsigned int> (a,b,c)); //Insertamos la cara en la coleccion de caras
}


/*Calculamos las tapas(2)
  Creamos un nuevo vertice en el centro con la altura del ultimo de los vertices iniciales y lo incluimos en la coleccion
  Despues unimos dicho vertice con el ultimo de los iniciales, y sus hijos
*/
for(unsigned i = 0; i<nCortes; i++){
  a = vertices.size()-1;//Como antes, nuestro vertice es el ultimo insertado
  b = ((nElem-1)+(i*nElem))%(vertices.size()-2); //El metodo es como antes, usaremos nElem para escoger nuestro vertice y sus hijos
  c = ((nElem-1)+((i+1)*nElem))%(vertices.size()-2);
  caras.push_back(_vertex3<unsigned int> (a,b,c));
}

calcularNormales();
tieneMalla = true;

}
