/**
 * @author Yeray Lopez Ramirez
 * @date 15 de diciembre de 2021
 * @file guiatlf.h
 * @brief TDA guia_tlf. Es un .h pero funciona como .cpp
 */
#ifndef _GUIA_TLF_H
#define _GUIA_TLF_H
#include <map>
#include <iostream>
#include <string>
using namespace std;
istream & operator>>(istream &is,pair<string,string> &d){
	  
	  getline(is,d.first,'\t');
	  getline(is,d.second);
	  return is;
}	  

ostream & operator<<(ostream &os,const pair<const string,string> &d){
	  
	  os<<d.first<<'\t'<<d.second<<endl;
	  return os;
}	  


/**
  *  @brief T.D.A. Guia_Tlf
  *
  * Una instancia @e c del tipo de datos abstracto @c Guia_Tlf es un objeto
  * formado por una colección de pares {(e11,e21),(e12,e22),(e13,e23),...,(e1n-1,e2n-1)}
  * ordenados por la el primer elemento del par denominado clave o key. No existen
  * elementos repetidos. 
  *
  *
  * Un ejemplo de su uso:
  *
  *
  * @author Rosa Rodríguez
  * @date Marzo 2012
  */

class Guia_Tlf{
  /**
  * @page repGuia_Tlf Rep del TDA Guia_Tlf
  *
  * @section invGuia_Tlf Invariante de la representación
  *
  * El invariante es \e para todo \e i y \e j tal que i<j entonces \e e1i y e1j son distintos
  *
  * @section faGuia_Tlf Función de abstracción
  *
  * Un objeto válido @e rep del TDA Guia_Tlf representa al valor
  *
  * {(rep.begin().first,rep.begin().second),(rep.begin()+1.first,rep.begin()+1.second),....,(rep.begin()+n-1.first,rep.begin()+n-1.second)}
  *
  */
	  private:
		    map<string,string> datos; //si admites que haya nombres repetidos tendrías que usar un
					     //multimap
					     
	  public:
		    
		    /**
		      @brief Acceso a un elemento
		      @param nombre: nombre del elemento  elemento acceder
		      @return devuelve el valor asociado a un nombre, es decir el teléfono
		    */
		    //si fuese un multimap no podriamos usar []. Ademas que deberiamos devolver p.e un vector con todos
		    // los telefonos asociados a dicho nombre
		    string & operator[](const string &nombre) {
			      return datos[nombre];
		    }
		    
		    
		    string  gettelefono(const string & nombre){
			      map<string,string>::iterator it=datos.find(nombre);
			      if (it==datos.end()) 
					return string("");
			      else return it->second;
		    }
		     
		    /**
		     @brief Insert un nuevo telefono 
		     @param nombre: nombre clave del nuevo telefono
		     @param tlf: numero de telefono
		     @return : un pair donde first apunta al nuevo elemento insertado y bool es true si se ha insertado el nuevo tlf o 
			      o false en caso contrario
		    */
		    pair<map<string,string>::iterator,bool>  insert(string nombre, string tlf){
			      pair<string,string> p (nombre,tlf);
			      pair< map<string,string> ::iterator,bool> ret;

			      ret=datos.insert(p); //datos.insert(datos.begin(),p); tambien funcionaría
			      return ret;     
					
		    }
		    
		    /**
		     @brief Insert un nuevo telefono 
		     @param p: pair con el nombre y el telefono asociado
		     
		     @return : un pair donde first apunta al nuevo elemento insertado y bool es true si se ha insertado el nuevo tlf o 
			      o false en caso contrario
		    */
		    pair<map<string,string>::iterator,bool>  insert(pair<string,string> p){
			      
			      pair<map<string,string> ::iterator,bool> ret;

			      ret=datos.insert(p); //datos.insert(datos.begin(),p); tambien funcionaría
			      return ret;     
					
		    }
		    
		    /**
		      @brief Borrar un telefono
		      @param nombre: nombre que se quiere borrar
		      @note: en caso de que fuese un multimap borraria todos con ese nombre
		    */
		    void borrar(const string &nombre){
			   map<string,string>::iterator itlow = datos.lower_bound(nombre);//el primero que tiene dicho nombre
			   map<string,string>::iterator itupper = datos.upper_bound(nombre);//el primero que ya no tiene dicho nombre
			   datos.erase(itlow,itupper);//borramos todos aquellos que tiene dicho nombre
			   //OTRA ALTERNATIVA
			   //pair<map<string,string>::iterator,map<string,string>::iterator>ret;
			   //ret = datos.equal_range(nombre
			   //datos.erase(ret.first,ret.second);   
		    }
		    
		    /**
		      @brief Borrar un telefono
		      @param nombre: nombre que se quiere borrar y telefono asociado
		      @note: esta funcion nos permite borrar solamente aquel que coincida en nombre y tlf
		    */
		    //con map siempre hay uno con multimap puede existir mas de uno
		    void borrar(const string &nombre,const string &tlf){
		           map<string,string>::iterator itlow = datos.lower_bound(nombre);//el primero que tiene dicho nombre
			   map<string,string>::iterator itupper = datos.upper_bound(nombre);//el primero que ya no tiene dicho nombre
			   map<string,string>::iterator it;
			   bool salir =false;
			   for (it=itlow; it!=itupper && !salir;++it){
				     if (it->second==tlf){
					datos.erase(it);
					salir =true;
				     }		
			   }		
			   
		    }
		    /**
		      @brief  Numero de telefonos 
		      @return el numero de telefonos asociados
		     */
		    int size()const{
			      return datos.size();
		    }	      
		    /**
		      @brief Contabiliza cuantos telefonos tenemos asociados a un nombre
		      @param nombre: nombre sobre el que queremos consultar
		      @return numero de telefonos asociados a un nombre
		      
		     */
		    //al ser un map debe de ser 0 o 1. Si fuese un multimap podríamos tener mas de uno
		    unsigned int contabiliza(const string &nombre){
			      return datos.count(nombre);
		    }
		    
		    /**
		      @brief Limpia la guia
		     */
		    void clear(){
			      datos.clear();
		    }	      
		    /**
		      @brief Union de guias de telefonos
		      @param g: guia que se une
		      @return: una nueva guia resultado de unir el objeto al que apunta this y g
		    */
		    Guia_Tlf operator+(const Guia_Tlf & g){
			Guia_Tlf aux(*this);
			map<string,string>::const_iterator it;
			for (it=g.datos.begin();it!=g.datos.end();++it){
			   aux.insert(it->first,it->second);
			}	  
			return aux;
			
		    }	   
		    	      
		    /**
		      @brief Diferencia de guias de telefonos
		      @param g: guia a restar
		      @return: una nueva guia resultado de la diferencia del objeto al que apunta this y g
		    */
		    Guia_Tlf operator-(const Guia_Tlf & g){
			Guia_Tlf aux(*this);
			map<string,string>::const_iterator it;
			for (it=g.datos.begin();it!=g.datos.end();++it){
			   aux.borrar(it->first,it->second);
			}	  
			return aux;
			
		    }
		    /**
		      @brief  Obtiene una guia con los nombre previos a uno dado
		      @param nombre: nombre delimitador
		      @param tlf: telefono asociado a nombre
		      @return nueva guia sin nombres mayores que \a  nombre
		     */
		    Guia_Tlf previos(const string &nombre,const string &tlf){
			map<string,string>::value_compare vc=datos.value_comp();
            //map<string,string>::key_compare vc=datos.key_comp();
			Guia_Tlf aux;
			pair<string,string>p(nombre,tlf);
			map<string,string>::iterator it=datos.begin();
			while (vc(*it,p)){
				  aux.insert(*it++);
				  
			}
			return aux;
			      
		     }	      
		    
		    /**
             * @brief Modifica el numero de telefono del nombre pasado como parametro
             * @param nombre El nombre de contacto cuyo telefono se quiere modificar
             * @param tlf El nuevo telefono que reemplazara el antiguo
             */
		    void modificarTlf(string nombre, string tlf){
			      map<string,string>::iterator it=datos.find(nombre);
                  if(it != datos.end()){
                     pair<string,string> p(it->first,tlf);
                     datos.erase(it);
                     datos.insert(p);
                  }
            }

            /**
             * @brief Lista los telefonos de los contactos que empiecen por la letra pasada como paramatro
             * @param letra La letra a partir del cual se buscaran los telefonos
             * @return tlfs Una guia con los telefonos encontrados
             */
		    Guia_Tlf TlfsPorLetra(char letra){
                Guia_Tlf tlfs;
                int contador = 1; //Para enumerar los telefonos del map
                map<string,string>::iterator it;
                for(it = datos.begin(); it != datos.end(); ++it)
                    if(letra == (*it).first[0])
                        tlfs.insert(to_string(contador++) + ".",(*it).second);

                return tlfs;
            }

            /**
             * @brief Lista los telefonos que se encuentran entre los 2 nombres dados como parametro
             * @param nombre_1 El nombre a partir empieza a listar
             * @param nombre_2 El nombre hasta donde se listan los telefonos
             * @return tlfs Los telefonos encontrados
             */
		    Guia_Tlf TelfsEntreNombres(const string &nombre_1, const string &nombre_2){
                Guia_Tlf tlfs;
                map<string,string>::iterator itlow = datos.find(nombre_1);
                map<string,string>::iterator itupper = datos.find(nombre_2);

                int contador = 1,
                    dis1 = distance(datos.begin(),itlow),
                    dis2 = distance(datos.begin(), itupper);
                if(itlow != datos.end() && dis1 <= dis2){
                  tlfs.insert(to_string(contador++) + ".",itlow->second);
                  while(dis1 < dis2){
                     itlow++; dis1++;
                     tlfs.insert(to_string(contador++) + ".",itlow->second);
                  }
                }
                return tlfs;
            }

		    /**
		      @brief Escritura de la guia de telefonos
		      @param os: flujo de salida. Es MODIFICADO
		      @param g: guia de telefonos que se escribe
		      @return el flujo de salida
		     */
		    friend ostream & operator<<(ostream & os, Guia_Tlf & g){
			      map<string,string>::iterator it;
			      for (it=g.datos.begin(); it!=g.datos.end();++it){
					os<<it->first<<"\t"<<it->second<<endl;
			      }
			      return os;
		    }
		    
		    /**
		      @brief Lectura de  la guia de telefonos
		      @param is: flujo de entrada. ES MODIFICADO
		      @param g: guia de telefonos. ES MODIFICADO
		      @return el flujo de entrada
		    */
		    
		    friend istream & operator>>(istream & is, Guia_Tlf & g){
			      pair<string,string> p;
			      Guia_Tlf aux;
			      
			      while (is>>p){
				  aux.insert(p);
			      }
			      g=aux;
			      return is;
		    }

		    /**
		     * @brief clase para iterar sobre la guia
		     * */
		    class iterator{
		     private:
		      map<string,string>::iterator it;
		     public:
		       iterator & operator++(){
			    ++it;
                return *this;
		       }
		       iterator & operator--(){
			   --it;
               return *this;
		       }
		       pair<const string,string> &operator *(){
			  return *it;
		       }
		       bool operator ==(const iterator &i){
			  return i.it==it;
		       }	  
		       
		       bool operator !=(const iterator &i){
			  return i.it!=it;
		       }
		       friend class Guia_Tlf;
		    };
		    
		    /**
		     * @brief Inicializa un iterator al comienzo de la guia
		     * */
		    iterator  begin(){
			iterator i;
			i.it=datos.begin();
			return i;
		    }	
		    /**
		     * @brief Inicializa un iterator al final de la guia
		     * */
		    iterator  end(){
			iterator i;
			i.it=datos.end();
			return i;
		    }  
		        
					
			      
		    
};
#endif

