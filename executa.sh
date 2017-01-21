#!/bin/bash

gcc main.c estruturas.c automato.c lexico.c sintatico.c tabelapreditiva.c gerador-intermediario.c semantico.c -o compilador -w
./compilador -f ee.d 
