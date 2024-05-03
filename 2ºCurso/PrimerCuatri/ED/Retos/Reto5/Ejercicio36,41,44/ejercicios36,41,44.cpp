//////////////////////////////////////////////////////////////////////////////////////////////////////////
//EJERCICIO 36
//////////////////////////////////////////////////////////////////////////////////////////////////////////
int getProfundidad(const bintree<int> &arb, bintree<int>::node n) { //Calcula la profundidad del nodo en el árbol (igual implementación que el getnivel)
    int profundidad = 0;

    while ( n != arb.laraiz ) {
        n = n.parent();
        profundidad++;
    }

    return profundidad;
}

bintree<int>::node AMC(const bintree<int> &A, bintree<int>::node v, bintree<int>::node w) {
    bintree<int>::node ancestro;
    
    // Primero hacemos que ambos estén en el mismo nivel, entonces
    // encontrar el ancestro común más cercano será ir subiendo en los
    // padres de cada uno hasta que coincidan
    int prof_v = getProfundidad(A, v), prof_w = getProfundidad(A, w);
    if ( prof_v < prof_w )
        for ( int i = 0; i < prof_w-prof_v; ++i )
            w = w.parent();
    else if ( prof_v > prof_w )
        for ( int i = 0; i < prof_v-prof_w; ++i )
            v = v.parent();
    
    // caso límite
    if ( v == w )
        return v;
    
    bool continuar = true;
    while ( continuar ) {
        v = v.parent();
        w = w.parent();
        
        if ( v == w ) {
            ancestro = v;
            continuar = false;
        }
    }
    
    return ancestro;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//EJERCICIO 41
//////////////////////////////////////////////////////////////////////////////////////////////////////////
int enquenivel (bintree<int>::node w, bintree<int> & A){ //Devuelve el nivel en el que se encuentra el nodo en el árbol
    int profundidad = 0;

    while ( w != A.laraiz ) {
        w = w.parent();
        profundidad++;
    }

    return profundidad;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//EJERCICIO 44
//////////////////////////////////////////////////////////////////////////////////////////////////////////
int altura(bintree<int>::node n) {  //Calcula la altura del nodo

   int alturaDerecha = 0; int alturaIzquierda = 0;

   if(n == 0) {
      return 1;
   }

   if(!n.right().null()) {
      alturaDerecha = altura(n.right());
   }

   if(!n.left().null()){
      alturaIzquierda = altura(n.left());
   }

   int alturaHijos = max(alturaDerecha, alturaIzquierda);

   return alturaHijos + 1;
}

bool tienenigualvolumen(bintree<int> A, bintree<int> B){ //Devuelve true si el num de hojas * la altura de ambos árboles es igual y false en caso contrario
    int profA = altura(A.root()), profB = altura(B.root()), hojasA = A.size(), hojasB = B.size();
    return ( (hojasA * profA) == (hojasB * profB) );
} 
