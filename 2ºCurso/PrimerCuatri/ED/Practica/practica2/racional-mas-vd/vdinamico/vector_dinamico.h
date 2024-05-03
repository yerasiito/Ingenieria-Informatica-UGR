/**
  * @file vector_dinamico.h
  * @brief Fichero cabecera del TDA Vector Dinamico
  *
  * Se crea un vector con capacidad de crecer y decrecer
  * 
  */
#ifndef _vectorDinamico_h
#define _vectorDinamico_h


/**
 *  @brief T.D.A. Vector_Dinamico
 *
 *
 * Una instancia @e v del tipo de datos abstracto @c Vector_Dinamico sobre el
 * tipo @c float es un array 1-dimensional de un determinado tamaño @e n, que
 * puede crecer y decrecer a petición del usuario. Lo podemos representar como
 *
 *  {v[0],v[1],...,v[n-1]} 
 *
 * donde  v[i] es el valor almacenado en la posición  i del vector
 *
 * La eficiencia en espacio es @e O(n).
 *
 * Un ejemplo de su uso:
 * @include ejemplo_vector_dinamico.cpp
 *
 */
class Vector_Dinamico {
  private:
    /**
       * @page repVector_Dinamico Rep del TDA Vector_Dinamico
       *
       * @section invVector_Dinamico Invariante de la representación
       *
       * Un objeto válido @e v del TDA Vector_Dinamico debe cumplir 
       * - @c v.nelementos>= 0 
       * - @c v.datos apunta a una zona de memoria con capacidad para albergar
       *   @c nelementos valores de tipo @c float
       *
       * @section faVector_Dinamico  Función de abstracción
       *
       * Un objeto válido @e rep del TDA Vector_Dinamico representa al vector de
       * tamaño @e n
       *
       * {v.datos[0],v.datos[1],...,v.datos[v.nelementos-1]}
       *
    */
    float * datos; /**< Apunta a los elementos del vector */
    int nelementos; /**< Indica el número de elementos en @c datos */
  public:
    // ---------------  Constructores ----------------
    /**
     * @brief Constructor por defecto
     * @param n indica el número de componentes inicial reservados
     *          para el vector
     * @note
     *   Este constructor también corresponde al de por defecto
     */
    Vector_Dinamico(int n=0);
    Vector_Dinamico(const Vector_Dinamico& original);
    // ------------------ Destructor ------------------
    ~Vector_Dinamico();
    // --------------- Otras funciones ---------------
    /**
     * @brief Número de componentes del vector
     * @return Devuelve el número de componentes que puede almacenar en este
     * instante el vector
     * @see resize()
     */
    int size() const;
    /**
     * @brief Acceso a un elemento
     * @param i la posición del vector donde está el componente. 0<=i<size()
     * @return La referencia al elemento. Por tanto, se puede usar para almacenar
     *     un valor en esa posición.
     */
    float& operator[] (int i);
    /**
     * @brief Acceso a un elemento de un vector constante
     * @param i la posición del vector donde está el componente. 0<=i<size()
     * @return La referencia al elemento. Se supone que el vector no se puede
        modificar y por tanto es acceso de sólo lectura
     */
    const float& operator[] (int i) const;
    /**
     * @brief Redimensión del vector
     * @param n El nuevo tamaño del vector. n>=0
     * @post Los valores almacenados antes de la redimensión no se pierden
     *  (excepto los que se salen del nuevo rango de índices)
     */
    void resize(int n);
    Vector_Dinamico& operator= (const Vector_Dinamico& original);
};

#endif /* _vectorDinamico_h */
