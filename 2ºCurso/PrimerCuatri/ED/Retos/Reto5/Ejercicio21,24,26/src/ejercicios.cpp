///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EJERCICIO 21
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief funcion auxiliar a pesointerior para trabajar con nodos de forma recursiva
 * @param n node a iterar del arbol
 * @return true si la suma de los hijos es igual al padre, false en otro caso
 */
bool pesointerior_nodo(bintree<int>::node n){
   if(n.left().null() && n.right().null())
      return true; //Si llega aqui, ha pasado todas las comprobaciones anteriores, por tanto, devuelve true
   else
      if(n.parent().null()){ //si es el nodo raiz, controla el resultado final
         if(*n == *n.left() + *n.right()){
            if(!pesointerior_nodo(n.left()))
               return false;
            if(!pesointerior_nodo(n.right()))
               return false;
         return true; //si todos los nodos cumplen la condicion, entonces devuelve true
         }
      }
      else //si es otro nodo
         if(n.left().null() && *n == *n.right())
            return pesointerior_nodo(n.right());
         else if(n.right().null() && *n == *n.left())
            return pesointerior_nodo(n.left());
         else
            if(*n == *n.left() + *n.right()){
               return pesointerior_nodo(n.left());
               return pesointerior_nodo(n.right());
            }
   return false; //false en otro caso
}

/**
 * @brief comprueba si un arbol es pesointerior, es decir, la suma de los hijos de cada nodo es el padre
 * Usa la funcion auxiliar pesointerior_nodo para trabajar con nodos de forma recursiva
 * @param a arbol a comprobar
 * @return true si la suma de los hijos de los nodos es igual al padre, false en otro caso
 */
bool pesointerior(bintree<int> a){
   return pesointerior_nodo(a.root());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EJERCICIO 24
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief devuelve la suma de los caminos cuyos nodos tienen valor par
 * @param a arbol a comprobar
 * @param n node raiz del arbol
 * @return contador total de los valores de los nodos con valor par(siguiendo un camino)
 */
int sumaparantec(bintree<int> & a, bintree<int>::node n){
   if(n.left().null() && n.right().null()) //es una hoja?
      if(*n%2 == 0){return *n;}
      else return 0;
   else{
      int contador = 0;
      if(*n%2 == 0){
         contador+=sumaparantec(a, n.left());
         contador+=sumaparantec(a, n.right());
         contador+=*n;
      }
         return contador;
   }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//EJERCICIO 26
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief comprueba si un arbol dado contiene caminos ordenador de menor a mayor
 * @param a arbol a comprobar
 * @param n node raiz del arbol
 * @return true si existe el camino, false en otro caso
 */
bool camino_ord(bintree<int> A, bintree<int>::node n){
   if(n.left().null() && n.right().null())
      if(*n > *n.parent())
         return true;
      else
         return false;
   else{
      if(n.parent().null()){
         if(camino_ord(A, n.left()))
            return true;
         if(camino_ord(A, n.right()))
            return true;

         return false;
      }
      else if( *n > *n.parent()){
         return camino_ord(A, n.left());
         return camino_ord(A, n.right());
      }
   }

   return false; //false en otro caso;
}
