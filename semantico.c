#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

int             inc_escopo = 0;
Escopo*         raiz_escopo;
ItemVariavel*   raiz_variavel;

Tree*   executa_semantico(Tree* arvore);
char*   get_nome_escopo();
void    analisa_arvore(Tree* arvore, Escopo* pai);
int     get_escopo_atual();

int get_escopo_atual(){
    int atual = inc_escopo;
    inc_escopo++;
    return atual;
}

Tree* executa_semantico(Tree* arvore) {
    raiz_escopo     = create_escopo();
    raiz_variavel   = create_lista();
    analisa_arvore(arvore, NULL);
    printf("Nome: %s\n", raiz_variavel->nome);
    printf("Primeira declaração: %s\n", raiz_variavel->primeiro->escopo->nome);
    printf("Segunda declaração: %s\n",  raiz_variavel->primeiro->proximo->escopo->pai->nome);
    return arvore;
}

void analisa_arvore(Tree* arvore, Escopo* pai) {
    Escopo* current = pai;
    if (strcmp(arvore->token.token, "{") == 0) {
        current = add_escopo(raiz_escopo, get_nome_escopo(), -1, pai);
    }
    if (strcmp(arvore->token.token, "=") == 0) {
        ItemVariavel* v = get_variavel(raiz_variavel, arvore->filhos->token.token);
        if(v == NULL){
            add_variavel(raiz_variavel, arvore->filhos->token.token);
        }
        add_item(raiz_variavel, arvore->filhos->token.token,
                create(current, arvore->pai->token.categoria));
    }
    if(arvore->filhos != NULL){
        analisa_arvore(arvore->filhos, current);
    }
    if(arvore->irmaos != NULL){
        analisa_arvore(arvore->irmaos, current);
    }
    
}

char* get_nome_escopo() {
    char* to_return;
    to_return = malloc(32);
    snprintf(to_return,32, "%s_%i","scope", get_escopo_atual());
    
    return to_return;
}