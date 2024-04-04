#!/bin/bash
make num_elem=1 ejecutar > tiempos.dat
make num_elem=10 ejecutar >> tiempos.dat
make num_elem=100 ejecutar >> tiempos.dat
make num_elem=1000 ejecutar >> tiempos.dat
make num_elem=2000 ejecutar >> tiempos.dat
make num_elem=4000 ejecutar >> tiempos.dat
make num_elem=8000 ejecutar >> tiempos.dat
make num_elem=16000 ejecutar >> tiempos.dat
make num_elem=32000 ejecutar >> tiempos.dat
