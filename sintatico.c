#include <stdio.h>
#include "tabelaPreditiva.h"
#include "pilha.h"
#include "lexico.h"

Pilha pilha = inicializa_pilha(caracter '$');

void preditivoDescendente() {
    Token a = getToken();
    Elemento * X = pilha.topo;
    while (X->caracter != '$') {
        if (strcmp(X->caracter, a.token) == 0) {
            desempilha(pilha);
        } else if (strcmp() != 0) {
            printf("Símbolo inválido");
        } else if (matrizPreditiva[X][a].indexCaracter <= 0) {
            printf("Erro. erro de gramática");
        } else if (matrizPreditiva[x][a].indexCaracter > 0) {
            desempilha(pilha);
            for (int i = 0; i < matrizPreditiva[x][a].indexCaracter; i++) {
                empilha(pilha, matrizPreditiva[x][a].caracter[i]);
            }
        }
    }
}
