////////////////////////////////////////////////////////////////////////////////////////////////////////////
//EJERCICIO 35
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void preorden_suma(const ArbolBinario<int>& a, const typename ArbolBinario<int>::Nodo n1,const ArbolBinario<int>& b, const typename ArbolBinario<int>::Nodo n2){
    if (n1 != 0 && n2 != 0){
        n2->etiqueta += n1->etiqueta;

        preorden_suma(a,a.izquierda(n1), b, b.izquierda(n2));
        preorden_suma(a,a.derecha(n1), b, b.derecha(n2));
    }
}

void sumar_dos_arboles_en_otro (const ArbolBinario<int> &a, const ArbolBinario<int> &b, ArbolBinario<int> &c)
{
    c = a;
    preorden_suma(b,b.raiz(), c, c.raiz());

}
