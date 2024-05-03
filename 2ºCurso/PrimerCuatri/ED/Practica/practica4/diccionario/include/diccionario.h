/**
 * @author Yeray Lopez Ramirez
 * @date 15 de diciembre de 2021
 * @file diccionario.h
 * @brief TDA diccionario. Es un .h pero funciona como .cpp
 */
#ifndef _DICCIONARIO_H
#define _DICCIONARIO_H

#include <iostream>
#include <string>
#include <list>
using namespace std;

/**
 * @brief Tipo elemento que define el diccionario. T es el tipo de dato asociado a una clave que
 * no se repite (DNI p.ej.) y list<U> es una lista de datos (string p.ej) asociados a la clave
 * de tipo T. El diccionario está ordenado de menor a mayor clave.
*/
template <class T,class U>
struct data{
    T clave;
    list<U> info_asoci;
 };

 
 /**
  * @brief Comparador de datos. Ordena 2 registros de acuerdo a la clave de tipo T. Puede usarse como
  * un funtor.
 */
template <class T, class U>
bool operator< (const data<T,U> &d1,const data <T,U>&d2){
	   if (d1.clave<d2.clave)
		     return true;
	   return false;
}	   

/**
 * @brief Un diccionario es una lista de datos de los definidos anteriormente. Cuidado porque se
 * manejan listas de listas. Se añaden 2 funciones privadas que hacen más facil la implementación
 * de algunos operadores o funciones de la parte pública. Copiar copia un diccioario en
 * otro y borrar elimina todos los elementos de un diccionario. La implementación de copiar
 * puede hacerse usando iteradores o directamente usando la función assign.
*/
template <class T,class U>
class Diccionario{
	  private:
		    
		  
 		    list<data<T,U> > datos;
		    
		    void Copiar(const Diccionario<T,U>& D){
			   /*typename list<data<T,U> >::const_iterator it_d;
			   typename list<data<T,U> >::iterator it=this->datos.begin();*/
			   
			   datos.assign(D.datos.begin(),D.datos.end());
			   /*for (it_d=D.datos.begin(); it_d!=D.datos.end();++it_d,++it){
				     this->datos.insert(it,*it_d);
				     
			   }*/
		    }
		    
		    void Borrar(){
			       
			      this->datos.erase(datos.begin(),datos.end());
		    }	      
			   
			       
	  public:
         /**
          *@brief Constructor por defecto
          */
		 Diccionario():datos(list<data<T,U> >()){}
		 
		 /**
          * @brief Constructor de copias
          * @param D Diccionario a copiar
          */
		 Diccionario(const Diccionario &D){
			   Copiar(D);
		 }
		 
		 /**
          * @brief Destructor
          */
		 ~Diccionario(){}
		 
		 /**
          * @brief Operador de asignación
          * @param D Diccionario a ser asignado
          * @return this el propio objeto
          */
		 Diccionario<T,U> & operator=(const Diccionario<T,U> &D){
			   if (this!=&D){
				     Borrar();
				     Copiar(D);
			   }
			   return *this;
		 }
		
		/**
         *@brief Busca la clave p en el diccionario. Si está devuelve un iterador a
         * dónde está clave. Si no está, devuelve end() y deja el iterador de salida
         * apuntando al sitio dónde debería estar la clave
         * @param p La palabra a buscar
         * @param it_out El iterador de salida que apunta al struct 'data' donde se
         * encuentre la palabra pasada por parametro
         * @return true si la encuentra, false si no la encuentra
		*/
		bool Esta_Clave(const T &p, typename  list<data<T,U> >::iterator &it_out){
			  
			  if (datos.size()>0){
				    
			      typename list<data<T,U> >::iterator it;
			      
			      for (it=datos.begin(); it!=datos.end() ;++it){
					if ((*it).clave==p) {
						  it_out=it;
						  return true;
					}
					else if ((*it).clave>p){
						  it_out=it;
						  return false;
					}	  
					   
			      }
			      
			      it_out=it;
			      return false;
			  }
			  else {	
				    it_out=datos.end();
				    return false;
			  }	    
		 }
		 
		 /**
          *@brief Inserta un nuevo registro en el diccionario. Lo hace a través de la clave
          * e inserta la lista con toda la información asociada a esa clave. Si el
          * diccionario no estuviera ordenado habría que usar la función sort()
          * @param clave La palabra a insertar
          * @param info La lista de definiciones a insertar
         */
		 void Insertar(const T& clave,const list<U> &info){
			   
		     typename list<data<T,U> >::iterator it;
		     
		     if (!Esta_Clave(clave,it)){
			       data<T,U> p;
			       p.clave = clave;
			       p.info_asoci=info;
			 
			       datos.insert(it,p);
			      	 
		     }
		     
		 }
		 
		 /**
          * @brief Añade una nueva informacion asocida a una clave que está en el diccionario.
          * la nueva información se inserta al final de la lista de información.
          * Si no esta la clave la inserta y añade la informacion asociada.
          * @param s La definicion a añadir
          * @param clave La palabra a la que queremos añadir la definicion @c s
		 */
		 void AddSignificado_Palabra(const U & s ,const T &clave){
			   typename list<data<T,U> >::iterator it;
			   
			   if (!Esta_Clave(clave,it)){
                    data<T,U> p;
			        p.clave = clave;
				    datos.insert(it,p);
			   }
			   
			    //Insertamos el siginificado al final
		           (*it).info_asoci.insert((*it).info_asoci.end(),s);
		 }
		 
        /**
         * @brief Elimina todos los significados de una palabra a partir de la clave
         * Funcion extra "accidental" en el proceso de removePalabra
         * @param clave La palabra a la que borrar todas sus definiciones, sin borrar la palabra
         * @return true si borra las definiciones, false en otro caso
         */
		bool removeSignificados_Palabra(const T & clave){
            bool borrados = false;
            typename list<data<T,U> >::iterator it;
            cout << "Va a borrar las definiciones de " << clave << ":" << endl;
				if (Esta_Clave(clave,it)){
					(*it).info_asoci.clear();
                    borrados = true;
                }

            return borrados;
		}

		/**
         * @brief Elimina la palabra y sus definiciones del diccionario
         * @param clave La palabra a eliminar
         * @return true si borra la palabra, false si no existe
         */
		bool removePalabra(const T & clave){
            bool borrada = false;
            typename list<data<T,U> >::iterator it;
            if(Esta_Clave(clave,it)){
                datos.erase(it);
                borrada = true;
            }
            return borrada;
        }

        /**
         * @brief Une dos diccionarios devolviendo la union en un auxiliars
         * @param d Diccionario a sumar, añadiendo palabras y definiciones nuevas
         * @return aux Un diccionario que contiene ambos diccionarios
         */
        Diccionario operator+(const Diccionario & d){
            Diccionario aux(*this);
            typename list<data<T,U>>::iterator it2;
            typename list<data<T,U>>::const_iterator it;;
            for (it=d.datos.begin();it!=d.datos.end();++it){
                if(aux.Esta_Clave((*it).clave,it2)){ //mete las definiciones que no existan de la palabra
                    typename list<U>::const_iterator itinfod, itinfoaux;
                    bool existedef = false;
                    for (itinfod=(*it).info_asoci.begin();itinfod != (*it).info_asoci.end();++itinfod){
                        existedef = false;
                        for(itinfoaux=(*it2).info_asoci.begin();itinfoaux != (*it2).info_asoci.end() && !existedef;++itinfoaux)
                            if((*itinfoaux) == (*itinfod))
                                existedef = true;
                        if(!existedef)
                            aux.AddSignificado_Palabra((*itinfod),(*it).clave);
                    }
                }
                else //Si no existe la palabra, la mete
                    aux.Insertar((*it).clave,(*it).info_asoci);
            }
            return aux;
        }

        /**
         * @brief Devuelve los elementos entre las 2 claves dadas
         * @param clavea La clave inferior
         * @param claveb La clave superior
         * @return D Un nuevo diccionario con las claves intermedias con sus definiciones
         */
        Diccionario getElementosEntreClaves(const T & clavea, const T & claveb){
			Diccionario<T,U> D;
			typename list<data<T,U>>::iterator ita, itb;
            bool terminar = false;
            int disa,disb;
			if (Esta_Clave(clavea, ita) && Esta_Clave(claveb, itb)){
                disa = distance(datos.begin(), ita);
                disb = distance(datos.begin(), itb);
                if(disa <= disb){ //Si clave_a esta antes o es igual que clave_b
                    while (ita != itb){
                        D.Insertar((*ita).clave, (*ita).info_asoci);
                        ita++;
                    }
                    D.Insertar((*ita).clave, (*ita).info_asoci); //Añadimos la clave b
                }
                else{ //Si clave_b esta antes que clave_a
                    while (itb != ita){
                        D.Insertar((*itb).clave, (*itb).info_asoci);
                        itb++;
                        //cout << (*itb).clave << " y " << (*itb).clave << endl;
                    }
                    D.Insertar((*itb).clave, (*itb).info_asoci); //Añadimos la clave b
                }

            }
            else
                cerr << "Una de las claves introducidas no existe" << endl;

			return D;
		}

		 /**
          * @brief Devuelve la información (una lista) asociada a una clave p. Podrían
          * haberse definido operator[] como
          * data<T,U> & operator[](int pos){ return datos.at(pos);}
          * const data<T,U> & operator[](int pos)const { return datos.at(pos);}
          * @param p La palabra de la cual se busca su lista de definiciones
          * @return La lista de definiciones de la palabra si existe, devuelve una vacia en otro caso
		  */
		  list<U> getInfo_Asoc(const T & p) {
			   typename list<data<T,U> >::iterator it;

			   if (!Esta_Clave(p,it)){
				return list<U>();
			   }
			   else{
				return (*it).info_asoci;
			   }
		 }			   
				
			   
		 
		/**
         * @brief Devuelve el tamaño del diccionario
         * @return El tamaño del diccionario
         */
		 int size()const{
			   return datos.size();
		 }
		

		    /**
		     * @brief clase para iterar sobre la guia
		     * */
		    class iterator{
		     private:
		      typename list<T,list<U>>::iterator it;
		     public:
		       iterator & operator++(){
			    ++it;
                return *this;
		       }
		       iterator & operator--(){
			   --it;
               return *this;
		       }
		       list<const T,list<U>> &operator *(){
               return *it;
		       }
		       bool operator ==(const iterator &i){
               return i.it==it;
		       }

		       bool operator !=(const iterator &i){
               return i.it!=it;
		       }
		       friend class Diccionario;
		    };

		 /**
          *@brief Funciones begin y end asociadas al diccionario
          */

         /**
          * @brief Devuelve el iterador inicio del diccionario
          * @return un iterador que apunta al inicio del diccionario
          */
		 typename list<data<T,U> >::iterator  begin(){
			   return datos.begin();
		 }
         /**
          * @brief Devuelve el iterador fin del diccionario
          * @return un iterador que apunta al final del diccionario
          */
		 typename list<data<T,U> >::iterator end(){
			   return datos.end();
		 }

         /**
          * @brief Devuelve el iterador inicio del diccionario
          * @return un iterador no modificable que apunta al inicio del diccionario
          */
		 typename list<data<T,U> >::const_iterator  begin()const{
			   return datos.begin();
		 }

         /**
          * @brief Devuelve el iterador fin del diccionario
          * @return un iterador no modificable que apunta al final del diccionario
          */
		 typename list<data<T,U> >::const_iterator end()const {
			   return datos.end();
		 }
		 	
};

#endif
	 
	  

	  
