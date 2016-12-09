#include "sintatico.h"
#include "estruturas.h"
#include <stdio.h>

Pilha p;

void preditivoDescendente();

void preditivoDescendente() {
    p = inicializa_pilha("$");
    //    Elemento * X = pilha.topo;
    //    int indexX = retornaIndiceNT(X->caracter.c);
    //    int indexA = retornaIndiceT(a.token);
    //    while (X->caracter.c != '$') {
    //        if (strcmp(X->caracter.c, a.token) == 0) {
    //            desempilha(pilha);
    //        } else if (strcmp() != 0) {
    //            printf("Símbolo inválido");
    //        } else if (matrizPreditiva[indexX][indexA].indexCaracter <= 0) {
    //            printf("Erro. erro de gramática");
    //        } else if (matrizPreditiva[indexX][indexA].indexCaracter > 0) {
    //            desempilha(pilha);
    //            for (int i = 0; i < matrizPreditiva[indexX][indexA].indexCaracter; i++) {
    //                empilha(pilha, matrizPreditiva[indexX][indexA].caracter[i]);
    //            }
    //        }
    //    }
}