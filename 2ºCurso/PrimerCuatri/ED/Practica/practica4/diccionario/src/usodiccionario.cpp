/**
 * @file usodiccionario.cpp
 * @author Yeray Lopez Ramirez
 * @date Diciembre de 2021
 * @brief Archivo de ejemplo para probar el TDA diccionario. Se ejecuta ./usodiccionario < archivodeentrada o escribiendo los datos a mano(mas engorroso esta ultima)
 */

#include <iostream>
#include "diccionario.h"

//COMANDO EJECUCION: ./usodiccionario < ../datos/data.txt

/**
 * @brief Operator<<. Obsérvese el uso de 2 tipos diferentes de iteradores. Uno sobre
 * listas de listas y otro sobre listas
 * @param os El operador de salida
 * @param D El diccionario a escribir
 * @return os La salida estandar
*/
ostream & operator<<(ostream & os, const Diccionario<string,string> & D){
	  
	  list<data<string,string> >::const_iterator it;
	  
	  for (it=D.begin(); it!=D.end(); ++it){
	  
		    list<string>::const_iterator it_s;
		    
		    os<<endl<<(*it).clave<<endl<<" informacion asociada:"<<endl;
		    for (it_s=(*it).info_asoci.begin();it_s!=(*it).info_asoci.end();++it_s){
			      os<<(*it_s)<<endl;
		    }
		    os<<"**************************************"<<endl;
	  }
	  
	  return os;
}

/**
 * @brief Operator >>. El formato de la entrada es:
 * numero de claves en la primera linea
 * clave-iésima retorno de carro
 * numero de informaciones asociadas en la siguiente linea
 * y en cada linea obviamente la informacion asociada
 * @param is El operador de entrada
 * @param D El diccionario a leer
 * @return is La entrada estandar
*/
istream & operator >>(istream & is,Diccionario<string,string> &D){
	  int np;
	  is>>np;
	  is.ignore();//quitamos \n
	  Diccionario<string,string> Daux;
	  for (int i=0;i<np; i++){
		    string clave;

		    getline(is,clave); 
		    
		    int ns;
		    is>>ns; 
		    is.ignore();//quitamos \n
		    list<string>laux;
		    for (int j=0;j<ns; j++){
			      string s;
			      getline(is,s);
			      
			      // cout<<"Significado leido "<<s<<endl;
			      laux.insert(laux.end(),s);
		    }
		    Daux.Insertar(clave,laux);		      
		    
	  }
	  D=Daux;
	  return is;
}

/**
 *@brief Recorre la lista de información asociada a una clave y la imprime
 * @param l La lista de definiciones
 */
void EscribeSigni(const list<string>&l){		 
	  list<string>::const_iterator it_s;
	  for (it_s=l.begin();it_s!=l.end();++it_s){
		    cout<<*it_s<<endl;
	  }
}	

/**
 * @brief separa las salidas de texto para una mejor lectura
 */
void separador(){
    for(int i = 0; i < 100; i++)
        cout << "=";
    cout << endl;
}

/**
 * @brief Lee un diccioario e imprime datos asociados a una clave.
 * Hay un fichero ejemplo de prueba: data.txt.Para lanzar el programa con ese fichero se escribe
 * ./usodiccionario < data.txt
*/
int main(){
    //Diccionario 1
    Diccionario<string,string> D1;
    cin>>D1;
    cout << "Diccionario 1:" << endl;
    cout<<D1;

    if(D1.size() == 0)
        cout << "El diccionario 1 esta vacio" << endl;
    //Diccionario 2
    separador();
    Diccionario<string,string> D2;
    cin>>D2;
    cout << "Diccionario 2:" << endl;
    cout<<D2;

    if(D2.size() == 0)
        cout << "El diccionario 2 esta vacio" << endl;
    //removePalabra: elimina una palabra del diccionario
    separador();
    cout << "Palabra a eliminar del Diccionario 1:" << endl;
    string a;
    cin>>a;
    D1.removePalabra(a);
    cout << "Diccionario despues de borrar " << a << endl;
    cout << D1;

    //operator+: une dos diccionarios
    separador();
    cout << "La union de los dos diccionarios es " << endl;
    Diccionario<string,string> D3 = D1+D2;
    cout << D3;

    //getDiccionarioEntreClaves: Devuelve elementos entre dos claves
    separador();
    cout << "Escribes las 2 claves entre las que buscar" << endl;
    string clave1, clave2;
    cin >> clave1 >> clave2;
    cout << "Los elementos entre las claves '" << clave1 << "' y '" << clave2 <<
        "' en el diccionario fusionado es:" << endl;
    Diccionario<string,string> DEntreClaves = D3.getElementosEntreClaves(clave1,clave2);
    cout << DEntreClaves << endl;

    /* //Para borrar definiciones. Funcion extra "accidental"
    string b;

    cout<<"Introduce una palabra"<<endl;
    cin>>b;

    //Borra las definiciones de una palabra
    //D1.removeSignificados_Palabra(b);

    /*
    list<string>l=D1.getInfo_Asoc(b);

    //Imprime las definiciones de una palabra
    cout << "Las definiciones de " << b << " son:" << endl;
    if (l.size()>0)
        EscribeSigni(l);
    */
}

