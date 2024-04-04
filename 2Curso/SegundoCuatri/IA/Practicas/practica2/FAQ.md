# Frequently Asked Questions

Algunos problemas comunes hasta el momento con el uso de Github o la realización de la práctica.

## Relacionados con la Práctica 2

### Nivel 1 (Batería insuficiente)

El plan con el mínimo número de acciones puede dar lugar a un camino que exige más batería de la disponible. El objetivo de este nivel es exclusivamente encontrar el camino con el mínimo número de acciones. Para superar este nivel, no es necesario implementar variaciones que permitan alcanzar el objetivo.

## Relacionados con Github

### Error fatal: not a git repository (or any of the parent directories): .git

Este error ocurre cuando tratais de hacer un git commit (o cualquier otro comando git) desde una carpeta inadecuada. Las carpetas git deben tener un fichero .git que contiene la configuración necesaria para ser consideradas como un repositorio.

### Error SSH:

Configurar la clave ssh es solo una ayuda para evitar tener que usar usuario y contraseña en cada ocasión. Toda la información está en [Conectar a GitHub con SSH](https://docs.github.com/es/authentication/connecting-to-github-with-ssh) y teneis una lista de errores comunes en: [SSH Troubleshooting](https://docs.github.com/es/authentication/troubleshooting-ssh)


## Otros sistemas operativos

### Arch linux

Para poder compilar y ejecutar la práctica en Arch Linux, es necesario realizar un par de cambios en los ficheros proporcionados.
- En [CMakeLists.txt](CMakeLists.txt) hay que incluir `-lglut` al final de la línea 62 para que quede así: `set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11 -lglut")`
- En [install.sh](install.sh) hay que cambiar `apt-get install ...` por `sudo pacman -Sy freeglut libjpeg openmpi openmpi libxmu libxi boost`. Algunos paquetes cambian de nombre con respecto a Ubuntu, pero funcionan.
