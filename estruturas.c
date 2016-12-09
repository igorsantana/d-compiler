#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "estruturas.h"

/* COMEÇO FUNÇÕES RELACIONADAS A PILHA */
Pilha       inicializa_pilha(char * t);
Elemento*   desempilha(Pilha* pilha);
void        empilha(Pilha* pilha, char * elemento);

Pilha inicializa_pilha(char * t) {
    Pilha p;
    p.topo = malloc(sizeof (Elemento));
    strcpy(p.topo->c, t);
    return p;
}
Elemento* desempilha(Pilha* pilha) {
    if (pilha->topo == NULL) return NULL;

    Elemento* topo_atual = pilha->topo;
    pilha->topo = topo_atual->abaixo;
    return topo_atual;
}
void empilha(Pilha* pilha, char * elemento) {
    Elemento* topo = pilha->topo;
    topo->acima = (Elemento*) malloc(sizeof (Elemento));
    strcpy(topo->acima->c, elemento);
    topo->acima->abaixo = topo;
    pilha->topo = topo->acima;
}
/* FIM FUNÇÕES RELACIONADAS A PILHA */



