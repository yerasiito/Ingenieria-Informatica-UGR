/**
  * @file ahorcado.cpp
  * @brief Programa para jugar al ahorcado en consola
  *
  * @author Fulanito...
  * @date Enero-2020
  *
  * El programa implementa una versión básica del juego del ahorcado como
  * ejercicio de uso de clases simples.
  * 
  * El objetivo que se pretende es programar el juego en base a una clase "Ahorcado"
  * que resuelva las operaciones que se tienen que realizar. El programa principal
  * deberá declarar un objeto de esta clase y llamar a los distintos métodos hasta
  * el final de la partida.
  * 
  * Para hacerse una idea de qué componentes formarán parte de la clase:
  * 
  * - Un objeto de esta clase, deberá tener información sobre:
  *    - La frase o palabra que hay que acertar.
  *    - La plantilla con el estado actual de la partida (la palabra con guiones).
  *    - El número de intentos que quedan.
  *    - Las letras que ya se han dicho hasta el momento.
  * 
  * - Para que la clase controle el proceso de la partida, deberá tener operaciones para:
  *    - Consultar el estado actual de la plantilla (la cadena de letras/guiones actual)
  *    - Consultar el número de intentos que quedan.
  *    - Consultar la cadena de letras que ya se han usado.
  *    - Saber si la partida se ha terminado.
  *    - Saber si una letra se puede decir o no.
  *    - Saber si se ha ganado la partida.
  *    - Procesar una nueva letra seleccionada por el jugador, teniendo en cuenta que si
  *      se da en mayúscula también debe funcionar. La función devolverá si se ha procesado
  *      correctamente, es decir, si la letra tenía sentido y no se había usado antes. Por 
  *      ejemplo, si le da un carácter que no es una letra no se puede procesar.
  * 
  * Para hacer el programa más interesante, el juego debería "inventarse" una palabra. Para
  * resolver esto, creamos una clase con la responsabilidad de seleccionar una palabra
  * aleatoria. El diseño que se propone es crear una nueva clase "Bolsa" que nos hace de
  * generador aleatorio. 
  * 
  * Para hacerse una idea de qué componenetes formarán parte de la clase, tenga en cuenta
  * que deberá tener múltiples palabras y nos debería permitir "sacar palabras" en un orden
  * arbitrario. Para ello, puede considerar
  *     - Deberá contener un vector privado con las palabras que hay en la bolsa.
  *     - El constructor debería cargar ese vector privado con múltiples palabras en un
  *       orden aleatorio.
  *     - Debería tener un método para seleccionar una nueva palabra.
  * 
  * Ya que es una bolsa, podemos realizar el siguiente comportamiento:
  *     - Cuando se declara un objeto de la bolsa, se cargan las palabras y se barajan.
  *     - Se puede pedir la siguiente palabra, dando lugar a una secuencia de palabras que
  *       surgen con un orden aleatorio según hayan quedado ordenadas al construir la bolsa.
  *     - Si se llegan a pedir todas las palabras, pedir la siguiente palabra implicará volver
  *       a barajar la bolsa y comenzar con la primera de ellas.
  * 
  * Para simplificar el problema sin entrar en soluciones que impliquen pedir palabras desde
  * cin, puede declarar un vector con un contenido predeterminado en el constructor y que nos
  * permite inicializar la bolsa. Si quiere, puede usar:
  *       "caballero",  "Dulcinea",   "historia",   "escudero",
  *       "rocinante",  "adelante",   "gobernador", "andantes", 
  *       "voluntad",   "capitulo",   "menester",   "doncella", 
  *       "caballeria", "castillo",   "Fernando",   "finalmente", 
  *       "aventura",   "hermosura",  "palabras",   "gobierno", 
  *       "intencion",  "cardenio",   "pensamientos", "Luscinda",
  *       "lagrimas",   "aposento",   "aventuras",  "quisiera", 
  *       "libertad",   "desgracia",  "entendimiento", "pensamiento", 
  *       "licencia",   "Mercedes",   "semejantes", "silencio", 
  *       "valeroso",   "doncellas",  "labrador",   "caballerias", 
  *       "cristiano",  "cristianos", "discreto",   "hicieron", 
  *       "llegaron",   "quisiere",   "espaldas",   "muestras", 
  *       "escuderos",  "discurso",   "grandeza",   "altisidora",
  *       "princesa",   "haciendo",   "renegado",   "provecho",
  *       "quedaron",   "resolucion", "presente",   "encantadores",
  *       "enamorado",  "valiente",   "encantado",  "molino",
  *       "licenciado", "necesidad",  "responder",  "discrecion", 
  *       "ejercicio",  "hacienda",   "posadero",   "Rocinante",
  *       "presencia",  "historias",  "presentes",  "verdadero"
  * 
  * Observe que una vez que tenga las dos clases, puede declarar una bolsa de palabras y después
  * inicializar un objeto de la clase Ahorcado con una palabra aleatoria, ya que la palabra se pide
  * al objeto "Bolsa". 
  * 
  * Para programar el juego, puede definir la clase "Ahorcado" e inicializar el objeto con una palabra
  * fija y conocida (por ejemplo, en el constructor). Una vez que ya lo ha depurado y obtenido 
  * una solución que funciona, puede añadir la clase bolsa y crear un programa que juega varias 
  * partidas del ahorcado. 
  * 
  * En concreto, el programa pedirá cuántas palabras quiere adivinar y repetirá el juevo con un 
  * bucle que permita al usuario jugar varias partidas. Note que declarará una Bolsa al principio del
  * main y el bucle que repite las partidas pedirá a dicha bolsa una nueva palabra para cada nueva partida.
  * 
  */
