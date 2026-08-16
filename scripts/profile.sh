#!/usr/bin/env bash

# path to this file
cwd=$(dirname $(realpath $0))
libspath="../../run/libs/bin"
bindir="$(dirname $(realpath $1))"

export LD_LIBRARY_PATH="${cwd}/${libspath}"

clear
echo "current dir      : ${PWD}"
echo
echo "scripts dir      : ${cwd}"
echo "libs dir         : ${libspath}"
echo "LD_LIBRARY_PATH  : $(realpath ${LD_LIBRARY_PATH})"
echo
echo "running          : $(dirname $(realpath $1))"
echo "running          : $(basename $1)"

echo "--------------------------------------------------------------------- >>>"
time {
	valgrind --leak-check=full --log-file="./analisis" -s $1 $2 
echo "<<< ------------------------------------------------------------------END"
}
