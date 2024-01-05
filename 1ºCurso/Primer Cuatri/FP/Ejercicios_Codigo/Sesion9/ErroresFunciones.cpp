//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// // Don Oreo
//
//////////////////////////////////////////////////////////////////////////
/*
int ValorAbsoluto(int entero){
   if (entero < 0)
       entero = -entero;
   else
       return entero;
}
En esta primera función el error está en poner el
return entero dentro de un else ya que si el entero
es negativo, no va a devolver nada

bool EsPositivo(int valor){
   if (valor > 0)
       return true;
}
Le estamos dando un valor int, nos debe devolver un
valor int, no un true/false como si fuera un boolean

long ParteEntera(double real){
   int parte_entera;

   parte_entera = trunc(real);
   return parte_entera;
}

El int parte_entera es totalmente innecesario ya que es
justamente lo que hace el trunc. O quitas el trunc y haces
el casting automatico double a int o modificas el double real
*/
