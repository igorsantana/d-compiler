#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"
#include "lexico.h"
#include "sintatico.h"
#include "gerador-intermediario.h"

int main(int argc, char** argv) {
    
    char nomeArquivo[30] = {'e', 'e', '.', 'd'};
    FILE * arquivo;
    if ((arquivo = fopen(nomeArquivo, "r")) == NULL) {
        printf("Arquivo não encontrado!");
    }
    arquivo_leitura(arquivo);

    Tree* arvore = preditivoDescendente();
    
    gerador_intermediario(arvore);
    
//    Token x1 = getToken();
//    Token x2 = getToken();
//    Token x3 = getToken();
//    Token x4 = x3;
//    Token x4 = getToken();
//    Token x5 = getToken();
//    
//    Tree* r1 = create_tree(NULL, x1);
//    Tree* r2 = create_tree(NULL, x2);
//    Tree* r3 = create_tree(NULL, x3);
//    
//    Tree* r4 = create_tree(NULL, x4);
//    
//    ItemLista* l1 = create_list(r1);
//    add_list(l1,r4);
//    ItemLista* l2 = create_list(r2);
//    add_list(l2,r3);
//    
//    l1 = concat_list(l1,l2);
//    
//    print_list(l1);
//    add_son(r, x1, x2);
//    add_son(r, x1, x3);
//    add_son(r, x1, x4);
//    add_son(r, x4, x5);
    
    
//    reduce_tree(r);

    
    return (EXIT_SUCCESS);
}

