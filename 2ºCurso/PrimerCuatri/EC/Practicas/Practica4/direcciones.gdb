#cargar programa
file bomba
br main
run
#primera bomba
br *main+108
cont
# password -> 0x404068
set $eax=0

#segunda bomba
br *main+142
cont
set $eax=0

#tercera bomba
br *main+226
cont
# Introducir 0000
set $eax=0000
# pin->0x404060

#cuarta y ultima bomba
br *main+262
cont
set $eax=0
cont
