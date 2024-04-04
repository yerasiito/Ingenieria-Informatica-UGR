# Práctica 3 de *Inteligencia Artificial*, curso 2021/2022

Si has realizado la práctica1, y tienes la clave SSH configurada, puedes ir directamente al [paso 2](#2.-crear-tu-copia-personal-del-repositorio-de-la-asignatura).



## Prerrequisitos

### Crear una cuenta en [GitHub](https://github.com/). 
Para ello, puedes usar tu correo personal, el de *@correo.ugr.es* o el de *@go.ugr.es*.


### 1. Añadir tu clave SSH a GitHub
Hay varias maneras de conectarte desde tu ordenador a GitHub. Si utilizas un navegador, usarás tu usuario y contraseña. Desde el terminal, lo más cómodo es utilizar una clave SSH. Puedes crear una nueva si no tienes, o reutilizar una ya existente. Tienes toda la información para realizar la configuración en: 
[Conectar a GitHub con SSH](https://docs.github.com/es/authentication/connecting-to-github-with-ssh)


### 2. Crear tu copia personal del repositorio de la asignatura
Cada estudiante debe tener su propia copia del repositorio para poder trabajar sobre ella. En adelante, a tu copia la llamaremos *origin*, y al repositorio original de la asignatura lo llamaremos *upstream* (NOTA: Estas son convenciones que la mayoría de los desarrolladores usan, pero los puedes llamar como quieras). 

> La forma usual de crear tu copia del repositorio es realizando un *fork*. Sin embargo, dado que realizar un *fork* de un repositorio con visibilidad pública obliga al que la copia sea también pública, nosotros usaremos un procedimiento diferente que nos permite que nuestra copia del repositorio sea privada.

Para realizar la copia, una vez que tengas creada tu cuenta en GitHub, haz click en <https://github.com/new/import> y rellena tal y como se ve en la imagen de abajo. El repositorio que quieres importar es `https://github.com/ugr-ccia-IA/practica3`. ¡Asegúrate de que tu repositorio es privado!

![Importar repositorio practica3](doc/img/import_new_repo.png)


### 3. Clonar tu repositorio en tu máquina
Una vez hecho el paso anterior, tendrás tu repositorio personal de la práctica1 en GitHub; puedes descargarlo a tu ordenador usando:
`git clone git@github.com:TU_USUARIO_GITHUB/practica3.git` (si no has configurado tu clave SSH, esto no funcionará).


### 4. Modificar el código y guardar los cambios
Es el momento de empezar a modificar ficheros. Abre el fichero README.md (este fichero) y busca la línea 93. Debes cambiar el enlace que usa el botón para que apunte a tu repositorio y no al de la asignatura.
Una vez lo hayas modificado, guarda el fichero, y ejecuta los siguientes comandos en el terminal estando dentro de la carpeta `practica3`:

```
git add . 
git commit -m "Cambiando el enlace del botón"
git push origin main 
```

Los tres comandos anteriores le indican a git que 1) queremos guardar una nueva versión con todos los ficheros modificados de la carpeta, 2) que haga esa versión y le ponga el comentario "Cambiando el enlace del botón", y 3) que envíe esta nueva versión a la copia de nuestro repositorio alojada en GitHub.

Este proceso es el que debes repetir cada vez que vayas avanzando en la implementación de la práctica: add, commit, push.



### 5. Enlazar tu repositorio personal con el de la asignatura
Aunque tu repositorio y el de la asignatura (recuerda que los conocemos por *origin* y *upstream* respectivamente) sean independientes, nos va a interesar que estén enlazados. De esta forma, podrás aplicar fácilmente sobre tu repositorio (*origin*) cualquier actualización que los profesores realicemos en *upstream*. Para enlazarlos, ejecuta lo siguiente dentro de la carpeta de tu repositorio:

`git remote add upstream git@github.com:ugr-ccia-IA/practica3.git`


### Actualizar tu repositorio con cambios realizados en el de la asignatura
Una vez tengas los repositiorios enlazados, lo único que debes hacer para aplicar posibles cambios en el repositorio de la asignatura en tu repositorio (cambios de *upstream* en *origin*) es: `git pull upstream main`

Hacer esto no sobreescribirá tus avances en la implementación de la práctica, puesto que tú no deberías haber modificado ninguna parte del código diferente a la que se indica en el guión.

Si quieres que esos cambios también se guarden en github, a continuación ejecuta: `git push origin main`


> Si quieres saber más sobre Git y GitHub, en Internet existen multitud de recursos, incluidos videos y tutoriales. Para realizar esta práctica sólo necesitas lo básico (hacer commits), pero hay muchas cosas más que se pueden hacer con estas herramientas (uso de ramas, gestión de conflictos, etc.) 
El propio GitHub pone a tu disposición un [breve curso](https://classroom.github.com/a/W33pQ3pa) (en inglés) para aprender lo básico.


## Realización de la práctica
El guión (disponible en [PRADO](https://pradogrado2122.ugr.es/)) contiene toda la información sobre en qué consiste la práctica3. Leelo con atención.
También tienes a tu disposición un tutorial con los primeros pasos a realizar.


### Instalación local

En el guión y el tutorial tienes las instrucciones. 
El software usa la librería [SFML](https://www.sfml-dev.org/index.php), por lo que debes instalarla según tu versión de linux:
- Ubuntu/Debian: `sudo apt install libsfml-dev`
- Arch: `sudo pacman -S sfml`
- Fedora/CentOS/Suse: `sudo dnf -y install SFML-devel` o `sudo yum -y install SFML-devel`

Si ninguna de estas opciones te funciona, también hay otras [opciones de instalación](https://www.sfml-dev.org/tutorials/2.5/start-linux.php)

Cuando realices cualquier modificación en el código, debes recompilar, así que usa `make`.


### Instalación en máquina virtual
Si no tienes linux de forma nativa en tu ordenador, puedes crear una máquina virtual en tu ordenador (por ejemplo, usando VirtualBox), e instalar linux en ella. A partir de ahí, puedes trabajar dentro de ella como si tuvieras linux instalado de forma nativa.


### Desarrollo remoto con Gitpod
Si prefieres no instalar nada localmente, puedes usar [Gitpod](https://gitpod.io). Este es un servicio que no depende de los profesores de la asignatura y que no podemos garantizar que funcione perfectamente. Para ello, haz click en el siguiente botón (después de modificarlo para que apunte a tu repositorio y no al de la asignatura) y sigue las instrucciones.

<!-- IMPORTANTE: Debes cambiar en el siguiente enlace TUSUARIO por tu nombre de usuario en github!  -->
[![Abrir con Gitpod](https://gitpod.io/button/open-in-gitpod.svg)](https://gitpod.io/#https://github.com/TUSUARIO/practica3)

Una vez que el servidor remoto esté creado (la primera vez tardará un rato en configurarlo todo, las siguientes veces, debería ser más inmediato), verás un IDE completamente funcional en el navegador; puedes seguir usándolo, o usar VScode localmente si lo tienes instalado(aunque conectado al servidor Gitpod remoto). También, se te debería de haber abierto una nueva ventana en el navegador que te mostrará la interfaz gráfica del programa.

Si no se abre la ventana, copia la url del navegador y anteponle `6080-`. 
Por ejemplo, si la URL del IDE es `https://USUARIO-REPO-zzzzz.ws-eu34.gitpod.io` abriríamos en una nueva pestaña `https://6080-USUARIO-REPO-zzzzz.ws-eu34.gitpod.io`.


Si trabajas con Gitpod, ¡no olvides hacer commit de todos tus cambios para que se vayan guardando en tu repositorio!
