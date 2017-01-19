#!/bin/bash

gcc main.c estruturas.c automato.c lexico.c sintatico.c tabelapreditiva.c -o compilador -w && ./compilador
./compilador -f ee.d 
