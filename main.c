#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"
#include "lexico.h"
#include "sintatico.h"

int main(int argc, char** argv) {
    
    char nomeArquivo[30] = {'e', 'e', '.', 'd'};
    FILE * arquivo;
    if ((arquivo = fopen(nomeArquivo, "r")) == NULL) {
        printf("Arquivo não encontrado!");
    }
    arquivo_leitura(arquivo);

    Token x1 = getToken();
    Token x2 = getToken();
    Token x3 = getToken();
    Token x4 = getToken();
    Token x5 = getToken();
    
    Tree* r = create_tree(NULL, x1);
    add_son(r, x1, x2);
    add_son(r, x1, x3);
    add_son(r, x1, x4);
    add_son(r, x4, x5);
    
    
    reduce_tree(r);

    
    return (EXIT_SUCCESS);
}

