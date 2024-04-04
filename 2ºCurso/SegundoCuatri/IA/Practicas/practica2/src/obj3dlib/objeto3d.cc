#include "obj3dlib/objeto3d.h"
#include "obj3dlib/file_ply_stl.h"
#include <iostream>


/* Constructores y Destructores*/

Objeto3D::Objeto3D(std::string archivo){
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

  for (unsigned i=0;i<carAux.size();i+=3){
    caras.push_back( _vertex3<unsigned int> (carAux[i],carAux[i+1],carAux[i+2]));
  }

  calcularNormales();
  tieneMalla = true;
}

Objeto3D::Objeto3D(const Objeto3D& objeto){
  posicion = objeto.posicion;
  colores = objeto.colores;

  vertices = objeto.vertices;
  caras = objeto.caras;

  normalCaras = objeto.normalCaras;
  normalVertices = objeto.normalVertices;

  transformaciones = objeto.transformaciones;

  hijos = objeto.hijos;

  matAmb = objeto.matAmb;
  matSpec = objeto.matSpec;
  matDiff = objeto.matDiff;

  tieneMalla = objeto.tieneMalla;

}


/*Funciones privadas auxiliares*/

void Objeto3D::calcularNormales(){

    _vertex3 <float> p,q,r, aux1, aux2, normal;
    float modulo;

    /* Creacion de variables auxiliares usadas para generar los vectores de Normales
            Calculamos la normal N = (q-p)x(r-q)
            usaremos aux1 y aux2  para guardar las restas parciales antes de calcular el producto escalar
            Guardaremos el resultado en la variable "normal" para su posterior tratamiento

            La variable modulo es otra variable auxiliar que usaremos para calcular el modulo de la normal para normalizar esta

    */

    normalVertices.resize(vertices.size()); //Ponemos el tamaño correcto a normalVertices antes de empezar su tratamiento

    for (unsigned i = 0; i<caras.size();i++){ //Para todas las caras
        p = vertices[caras[i]._0]; //Inicializamos las variables auxiliares
        q = vertices[caras[i]._1];
        r = vertices[caras[i]._2];

        aux1 = q - p; //Restamos
        aux2 = r -q;

        normal =aux1.cross_product(aux2); //Calculamos el producto escalar y lo asignamos a la normal

        modulo = normal.module(); //Calculamos su modulo
        normal = normal/modulo; //Normalizamos
        normalCaras.push_back(normal); //Incluimos en la coleccion

        /* Para cada uno de los 3 vertices de cada cara
          Sumamos la normal de la cara a la normal de cada vertice
        */

        normalVertices[caras[i]._0].x+=normal.x;
        normalVertices[caras[i]._0].y+=normal.y;
        normalVertices[caras[i]._0].z+=normal.z;

        normalVertices[caras[i]._1].x+=normal.x;
        normalVertices[caras[i]._1].y+=normal.y;
        normalVertices[caras[i]._1].z+=normal.z;

        normalVertices[caras[i]._2].x+=normal.x;
        normalVertices[caras[i]._2].y+=normal.y;
        normalVertices[caras[i]._2].z+=normal.z;

    }

    //Y normalizamos los vertices...
    for (unsigned i = 0; i< normalVertices.size(); i++){
        modulo = normalVertices[i].module();
        normalVertices[i] = normalVertices[i]/modulo;
    }

     /*Muestra por pantalla de las normales
    for (unsigned i = 0; i< normalVertices.size(); i++){
        cout << normalVertices[i].x << " " <<normalVertices[i].y << " " <<normalVertices[i].z << " " <<endl;
    } */



}

void Objeto3D::transformar(){
    int aux;
    glMatrixMode(GL_MODELVIEW);
    for(unsigned i = 0; i<transformaciones.size(); i++){
        aux = transformaciones[i].x;
        switch(aux){
        case 1:
            glTranslatef(transformaciones[i]._1,transformaciones[i]._2,transformaciones[i]._3);
            break;
        case 2:
            glScalef(transformaciones[i]._1,transformaciones[i]._2,transformaciones[i]._3);
            break;
        case 3:
            if (transformaciones[i]._1 == 0.0){
                glRotatef(transformaciones[i]._2,1,0,0);
            }
            if (transformaciones[i]._1 == 1.0){
                glRotatef(transformaciones[i]._2,0,1,0);
            }
            if (transformaciones[i]._1 == 2.0){
                glRotatef(transformaciones[i]._2,0,0,1);
            }
            break;
        }
    }

}

void Objeto3D::drawSolido(){
  glColor3f(colores.x,colores.y,colores.z);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);

  glDrawElements(GL_TRIANGLES, caras.size()*3, GL_UNSIGNED_INT, &caras[0]);
}

void Objeto3D::drawSuave(){
  glShadeModel(GL_SMOOTH);
  GLfloat ambient[4]={matAmb.x,matAmb.y,matAmb.z,matAmb.w};
  GLfloat diffuse[4]={matDiff.x,matDiff.y,matDiff.z,matDiff.w};
  GLfloat specular[4]={matSpec.x,matSpec.y,matSpec.z,matSpec.w};
  glMaterialfv(GL_FRONT,GL_AMBIENT,(GLfloat *) &ambient);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,(GLfloat *) &diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR,(GLfloat *) &specular);
  glMaterialf(GL_FRONT,GL_SHININESS,10);


  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);

  glEnableClientState(GL_NORMAL_ARRAY);
  glNormalPointer(GL_FLOAT,0, &normalVertices[0]);

  glDrawElements(GL_TRIANGLES, caras.size()*3, GL_UNSIGNED_INT, &caras[0]);
}


/*Funciones publicas*/
void Objeto3D::draw(int modo){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(posicion.x, posicion.y, posicion.z);
    if (!transformaciones.empty()){
        transformar();
    }
    if(!hijos.empty()){
        for(unsigned i = 0; i<hijos.size(); i++){
            hijos[i]->draw(modo);
        }
    }

    if(tieneMalla != false){
        switch(modo){
            case 1:
            drawSolido();
            break;

            case 2:
            drawSuave();
            break;

        }
    }
    glPopMatrix();
}
