/**
  * @file conjunto_reales.h
  * @brief Fichero cabecera del TDA Conjunto_Reales
  *
  */
#ifndef _conjunto_reales_h
#define _conjunto_reales_h

#include <vector_dinamico.h>
#include <cassert>

/**
 *  @brief T.D.A. Conjunto_Reales
 *
 * Una instancia @e c del tipo de datos abstracto @c Conjunto_Reales 
 * es un conjunto de números de tipo \c float.
 *
 * El número de elementos del conjunto se denomina \e cardinal o \e tamaño del
 * conjunto. Un conjunto de tamaño cero se denomina vacío.
 * Lo podemos representar como
 *
 * {e1,e2,e3...,en}
 * 
 * donde n es el número de elementos del conjunto.
 * La eficiencia en espacio es @e O(n).
 *
 *
 * Un ejemplo de su uso:
 * @include ejemplo_conjunto_reales.cpp
 *
 * @author A. Garrido
 * @date Octubre-2011
 */
class Conjunto_Reales {
  private:
    /**
       * @page repConjunto_Reales Rep del TDA Conjunto_Reales
       *
       * @section invConjunto_Reales Invariante de la representación
       *
       * Un objeto válido @e rep del TDA Conjunto_Reales debe cumplir 
       * - @c rep.v.size()>=rep.nelementos 
       * - @c rep.nelementos>= 0
       * - \c rep.v[i]<rep.v[j] para todo \e i,j tal que \e \c
 0<=i<j<rep.nelementos
       *
       * @section faConjuntoReales Función de abstracción
       *
       * Un objeto válido @e rep del TDA Vector_Disperso representa al vector
       *
       * { rep.v[0],...,rep.v[rep.nelementos]}
       *
    */    
    Vector_Dinamico v; /**< Almacena los elementos del conjunto */
    int nelementos;  /**< Número de posiciones de \c v usadas */
    /**
     * @brief Localizador de una posición en @c v
     *
     * @param val valor del indice a localizar en la matriz
     * @retval pos La posición donde se encuentra el @a val (si está) o
     *     la posición donde debería insertarse (si no está)
     * @return Si el valor @a val está en el vector
     * @note La eficiencia es logarítmica (usa búsqueda binaria)
     */    
    bool posicion_elemento(int& pos, float val) const;
  public:
    Conjunto_Reales(): nelementos(0) {}
    // Conjunto_Reales(const Conjunto_Reales& c);
    // ~Conjunto_Reales();
    // Conjunto_Reales& operator= (const Conjunto_Reales& c);
    /**
     * @brief Añadir un elemento
     *
     * @param f valor a insertar en el conjunto.
     * @return Si el número de elementos ha aumentado (false en caso
     *     de que el elemento ya estaba en el conjunto)
     */
    bool Insertar(float f);
    /**
     * @brief Eliminar un elemento
     *
     * @param f valor a eliminar del conjunto.
     * @return Si el número de elementos ha disminuido (false en caso
     *     de que el elemento no estuviera en el conjunto)
     */
    bool Borrar(float f);
     /**
     * @brief Consultar la existencia de un elemento
     *
     * @param f valor a consultar en el conjunto.
     * @return Si el elemento pertenece al conjunto
     */
    bool Pertenece(float f) const { int pos; return posicion_elemento(pos,f); }
    /**
     * @brief Valor del i-ésimo elemento
     *
     * @param i indica el elemento del conjunto que queremos obtener.
     * @pre 0<=i<size()
     * @return El valor del i-ésimo elemento.
     */
    float Elemento(int i) const { assert(0<=i && i<v.size()); return v[i]; }
    /**
     * @brief Cardinal del conjunto
     * @return El número de elementos del conjunto
     */
    int size() const { return nelementos; }
};

#endif /* _conjunto_reales_h */
