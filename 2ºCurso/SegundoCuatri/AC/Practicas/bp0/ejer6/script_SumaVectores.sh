#!/bin/bash

for((i=65536; i < 67108865; i*=2))
do
	./SumaVectores $i
	echo -e "\n"
done
