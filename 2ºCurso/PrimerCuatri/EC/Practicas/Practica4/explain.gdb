# Practica 4, Actividad 4.1: explicacion de la bomba

# CONTRASEÑA: abracadabra
# 	 PIN: 7777

# MODIFICADA: hola,adios.
#	 PIN: 123

# Describe el proceso logico seguido
# primero: para descubrir las claves, y
# despues: para cambiarlas 

# Pensado para ejecutar mediante "source explain.gdb"
# o desde linea de comandos con gdb -q -x explain.gdb
# Renombrar temporalmente el fichero "bomba-gdb.gdb"
# para que no se cargue automat. al hacer "file bomba"

# funciona sobre la bomba original, para recompilarla
# usar la orden gcc en la primera linea de bomba.c
# gcc -Og bomba.c -o bomba -no-pie -fno-guess-branch-probability

########################################################

### cargar el programa
    file bomba
### util para la sesion interactiva, no para source/gdb -q -x
#   layout asm
#   layout regs
### arrancar programa, notar automatizacion para teclear hola y 123
    br main
    run < <(echo -e hola\\n123\\n)
### hicimos ni hasta call boom, antes pide contraseña y tecleamos hola
### si entramos en boom explota y hay que empezar de nuevo
### la decision se toma antes, justo antes de call boom
### hay un je que se salta la bomba, y el test anterior
### activaria ZF si el retorno de strncmp produjera 0,
### es decir, si 0==strncmp(rdi,rsi,edx)
#   0x4007b6 <main+91>  lea   0x30(%rsp),%rdi
#   0x4007bb <main+96>  mov   $0xd,%edx
#   0x4007c0 <main+101> lea   0x2008a1(%rip),%rsi # 0x601068 <password>
#   0x4007c7 <main+108> callq 0x4005d0 <strncmp@plt>
#   0x4007cc <main+113> test  %eax,%eax
#   0x4007ce <main+115> je    0x4007d5 <main+122>
#   0x4007d0 <main+117> callq 0x400727 <boom>
#   0x4007d5 <main+122> lea   ...
### avancemos hasta strncmp para consultar los valores
    br *main+108
    cont
### escribir "hola" cuando pida contraseña, resuelto ya en run
### ahora mismo estamos viendo de donde sale la contraseña
### 0x4007c0 <main+101> lea 0x2008a1(%rip),%rsi # 0x601068 <password>
### imprimir la contraseña y recordar que esta en 0x601068 longitud 13B
#   p(char*    )$rsi
#   p(char*    )0x601068
    p(char[0xd])password
### dejar que strncmp salga mal y corregir eax=0 para evitar boom()
    ni
    set $eax=0
    ni
    ni
### siguiente bomba es por tiempo
#   0x4007df <main+132> callq  0x4005f0 <gettimeofday@plt>
#   0x4007e4 <main+137> mov    0x20(%rsp),%rax
#   0x4007e9 <main+142> sub    0x10(%rsp),%rax
#   0x4007ee <main+147> cmp    $0x5,%rax
#   0x4007f2 <main+151> jle    0x4007f9 <main+158>
#   0x4007f4 <main+153> callq  0x400727 <boom>
#   0x4007f9 <main+158> lea    ... 
### avanzar hasta el cmp
    br *main+147
    cont
### falsear tiempo=0 por si acaso se ha tardado en teclear
    set $eax=0
    ni
    ni
### siguiente bomba compara resultado scanf con variable de memoria
#   0x400841 <main+230> mov   0x200819(%rip),%eax # 0x601060 <passcode>
#   0x400847 <main+236> cmp   %eax,0xc(%rsp)
#   0x40084b <main+240> je    0x400852 <main+247>
#   0x40084d <main+242> callq 0x400727 <boom>
#   0x400852 <main+247> lea ...
### avanzar hasta cmp para consultar valores
    br *main+236
    cont
### escribir "123" cuando pida pin, resuelto ya en run
### imprimir el pin y recordar que esta en 0x601060 tipo int
#   p*(int*)0x601060
    p (int )passcode
### corregir sobre la marcha EAX para que cmp salga bien
    set $eax=123
    ni
    ni
### siguiente bomba es por tiempo
#   0x40085c <main+257> callq  0x4005f0 <gettimeofday@plt>
#   0x400861 <main+262> mov    0x10(%rsp),%rax
#   0x400866 <main+267> sub    0x20(%rsp),%rax
#   0x40086b <main+272> cmp    $0x5,%rax
#   0x40086f <main+276> jle    0x400876 <main+283>
#   0x400871 <main+278> callq  0x400727 <boom>
#   0x400876 <main+283> callq  0x400741 <defused>
#   0x40087b            nopl
### avanzar hasta el cmp
    br *main+272
    cont
### falsear tiempo=0 por si acaso se ha tardado en teclear
    set $eax=0
    ni
    ni
### hemos llegado a defused, fin del programa
    ni

########################################################

### permitir escribir en el ejecutable
    set write on
### reabrir ejecutable con permisos r/w
    file bomba
### realizar los cambios
    set {char[10]}0x6030b0="yerasito\n"
    set {int     }0x6030ac=7777
### comprobar las instrucciones cambiadas
    p (char[0xd])password
    p (int      )passcode
### salir para desbloquear el ejecutable
    quit

########################################################

