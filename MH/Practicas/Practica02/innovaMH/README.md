# innovaMH

Proyecto de Innovación Docente para faciltar el aprendizaje de Metaheurísticas.

Nota: este repositorio es un mirror de mi propio repositorio en
[fossil](https://fossil-scm.org/), por favor, no hacer pull request, es mejor
usar Issues, o contactarme a dmolinac at ugr.es.

Este documento forma parte del **Proyecto de Innovación Docente Desarrollo de herramientas web interactivas para el aprendizaje de Metaheurísticas** asociado a la asignatura de Metaheurísticas que se imparte para el _Grado en Ingeniería Informática_ (aunque abierta a grados dobles) en la **Universidad de Granada (UGR)**.

En este sistema interactivo se mostrará cómo se puede aplicar un problema concreto, el _Viajante de Comercio_ para resolverlo con distintas metaheurísticas, algo semejante a lo que tienen que hacer los y las estudiantes de la asignatura, pero con problemas distintos. Al igual que las prácticas de la asignatura, este entorno web está dividido en tres partes, cada una de ellas abordando distintas metaheurísticas sobre el mismo problema.

## Instrucciones

Este documento está en formato [Pluto](https://plutojl.org/) para ofrecer un entorno reactivo, lo cual quiere decir que se pueden pulsar botones o cambiar valores usando elementos visuales (como Select, sliders, ...) y el sistema se
actualiza.

El código fuente disponible está en el lenguaje de programación [Julia](https://julialang.org/), que es muy similar a Python. Lo he escogido porque es muy legible, similar al seudocódigo pero al mismo tiempo es ejecutable. Se puede seleccionar *Edit in binder* y se podrá editar en una copia local.

## Instalación

Hay dos formas de instalarlo.

### Usando docker/podman

La primera opción es ejecutarlo en un contenedor usando
[docker](https://www.docker.com/) o [podman](https://podman.io/). Personalmente
lo uso con podman pero ambos presentan el mismo interfaz. Lo bueno que presenta
es que no es necesario instalar nada localmente.

El proceso es el siguiente (pongo docker pero usando podman funcionaría igual):

```
$ docker build -t innova_mh .
```

Tras varios minutos habrá instalado una nueva imagen. Luego para ejecutarlo con:

```
$ docker run -it --rm -p 1234:1234 innova_mh
```

Una vez ejecutado verá un mensaje como:

```
Go to http://0.0.0.0:1234/?secret=xxxxxx in your browser to start writing ~ have fun!
```

Escriba en su navegador la dirección http://127.0.0.1:134/?secret=xxxxxx (lo que
le salga) y disfrute.

### Instalando Julia en el ordenador actual

La otra opción es instalando [julia](https://julialang.org/). Se puede instalar
de la propia web, aunque recomiendo instalarlo usando
[juliaup](https://github.com/JuliaLang/juliaup) que es una aplicación que
permite instalar y actualizar la versión de Julia.

Una vez instalado el proceso es sencillo:

Instalando julia:

```sh
$ juliaup add release
```

Luego basta con hacer lo siguiente:

```sh
$ bash run_pluto.sh
```

El navegador debería de cargarse directamente. Si no es así vea el mensaje del
enlace y póngalo en su navegador, tal y como se detalla en el apartado anterior.

# Notebooks a cargar

Este proyecto include dos notebooks:

- part1.jl: Muestra cómo resolver el problema del viajante de comercio usando
  una Búsqueda Local.
- part2.jl: Muestra cómo resolver el mismo problema utilizando Algoritmos
  Genéticos.

Si se ha instalado localmente dichos ficheros se encuentran donde haya
descargado este proyecto. Si los ejecuta desde docker/podman la ruta para
cargarlos es /app/part1.jl y /app/part2.jl, respectivamente.
