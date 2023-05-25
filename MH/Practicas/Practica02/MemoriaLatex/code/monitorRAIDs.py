import re
import sys
f=open('/proc/mdstat')
for line in f:
    b=re.findall('\[[U]*[_]+[U]*\]',line)
    if(b!=[]):
        print("---ERROR_en_RAID---")
        sys.exit()
print("---OK_Script---")
