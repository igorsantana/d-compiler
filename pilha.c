#include <stdlib.h>
#include <stdio.h>
#include "lexico.h"

typedef struct Elemento Elemento;
typedef struct Pilha Pilha;

void empilha(Pilha* pilha, Caracter caracter);
Elemento* desempilha(Pilha* pilha);
Pilha inicializa_pilha(caracter t);

struct Elemento {
    caracter caracter;
    Elemento *abaixo;
    Elemento *acima;
};

struct Pilha {
    Elemento* topo;
};

Pilha inicializa_pilha(caracter t) {
    Pilha p;
    p.topo = malloc(sizeof (Elemento));
    p.topo->caracter = t;
    return p;
}

void empilha(Pilha* pilha, caracter caracter) {
    Elemento* topo = pilha->topo;
    topo->acima = (Elemento*) malloc(sizeof (Elemento));
    topo->acima->caracter = caracter;
    topo->acima->abaixo = topo;
    pilha->topo = topo->acima;
}

Elemento* desempilha(Pilha* pilha) {
    if (pilha->topo == NULL) return NULL;

    Elemento* topo_atual = pilha->topo;
    pilha->topo = topo_atual->abaixo;
    return topo_atual;
}