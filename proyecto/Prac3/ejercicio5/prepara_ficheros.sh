#!/bin/bash

directorio="$1" #primer argumento pasado por param

if [ -d "$directorio" ]; then
    rm -r "$directorio"  # Borra todo lo que tiene
else
    mkdir "$directorio"
fi

mkdir "$directorio/subdir"
touch "$directorio/fichero1"
touch "$directorio/fichero2"
echo "QWERTYUIOP" > "$directorio/fichero2"
ln -s "$directorio/fichero2" "$directorio/enlaceS"  #enlace simbolico
ln "$directorio/fichero2" "$directorio/enlaceH" #enlace duro

for archivo in $directorio/*
do
    echo "Archivo:$archivo"
    stat "$archivo"
    echo "--------------------------------"
done

# 1) el fichero 1 ocupa 0 bloques y 0 bytes porque está vacio y el fichero 2 tiene 0 bloques y un tamaño de 11 bytes
# 2) el tamaño de subdir es 4096 bytes
# 3) El fichero2 y enlaceh comparten el mismo nodo i