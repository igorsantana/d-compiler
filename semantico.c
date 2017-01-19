#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

int inc_escopo = 0;

Tree* executa_semantico(Tree* arvore);
char* get_nome_escopo();

Tree* executa_semantico(Tree* arvore) {
    Escopo*       raiz_escopo   = create_escopo();
    ItemVariavel* raiz_variavel = create_lista();
    
    printf("%s\n", get_nome_escopo());
    printf("%s\n", get_nome_escopo());
    
    return arvore;
}

void analisa_arvore(Tree* arvore) {
    if (strcmp(arvore->token.token, "{") == 0) {
        printf("ESCOPO");
    }
    if (strcmp(arvore->token.token, "=") == 0) {
        printf("ATRIBUICAO");
    }
    
}

char* get_nome_escopo() {
    char* to_return;
    sprintf(to_return, "scope%i", inc_escopo);
    inc_escopo++;
    return to_return;
}