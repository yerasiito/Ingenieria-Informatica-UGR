# Practica 4, Ejercicio 2: ejecutable sin comprobaciones

# Automatizar las modificaciones a los dos saltos
# Pensado para ejecutar mediante "source bomba.gdb"
# o desde linea de comandos con gdb -q -x bomba.gdb
# Renombrar temporalmente el fichero "bomba-gdb.gdb"
# para que no se cargue automat. al hacer "file bomba"

### permitir escribir en el ejecutable
    set write on
### reabrir ejecutable con permisos r/w
    file bomba
### comprobar las direcciones a cambiar
    x/i 0x4007ce
    x/i 0x40084b
### realizar los cambios
#   set *(char*)0x4007ce=0xeb
#   set *(char*)0x40084b=0xeb
    set  {char} 0x4007ce=0xeb
    set  {char} 0x40084b=0xeb
### comprobar las instrucciones cambiadas
    x/i 0x4007ce
    x/i 0x40084b
### salir para desbloquear el ejecutable
    quit
