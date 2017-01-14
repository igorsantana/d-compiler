#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "lexico.h"
#include "sintatico.h"

int main(int argc, char** argv) {
    
//    char nomeArquivo[30] = {'e', 'e', '.', 'd'};
//    FILE * arquivo;
//    if ((arquivo = fopen(nomeArquivo, "r")) == NULL) {
//        printf("Arquivo não encontrado!");
//    }
//    arquivo_leitura(arquivo);

//    preditivoDescendente();
    
    Escopo*       lista  = create_escopo();
    
    add_escopo(lista, "main",     0);
    add_escopo(lista, "funcao_1", 1);
    add_escopo(lista, "funcao_2", 2);
    add_escopo(lista, "if"      , 3);
    
    ItemVariavel* variaveis = create_lista();
    
    add_variavel(variaveis, "a");
    add_variavel(variaveis, "b");
    add_variavel(variaveis, "c");
    add_variavel(variaveis, "d");
    
    add_item(variaveis, "a", create(0, "INTEGER", "VAR", (void*) 1));
    add_item(variaveis, "a", create(1, "INTEGER", "VAR", (void*) 4));
    add_item(variaveis, "a", create(2, "INTEGER", "VAR", (void*) 5));
    add_item(variaveis, "a", create(3, "INTEGER", "VAR", (void*) 7));
    
    add_item(variaveis, "b", create(3, "INTEGER", "VAR", (void*) 2));
    
    add_item(variaveis, "c", create(0, "STRING", "VAR", (void*) "TESTE 1"));
    add_item(variaveis, "c", create(3, "STRING", "VAR", (void*) "TESTE 2"));
    
    add_item(variaveis, "d", create(1, "INTEGER", "VAR", (void*) 7));
    add_item(variaveis, "d", create(3, "STRING",  "VAR", (void*) "TESTE 3"));
    
    int a = (int) get_valor(variaveis, "a", get_escopo(lista, "main")->profundidade);
    printf("Valor 1 = %i\n", a);
    
        a = (int) get_valor(variaveis, "a", get_escopo(lista, "funcao_1")->profundidade);
    printf("Valor 2 = %i\n", a);
    
    a = (int) get_valor(variaveis, "a", get_escopo(lista, "funcao_2")->profundidade);
    printf("Valor 3 = %i\n", a);
    
    a = (int) get_valor(variaveis, "a", get_escopo(lista, "if")->profundidade);
    printf("Valor 4 = %i\n", a);
    
    int b = (int) get_valor(variaveis, "b", get_escopo(lista, "if")->profundidade);
    printf("Valor 5 = %i\n", b);
    
    char* c = (char*) get_valor(variaveis, "c", get_escopo(lista, "main")->profundidade);
    printf("Valor 6 = %s\n", c);
    
          c = (char*) get_valor(variaveis, "c", get_escopo(lista, "if")->profundidade);
    printf("Valor 7 = %s\n", c);
    
    b = (int) get_valor(variaveis, "d", get_escopo(lista, "funcao_1")->profundidade);
    printf("Valor 8 = %i\n", b);
    
    c = (char*) get_valor(variaveis, "d", get_escopo(lista, "if")->profundidade);
    printf("Valor 9 = %s\n", c);
    
//    Escopo* main      = get_escopo(lista, "main");
//    Escopo* funcao_1  = get_escopo(lista, "funcao_1");
//    Escopo* funcao_2  = get_escopo(lista, "funcao_2");
//    Escopo* funcao_if = get_escopo(lista, "if");
    
//    printf("%s - %i\n", &main->nome, main->profundidade);        
//    printf("%s - %i\n", &funcao_1->nome, funcao_1->profundidade);        
//    printf("%s - %i\n", &funcao_2->nome, funcao_2->profundidade);        
//    printf("%s - %i\n", &funcao_if->nome, funcao_if->profundidade);        
//    // Testes:
//    char* tipo;
//    char* categoria;
//    
//    strcpy(&tipo, "INTEGER");
//    strcpy(&categoria, "VARIAVEL");
//    
//    ValorVariavel* variavel_1 = create(0, "INTEGER", "variavel", (void*) 0);
//    ValorVariavel* variavel_2 = create(0, "FLOAT"  , "variavel", (void*) 1);
//    ValorVariavel* variavel_3 = create(3, "STRING" , "variavel", (void*) "ABC");
//    ValorVariavel* variavel_4 = create(0, "VECTOR" , "variavel", (void*) 0);
////    
//    ItemVariavel* raiz = create_lista();
//
//    char* nome_1; strcpy(&nome_1, "A");
//    char* nome_2; strcpy(&nome_2, "B");
//    char* nome_3; strcpy(&nome_3, "A");
//    char* nome_4; strcpy(&nome_4, "C");
//    char* nome_5; strcpy(&nome_5, "D");
//    
//    add_variavel(raiz, &nome_1);
//    add_variavel(raiz, &nome_2);
//    add_variavel(raiz, &nome_3);
//    add_variavel(raiz, &nome_4);
//    
//    print_variavel(raiz);
//    
//    add_item(raiz, &nome_1, variavel_1);
//
//    add_item(raiz, &nome_2, variavel_1);
//    
//    add_item(raiz, &nome_4, variavel_2);
//    add_item(raiz, &nome_4, variavel_3);
//    
//    add_item(raiz, &nome_5, variavel_3);
//    

    
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

