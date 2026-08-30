#!/usr/bin/env bash
clear

# path to this file
cwd=$(dirname $(realpath $0))
bindir="$(dirname $(realpath $2))"

if [[ "$2" == "list" ]]; then
    echo -----------------------------------------------------------------------------------------
    echo Listado de programas 
    echo -----------------------------------------------------------------------------------------
    echo
    ls -l ../../test/*.asm | awk '{print "    "  NR "   [" $9 "]"}'
    echo -----------------------------------------------------------------------------------------
else
    arch="$(ls -l ../../test/*.asm | awk '{print NR, $9}' | grep "^$2 " | awk '{print $2}')"
    echo "  [${arch}]"
    if [[ "$arch" != "" ]]; then
        $1 -f $arch -D -a 
    fi
fi
