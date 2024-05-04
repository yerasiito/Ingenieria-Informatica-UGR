# Practica 4 - Lección 2

Fecha: December 9, 2022
Resumen: Desarrollo de dockers y tests
Status: Terminado

v3 del doc. Ampliado y aclarado conceptos. Errores corregidos. Versión casi final.
Recuerda redescargar los documentos con frecuencia ya que los voy actualizando.

### Test básico con ab

ab: Apache Benchmark (está limitado por hardware)

- Con top o ps podemos ver cuantas concurrencias de ab.
- Ejecutamos ab para ver el número de concurrencias

Una vez terminada la instalación, vamos a realizar una prueba sencilla. Queremos saber el **comportamiento de nuestra página cuando hay 100 peticiones con 10 usuarios**
 que se conecten al mismo tiempo. Para realizar esta prueba, escribimos en la terminal:

```bash
ab -c 10 -n 100 https://www.ubunlog.com/ #Sustituir ubuntu por la página a testear
#y no, PRADO no se cae si le metes muchas peticiones con esto, haces un ataque DOS con un portatil xd
```

-c: indica el número de usuarios virtuales

-n: indica el número de peticiones de cada usuario

![Untitled](Imagenes/Untitled.png)

### Microservicios

Arquitectura donde los distintos servicios se ejecutan de forma independiente unos de otros y se comunican mediante APIs o sistemas de mensajería.
Su popularidad ha ido ligada a los dockers.

Ejemplos: redis o rabbitMQ

Ventajas principales: flexibilidad y escalabilidad (vertical y horizontal).

Uso principal de los microservicios: Esquema Servidor de Producción y de Desarrollo.

# Contenedores (docker)

Ventajas de una vm y un contenedor: encapsular informacion

vm: muchas capas y espacio en disco.

Contenedor: Comparte bibliotecas del SO anfitrion y la informacion sigue encapsulada.

Los contenedores ocupan menos espacio , requieren menos recursos y son
más veloces en el arranque.

Docker: usa un demonio, problemas de seguridad, ejecucion de superusuario

Recomendable podman en su lugar: no ejecuta ningun demonio de fondo, misma sintaxis que docker. En la práctica usamos docker.

![Ten en mente esta imagen, es importante
[https://www.docker.com/resources/what-container/](https://www.docker.com/resources/what-container/)](Imagenes/Untitled%201.png)

Ten en mente esta imagen, es importante
[https://www.docker.com/resources/what-container/](https://www.docker.com/resources/what-container/)

## Instalación y uso de Docker

```bash
#Todo esto es del guión
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"
sudo systemctl status docker
sudo usermod -aG docker yeraylp
```

![Untitled](Imagenes/Untitled%202.png)

ATENCION: aunque el procedimiento sea de la documentación hay un riesgo de seguridad que conviene conocer:

![Untitled](Imagenes/Untitled%203.png)

![En resumen, cualquier usuario que pertenezca al grupo de docker puede ganar privilegios y la puede liar](Imagenes/Untitled%204.png)

En resumen, cualquier usuario que pertenezca al grupo de docker puede ganar privilegios y la puede liar

```bash
docker info; docker run hello-world #la primera vez descarga la imagen
```

Opciones docker:

`docker images`: lista las imagenes cargadas en el sistema

`docker rmi (--force) imagen`: borra la imagen del sistema

Opciones docker run:

-d/--detached: ejecuta la imagen “in the background”

-p/--port: especifica el puerto donde acceder a la aplicacion del docker

-i/--interactive: permite interactuar con el docker. Se ejecuta junta a -t/--tty

-t/--tty: especifica terminal (bash). Se ejecuta junto --i

-it [image] bash: ejecuta el docker en modo interactivo a través del terminal bash. 

![Untitled](Imagenes/Untitled%205.png)

## Dockerfile

Es el equivalente del *playbook* de un docker. 

Documentación: *[Contenerizar* una aplicación](https://docs.docker.com/get-started/02_our_app/#dockerfile), [Construir un dockerfile](https://docs.docker.com/engine/reference/builder/), [Construir un composefile](https://docs.docker.com/compose/compose-file/) y [Mejores prácticas](https://docs.docker.com/develop/develop-images/dockerfile_best-practices/)

Copia archivos, instala paquetes, modifica configuraciones… al arrancar el docker.

En la aplicación de iseP4Jmeter tenemos 2 contenedores con su respectivo Dockerfile.

Podemos ver el dockerfile del docker nodejs en `iseP4JMeter/nodejs/Dockerfile`

![Todos los comandos se ejecutan DENTRO de la imagen de isep4jmeter_nodejs
El COPY copia . que es el directorio iseP4Jmeter/nodejs/. a /usr/src/app dentro del docker](Imagenes/Untitled%206.png)

Todos los comandos se ejecutan DENTRO de la imagen de isep4jmeter_nodejs
El COPY copia . que es el directorio iseP4Jmeter/nodejs/. a /usr/src/app dentro del docker

Y el dockerfile del docker mongodb en `iseP4JMeter/mongodb/Dockerfile`

![Todos los comandos se ejecutan DENTRO de la imagen de isep4jmeter_mongodb](Imagenes/Untitled%207.png)

Todos los comandos se ejecutan DENTRO de la imagen de isep4jmeter_mongodb

Puedes entrar a las imagenes en modo bash para ver como se ejecutan los comandos y el estado en el que quedan.

```bash
cd iseP4Jmeter/monogodb
docker build -t isep4jmeter_mongodb . #construye la imagen existente con el dockerfile en .
docker run -it isep4jmeter_mongodb bash #ejecutamos la imagen y entramos en bash
#Nos mete en el directorio /tmp que es el ultimo WORKDIR
```

```bash
cd iseP4Jmeter/nodejs
docker build -t isep4jmeter_mongodb . #construye la imagen existente con el dockerfile en .
docker run -it isep4jmeter_nodejs bash #ejecutamos la imagen y entramos en bash
#Nos mete en el directorio /usr/share/app que es el ultimo WORKDIR
```

Opcion de build:

-t/--target: especifica el directorio que contiene el dockerfile y los archivos de la app

`docker build prune`: borra las imágenes cargadas en caché.

No confundir con la opción de run:

-t/--tty: especifica la terminal (bash)

## Docker-compose

Es un *playbook* de varios docker.

Las imágenes anteriores los ejecuta con el compose mediante un fichero .yaml:

![Untitled](Imagenes/Untitled%208.png)

Instalamos el docker

```bash
sudo apt install docker-compose
```

Clonamos el repo de github y ejecutamos el compose:

```bash
git clone [https://github.com/davidPalomar-ugr/iseP4JMeter.git](https://github.com/davidPalomar-ugr/iseP4JMeter.git)
cd iseP4JMeter/
docker-compose up #Iniciamos el compose
#Spoiler, te vas a quedar sin espacio
#Si todo es correcto, no te devuelve el control en la terminal, se queda a la espera
```

Lo más seguro es que te falle por falta de espacio, ve al apartado de **Problemas** para ver como se amplia el espacio (Al final del doc).

Una vez arreglado quedará así:

![No devuelve el control](Imagenes/Untitled%209.png)

No devuelve el control

## Uso de la aplicación iseP4JMeter

![Esta es la estructura de la aplicación](Imagenes/Untitled%2010.png)

Esta es la estructura de la aplicación

Tenemos una aplicación metida en un compose con docker pero como funciona?

El [README.md](http://README.md) es bastante útil para entenderla. Aquí va un resumen:

La aplicación ES una API Rest (2 sistemas que se comunican para obtener información) para obtener información sobre alumnos tras una autenticación previa.

Se inicia con `docker-compose up` y al iniciar podemos ver su descripción en el navegador con la url [http://192.168.56.105:3000/](http://192.168.56.105:3000/):

![Untitled](Imagenes/Untitled%2011.png)

![En el servidor veremos la conexion](Imagenes/Untitled%2012.png)

En el servidor veremos la conexion

La aplicación tiene 2 servicios:

- /auth/login: Permite identificar al usuario como **alumno** o **administrador**. El acceso está protegido por HTTP BasicAuth(un usuario y contraseña). 
Cuando te logea, te devuelve un [JWT](https://jwt.io/) (el token) que se usa para el siguiente servicio.
- /alumnos/alumno: Devuelve el registro de calificaciones del alumno. Si es un administrador, puede consultar la nota de cualquier alumno. Se debe proporcionar un JWT(el del servicio login) para usarlo. 
**Ejemplo** del perfil de un alumno:
    
    ![Untitled](Imagenes/Untitled%2013.png)
    

El proceso de consulta es:

1. Identificarse en el servicio de login proporcionando credenciales de válidas de alumno o administrador. Obteniendo un token.
2. Solicitar los datos del propio alumno identificado (alumno) o de un grupo de alumnos (administrador).

Podemos hacer uso de los servicios con el script de prueba: `./pruebaEntorno.sh`

![Untitled](Imagenes/Untitled%2014.png)

Debemos entender como funciona. Lo primero es:

Comando `curl`: es una herramienta para transferir datos desde o para un servidor (HTTP/s). Opciones:

-s/--silent: Silencia el output.

-u/--user: especifica el nombre de usuario y contraseña.

-d/--data: Envia el dato especificado (POST) al servidor HTTP (credenciales)

-H/--header: Cabecera para obtener una página web

-X/--request: especifica un metodo de solicitud (GET) al comunicarse al servidor HTTP

El `$token` es una cadena de identificación que nos da el servicio de login.

![Untitled](Imagenes/Untitled%2015.png)

Es recomendable hacer los pasos a mano para entender mejor su funcionamento:

```bash
#login
curl -s -u etsiiApi:laApiDeLaETSIIDaLache -d "login=mariweiss@tropoli.com&password=anim" -H "Content-Type: application/x-www-form-urlencoded" -X POST http://192.168.56.105:3000/api/v1/auth/login
#muestra $TOKEN
```

![cuidado al copiarlo que se genera detrás de la linea de comandos](Imagenes/Untitled%2016.png)

cuidado al copiarlo que se genera detrás de la linea de comandos

![Untitled](Imagenes/Untitled%2017.png)

```bash
#solicitud
curl -H "Authorization: Bearer $TOKEN" http://192.168.56.105:3000/api/v1/alumnos/alumno/mariweiss%40tropoli.com
```

![Untitled](Imagenes/Untitled%2018.png)

![Untitled.png](Imagenes/Untitled%2019.png)

Recomiendo muy muy fuertemente usar el plugin [RESTED](https://chrome.google.com/webstore/detail/rested/eelcnbccaccipfolokglfhhmapdchbfg/related) en vuestro navegador.

Podemos probar las peticiones de GET y POST con RESTED muy visualmente:

![Primera consulta al servicio login](Imagenes/Untitled%2020.png)

Primera consulta al servicio login

![Segunda consulta al servicio alumno](Imagenes/Untitled%2021.png)

Segunda consulta al servicio alumno

Observamos en el servidor como van y vienen los mensajes:

![Memorizad esto de memoria, bueno con hacer la práctica una vez lo sabréis](Imagenes/Untitled%2022.png)

Memorizad esto de memoria, bueno con hacer la práctica una vez lo sabréis

Una vez entendida la aplicación, procedemos a testearla.

## Test completo con JMeter

Recordar tener el servidor docker-composer abierto para hacer esta parte.

JMeter permite lanzar tests (peticiones) desde un servidor a varios servidores. Guarda los proyectos en ficheros `jmx`.

Nota: Alternativa a JMeter = Gatling
También tenemos [locust](https://locust.io/) que nos permite escribir los tests en Python

Con `Ansible` no nos podemos asegurar de que la ejecución está sincronizada.

JMeter requiere de una interfaz gráfica cosa que nuestra vm no tiene así que vamos a runearlo desde el anfitrión (he probado el display forwarding pero no funciona bien).

1. Descarga de JMeter (no requiere instalación)
    
    Descargamos JMeter de [https://jmeter.apache.org/download_jmeter.cgi](https://jmeter.apache.org/download_jmeter.cgi)
    
    ![Untitled](Imagenes/Untitled%2023.png)
    
    ```bash
    #o con wget 
    wget https://dlcdn.apache.org//jmeter/binaries/apache-jmeter-5.5.zip
    unzip apache-jmeter-5.5.zip
    cd apache-jmeter-5.5/bin/
    #Runeamos ./jmeter o ApacheMeter.jar, ambos valen
    ./jmeter
    java -jar ApacheJMeter.jar #uso este por el modo oscuro xD
    ```
    
    ![Untitled](Imagenes/Untitled%2024.png)
    
2. Configuración completa del test, agárrate que esto es largo:
    1. Parametrizamos el Host y el Puerto:
    HOST: 192.168.56.105
    PORT: 3000
        
        ![Untitled](Imagenes/Untitled%2025.png)
        
    2. Hacer grupos de hebras para alumnos y admins. 
        
        ![Untitled](Imagenes/Untitled%2026.png)
        
        ![Inventate el numero de hilos, el periodo de subida y el contador de bucle](Imagenes/Untitled%2027.png)
        
        Inventate el numero de hilos, el periodo de subida y el contador de bucle
        
        ![Inventate el numero de hilos, el periodo de subida y el contador de bucle](Imagenes/Untitled%2028.png)
        
        Inventate el numero de hilos, el periodo de subida y el contador de bucle
        
    3. Añadimos los Valores por Defecto para Petición HTTP. Con esto todas las peticiones (las credenciales) usarán el mismo servidor y puerto.
    
        
        NOTA: TODOS los aliases tienen la forma `${}` , cuidado y no confundirlos con paréntesis.
        
        ![Untitled](Imagenes/Untitled%2029.png)
        
        ![Untitled](Imagenes/Untitled%2030.png)
        
    4. Añadimos las peticiones de login de cada alumno. Creamos una Petición HTTP:
        
        ![Untitled](Imagenes/Untitled%2031.png)
        
        Peticion: POST
        Ruta: /api/v1/auth/login
        Añadimos login y password a la tabla de parámetros con los valores $(login) y $(password). Se rellenan automáticamente con los .csv que añadimos después.
        
        ![Untitled](Imagenes/Untitled%2032.png)
        
    5. Añadimos las credenciales de los alumnos (los ficheros .CSV):
        
        ![Untitled](Imagenes/Untitled%2033.png)
        
        Descargate los JMeter/*.csv del repositorio https://github.com/davidPalomar-ugr/iseP4JMeter.git. Con un clone o a mano.
        En el nombre del archivo: busca donde te hayas descargado tú el alumnos.csv
        La codificación a UTF-8.
        El modo compartido debe ser el actual grupo (para no afectar a los administradores)
        
        ![Untitled](Imagenes/Untitled%2034.png)
        
    6. Extraemos el token que nos devuelve la Petición HTTP:
        
        ![Untitled](Imagenes/Untitled%2035.png)
        
        ![token es el alias que creamos antes para el token, aquí lo escribe
        $0$ es un identificador
        .+ ni idea de que es pero hace falta para que funcione](Imagenes/Untitled%2036.png)
        
        token es el alias que creamos antes para el token, aquí lo escribe
        $0$ es un identificador
        .+ ni idea de que es pero hace falta para que funcione
        
    7. Añadimos el temporizador de esperas aleatorias:
        
        ![El guión nos pide que usemos la gaussiana](Imagenes/Untitled%2037.png)
        
        El guión nos pide que usemos la gaussiana
        
        ![Lo dejamos tal cual](Imagenes/Untitled%2038.png)
        
        Lo dejamos tal cual
        
    8. Obtenemos los datos del alumno con otra Petición HTTP:
        
        ![Untitled](Imagenes/Untitled%2039.png)
        
        OJO CUIDADO: es __urlcode con 2 guiones bajos
        
        Peticion: GET
        Ruta: /api/v1/alumnos/alumno/${__urlencode(${login})}
        
        ![Untitled](Imagenes/Untitled%2040.png)
        
    9. Añadimos Cabecera HTTP que nos dará los datos del alumno:
    Nombre: Authorization 
    Valor: Bearer ${token}
        
        ![Untitled](Imagenes/Untitled%2041.png)
        
        ![Untitled](Imagenes/Untitled%2042.png)
        
    10. Añadimos la autorización para acceder a la API:
        
        URL Base: http://${HOST}:${PORT}/api/v1/auth/login
        Nombre de usuario: etsiiApi
        Contraseña: laApiDeLaETSIIDaLache
        
        ![Untitled](Imagenes/Untitled%2043.png)
        
        ![El nombre el que quieras, yo uso el de github
        ](Imagenes/Untitled%2044.png)
        
        El nombre el que quieras, yo uso el de github
        
    
    Ahora igual pero con administradores:
    
    1. Añadimos las Credenciales de los Administradores:
        
        ![Untitled](Imagenes/Untitled%2045.png)
        
        ![Untitled](Imagenes/Untitled%2046.png)
        
    2. Añadimos la Petición HTTP para el login de los administradores:
        
        ![Untitled](Imagenes/Untitled%2047.png)
        
        ![Untitled](Imagenes/Untitled%2048.png)
        
    3. Obtenemos el token JWT:
        
        ![Untitled](Imagenes/Untitled%2049.png)
        
        ![Untitled](Imagenes/Untitled%2050.png)
        
    4. El acceso de los administradores usa apiAlumnos.log. 
    Añadimos muestreo de Acceso a Log:
        
        ![Untitled](Imagenes/Untitled%2051.png)
        
        ![Untitled](Imagenes/Untitled%2052.png)
        
    5. Añadimos el Gestor de Cabecera HTTP para obtener los datos de los administradores:
        
        ![Untitled](Imagenes/Untitled%2053.png)
        
        ![Untitled](Imagenes/Untitled%2054.png)
        
    6. Añadimos la espera aleatoria:
        
        ![Untitled](Imagenes/Untitled%2055.png)
        
        ![Untitled](Imagenes/Untitled%2056.png)
        
        1. Añadimos los apartados de análisis:
        
        ![Untitled](Imagenes/Untitled%2057.png)
        
    
    Al final queda:
    
    ![Debe quedar igual al del repo iseP4 de github](Imagenes/Untitled%2058.png)
    
    Debe quedar igual al del repo iseP4 de github
    
    Ejecutamos el test y visualizamos los datos:
    
    ![Untitled](Imagenes/Untitled%2059.png)
    
    ![Si todo sale verde es que está perfe. Si os da valores en rojo significa que no va bien, revisadlo](Imagenes/Untitled%2060.png)
    
    Si todo sale verde es que está perfe. Si os da valores en rojo significa que no va bien, revisadlo
    
    En caso de que no os salga bien, mirad en la terminal con el servidor y analizar los errores que da. Al final explico al detalle que es cada error.
    
    En el servidor podemos ver todas las peticiones:
    
    ![Si os da error veréis errores `400`, `401`, `404` o `500`](Imagenes/Untitled%2061.png)
    
    Si os da error veréis errores `400`, `401`, `404` o `500`
    

**POSIBLE PREGUNTA DE EXAMEN**: explicar errores del servidor (el que avisa no es traidor)

### Docker para rocky

```bash
dnf install podman
dnf install pip
sudo pip install podman-compose
```

## Fine Tuning[muy opcional]

Documentación:

[Optimización en moodle](https://docs.moodle.org/33/en/Performance_recommendations)

[Optimización en wordpress](https://codex.wordpress.org/WordPress_Optimization)

[Apache tuning](https://httpd.apache.org/docs/current/misc/perf-tuning.html)

[MariaDB tuning](https://mariadb.com/kb/en/optimization-and-tuning/)

![Untitled](Imagenes/Untitled%2062.png)

Hay varios parámetros que podemos tocar para mejorar la funcionalidad del sistema:

### Hardware

- Para servidores Web es recomendable mucha RAM para evitar el swap.
- Aumentar el procesador (más nucleos) y habilitar hyperthreading.
- Usar SCSI hard disks en vez de SATA. Los SCSI llevan su propio procesador para gestionar multiples discos y consultas propias. Sino aprovechar el NCQ (Native Command Queuing).
- Comprar discos con la menor latencia posible
- Tener un swap file/partition. Moodle recomienda 4x la RAM fisica.
- Usar un RAID-1 y 5
- Usar un cable Gigabit de internet, sobre todo entre diferentes servidores
- Aumentar el uso de buffers y descriptores de la tarjeta de red

### Software

- Recomiendan añadir plugins de cache como `W3 Total Cache` o `WP Super Cache` para reducir la carga del procesador mediante ficheros de caché.
- Moodle recomienda Solaris como SO para un servidor
- Instalar firefox & firebug para ver el tiempo de carga de las paginas.

### PHP

- Usar el sistema de archivos **TMPFS.**
- Nos recomiendan muy fuertemente usar `PHP accelerator` para facilitar la carga de la CPU.
- PHP funciona mejor al instalarlo como un módulo de Apache.
- En php.ini, reducir el límite de memoria a 40M (por defecto es 128)

### Apache

- Modificar el **MaxRequestWorkers** con la formula:
    
    $\text{MaxRequestWorkers} = \frac{\text{Total available memory} · 80}{ \text{Max memory usage of apache process}}$
    Por defecto el denominador es 10M pero puede subir a 100M
    
- Reducir el numero de modilos que apache carga en el `httpd.conf`
- Para reducir las IDLEs connection, poner `KeepAlive off` o reducir el `timeout`
- Cambiar el HostnameLookups a off(on por defecto). Reduce la latencia.
- Añadir las opciones ****FollowSymLinks**** and ****SymLinksIfOwnerMatch**** para evitar llamadas extra al sistema.
- Usar el sistema de archivos **XFS**.

### MariaDB

Lo más importante para un servidor es la RAM, la velocidad de los discos y las [variables del sistema](https://mariadb.com/kb/en/system-variables/).

- Usar el `pool of threads` para muchas queries cortas.
`thread-handling=pool-of-threads`
- Set swappiness a 0. Queremos evitar el swapping.
- Usar `none scheduler` para reducir la latencia en el disco.
- Aumentar los limites de los descriptores que usualmente superar el por defecto 1024.

No tengo tiempo ni ganas de aplicar los cambios y hacer más benchmarks. Con esto es suficiente.

# Extender disco

Documentacion: [https://www.redhat.com/sysadmin/resize-lvm-simple](https://www.redhat.com/sysadmin/resize-lvm-simple)

Crear disco de 10G y meterlo en ubuntu.

Ejecutar:

```bash
lsblk -f
```

![El disco a ampliar es quien tenga /. Quédate con el formato de FSTYPE(xfs o ext4). El mío es xfs](Imagenes/Untitled%2063.png)

El disco a ampliar es quien tenga /. Quédate con el formato de FSTYPE(xfs o ext4). El mío es xfs

```bash
sudo vgdisplay
sudo vgextend vg0 /dev/sdc #Ampliar vg
```

![Untitled](Imagenes/Untitled%2064.png)

```bash
sudo lvdisplay; sudo lvextend -l +100%FREE /dev/vg0/raiz #Ampliar lv
#Recuerda si tu fs es xfs o ext4 y ejecuta un comando
```

![Untitled](Imagenes/Untitled%2065.png)

```bash
sudo xfs_growfs /dev/vg0/raiz #Ampliar sistema de archivos si es xfs
#
sudo resize2fs /dev/vg0/raiz #Ampliar sistema de archivos si es ext4
```

![Untitled](Imagenes/Untitled%2066.png)

### Problemas

1. **Codigos devueltos por el servidor (`IMPORTANTE`):**
    
    ![Buscamos que devuelva codigo `200`, que es el valor de OK](Imagenes/Untitled%2067.png)
    
    Buscamos que devuelva codigo `200`, que es el valor de OK
    
     0.  Código `304`: No modificado/Not Modified
    
    No es un error como tal. Sucede cuando accedes la web ([http://192.168.56.105:3000/](http://192.168.56.105:3000/)) y no ha cambiado desde la última consulta. Entonces el navegador carga la versión cargado en caché de nuestro ordenador.
    
    ![Untitled](Imagenes/Untitled%2068.png)
    
    Devuelve el código `200` cuando hacemos hard reload: Ctrl+f5 en el browser.
    
    ![Este codigo 404 not found no nos afecta, ignoralo](Imagenes/Untitled%2069.png)
    
    Este codigo 404 not found no nos afecta, ignoralo
    
    1. Error `400`: Solicitud errónea/Bad request
        
        ![Untitled](Imagenes/Untitled%2070.png)
        
        ![Untitled](Imagenes/Untitled%2071.png)
        
        1. Bad request(POST): content-type vacío o incorrecto:
            
            ![Corregido: -H "Content-Type: application/x-www-form-urlencoded”](Imagenes/Untitled%2072.png)
            
            Corregido: -H "Content-Type: application/x-www-form-urlencoded”
            
        2. Bad request(GET): url incorrecta:
            
            ![He puesto 41. Cualquier número que no empiece por 40 dará este error. 
            Corregido: mariweiss%40tropoli.com](Imagenes/Untitled%2073.png)
            
            He puesto 41. Cualquier número que no empiece por 40 dará este error. 
            Corregido: mariweiss%40tropoli.com
            
            ![Untitled](Imagenes/Untitled%2071.png)
            
        3. Failed to decode param: número despues del % menor a 10 o vacío
            
            ![He puesto %5. Cualquier número inferior a 2 dígitos dará este error. % lee dos números
            Corregido: mariweiss%40tropoli.com](Imagenes/Untitled%2074.png)
            
            He puesto %5. Cualquier número inferior a 2 dígitos dará este error. % lee dos números
            Corregido: mariweiss%40tropoli.com
            
            ![Aqui se ve bien el error por número. Uno da `400` y otro `404`(es directorio incorrecto)](Imagenes/Untitled%2075.png)
            
            Aqui se ve bien el error por número. Uno da `400` y otro `404`(es directorio incorrecto)
            
    2. Error `401`: Error de autenticación/Bad auth
        
        ![Untitled](Imagenes/Untitled%2076.png)
        
        ![Untitled](Imagenes/Untitled%2077.png)
        
        1. No hace nada: (-u) el nombre del usuario o contraseña(de la API) es incorrecto
            
            ![usuario y contraseña vacios
            Corregido: -u etsiiApi:laApiDeLaETSIIDaLache](Imagenes/Untitled%2078.png)
            
            usuario y contraseña vacios
            Corregido: -u etsiiApi:laApiDeLaETSIIDaLache
            
        2. Unauthenticed request: (-H) Sinxtaxis de la solicitud incorrecta
            
            ![Falta la opcion -H, da mismo error si no pones “Authorization: Bearer” o lo pones mal. 
            El token incorrecto no genera este error sino el `500`
            Corregido: curl -H “Authorization: Bearer $TOKEN”](Imagenes/Untitled%2079.png)
            
            Falta la opcion -H, da mismo error si no pones “Authorization: Bearer” o lo pones mal. 
            El token incorrecto no genera este error sino el `500`
            Corregido: curl -H “Authorization: Bearer $TOKEN”
            
    3. Error `404`: No encontrado/Not found
        
        ![Untitled](Imagenes/Untitled%2080.png)
        
        ![Untitled](Imagenes/Untitled%2081.png)
        
        1. Invalid credentials: usuario o contraseña (alumno del servidor) incorrectos
            
            ![La cadena pasada a -d no existe/incorrecta
            Corregido: "[login=mariweiss@tropoli.com](mailto:login=mariweiss@tropoli.com)&password=anim"](Imagenes/Untitled%2082.png)
            
            La cadena pasada a -d no existe/incorrecta
            Corregido: "[login=mariweiss@tropoli.com](mailto:login=mariweiss@tropoli.com)&password=anim"
            
        2. Not found: directorio del servidor incorrecto o Metodo de solicitud (POST o GET) incorrecto
            
            ![He puesto GET, eso no va ahí. Da el mismo error si la cadena posterior no es correcta
            Corregido: -X POST](Imagenes/Untitled%2083.png)
            
            He puesto GET, eso no va ahí. Da el mismo error si la cadena posterior no es correcta
            Corregido: -X POST
            
            ![Untitled](Imagenes/Untitled%2084.png)
            
        3. El alumno no existe: mismo error del directorio pero al hacer la parte GET del curl
            
            ![No es .es sino .com.
            Corregido: mariweiss%40tropoli.com](Imagenes/Untitled%2085.png)
            
            No es .es sino .com.
            Corregido: mariweiss%40tropoli.com
            
            ![El numero es 40 (% lee dos digitos) y la cadena/directorio empieza por 0. Un número que sea distinto de 40 dará error `400`](Imagenes/Untitled%2086.png)
            
            El numero es 40 (% lee dos digitos) y la cadena/directorio empieza por 0. Un número que sea distinto de 40 dará error `400`
            
    4. Error `**500**`: Error interno en el servidor web/Internal Web Server Error
        
        ![Untitled](Imagenes/Untitled%2087.png)
        
        ![Untitled](Imagenes/Untitled%2088.png)
        
        1. Signature verification failed: (-H) el token pasado es incorrecto
            
            ![Me he inventado el token, está mal
            Corregido: mete el token que te devuelve el POST](Imagenes/Untitled%2089.png)
            
            Me he inventado el token, está mal
            Corregido: mete el token que te devuelve el POST
            
        2. Unexpected token � in JSON: hay algún simbolo desconocido en el token y en un sitio muy específico. Es díficil sacar este error
            
            ![Accidentalmente puse tilde a una k y dió internal error](Imagenes/Untitled%2090.png)
            
            Accidentalmente puse tilde a una k y dió internal error
            
    5. No devuelve ni error ni el token esperado:
        
        ![Cadena del POST vacia
        Corregido: [http://192.168.56.105:3000/api/v1/auth/login](http://192.168.56.105:3000/api/v1/auth/login)](Imagenes/Untitled%2091.png)
        
        Cadena del POST vacia
        Corregido: [http://192.168.56.105:3000/api/v1/auth/login](http://192.168.56.105:3000/api/v1/auth/login)
        
        ![Protocolo https no es, es http](Imagenes/Untitled%2092.png)
        
        Protocolo https no es, es http
        
    6. Un error de no route to host siempre será por escribir mal la dirección ip o el puerto. O el puerto no está abierto
        
        ```bash
        sudo ufw allow 3000/tcp
        sudo firewall-cmd --zone=public --permanent --add-port 3000/tcp
        ```
        
    7. Error desconocido: comentamelo y lo añado.
    
2. Error: "value not allowed: *'org.apache.jmeter.protocol.http.util.accesslog.tclogparser' is not in []”* al añadir el muestreador de Acceso a Log en JMeter.
Causa: la app se bugea
Solucion: cierra JMeter y vuelve a abrirlo