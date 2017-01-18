#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "estruturas.h"
#include "lexico.h"
#include "sintatico.h"
#include "gerador-intermediario.h"

char* nomeArquivo;
int VERBOSE_MODE = 0;

void help();
void opcoes_entrada(int argc, char** argv);
void escreve_assembly(char* arq_sem_extensao);
void executa_assembly(char* arq_sem_extensao);  

void help(){
    printf("\nBem vindo ao compilador. Os comandos disponíveis são:\n");
    printf("\t-f\tFile\tExecuta o compilador para o arquivo de entrada. Exemplo: ./compilador -f <arquivo>\n");
    printf("\t-h\tHelp\tMostra na tela os comandos disponíveis para o programa\n");
    printf("\t-v\tVerbose\tDurante a execução do programa, mostra na tela o que está acontecendo\n\n");
    exit(EXIT_SUCCESS);
}
void opcoes_entrada(int argc, char** argv){
    int opt;
    while((opt = getopt(argc, argv, "f:hv")) != -1){
        switch(opt){
            case 'f':
                nomeArquivo = optarg;
                break;
            case 'h':
                help();
            case 'v':
                VERBOSE_MODE = 1;
                break;
        }
    }
}
void escreve_assembly(char* arq_sem_extensao){
    FILE *entrada;
    char cmd[256];
    int c;
    
    sprintf(cmd, "%s%s%s",  "set -o pipefail; llc ", arq_sem_extensao, ".ll 2>/dev/null; echo $?");
    
    if(!(entrada = popen(cmd, "r"))){
        exit(EXIT_FAILURE);
    }
    
    c = fgetc(entrada) - '0';
    pclose(entrada);
    
    if(c == 1){
        printf("[ERRO] Houve algum erro durante a tradução do arquivo llvm para assembly.\n");
        exit(EXIT_FAILURE);
    }
}
void executa_assembly(char* arq_sem_extensao){
    FILE *entrada;
    
    char cmd[256];
    
    sprintf(cmd, "%s%s%s",  "clang ", arq_sem_extensao,".s");
    
    if(!(entrada = popen(cmd, "r"))){
        exit(EXIT_FAILURE);
    }
    
    pclose(entrada);
    
}

int main(int argc, char** argv) {
    
    opcoes_entrada(argc, argv);
    char arq_no_extension[64]; strcpy(arq_no_extension, nomeArquivo);
    
    arq_no_extension[strlen(nomeArquivo) -2] = 0;

    FILE * arquivo;
    if ((arquivo = fopen(nomeArquivo, "r")) == NULL) {
        printf("Arquivo não encontrado!");
    }
    
    arquivo_leitura(arquivo);
//    Compilador
    Tree* arvore = preditivoDescendente();
    
    gerador_intermediario(arvore);
//    Manipulação de Arquivos LLVM e Assembly
    escreve_assembly(arq_no_extension);    
    executa_assembly(arq_no_extension);

    
//    Escopo*       lista  = create_escopo();
////    
//    add_escopo(lista, "main",     0);
//    add_escopo(lista, "funcao_1", 1);
//    add_escopo(lista, "funcao_2", 2);
//    add_escopo(lista, "if"      , 3);
//    
//    ItemVariavel* variaveis = create_lista();
//    
//    add_variavel(variaveis, "a");
//    add_variavel(variaveis, "b");
//    add_variavel(variaveis, "c");
//    add_variavel(variaveis, "d");
//    
//    add_item(variaveis, "a", create(0, "INTEGER", "VAR", (void*) 1));
//    add_item(variaveis, "a", create(1, "INTEGER", "VAR", (void*) 4));
//    add_item(variaveis, "a", create(2, "INTEGER", "VAR", (void*) 5));
//    add_item(variaveis, "a", create(3, "INTEGER", "VAR", (void*) 7));
//    
//    add_item(variaveis, "b", create(3, "INTEGER", "VAR", (void*) 2));
//    
//    add_item(variaveis, "c", create(0, "STRING", "VAR", (void*) "TESTE 1"));
//    add_item(variaveis, "c", create(3, "STRING", "VAR", (void*) "TESTE 2"));
//    
//    add_item(variaveis, "d", create(1, "INTEGER", "VAR", (void*) 7));
//    add_item(variaveis, "d", create(3, "STRING",  "VAR", (void*) "TESTE 3"));
//    
//    int a = (int) get_valor(variaveis, "a", get_escopo(lista, "main")->profundidade);
//    printf("Valor 1 = %i\n", a);
//    
//        a = (int) get_valor(variaveis, "a", get_escopo(lista, "funcao_1")->profundidade);
//    printf("Valor 2 = %i\n", a);
//    
//    a = (int) get_valor(variaveis, "a", get_escopo(lista, "funcao_2")->profundidade);
//    printf("Valor 3 = %i\n", a);
//    
//    a = (int) get_valor(variaveis, "a", get_escopo(lista, "if")->profundidade);
//    printf("Valor 4 = %i\n", a);
//    
//    int b = (int) get_valor(variaveis, "b", get_escopo(lista, "if")->profundidade);
//    printf("Valor 5 = %i\n", b);
//    
//    char* c = (char*) get_valor(variaveis, "c", get_escopo(lista, "main")->profundidade);
//    printf("Valor 6 = %s\n", c);
//    
//          c = (char*) get_valor(variaveis, "c", get_escopo(lista, "if")->profundidade);
//    printf("Valor 7 = %s\n", c);
//    
//    b = (int) get_valor(variaveis, "d", get_escopo(lista, "funcao_1")->profundidade);
//    printf("Valor 8 = %i\n", b);
//    
//    c = (char*) get_valor(variaveis, "d", get_escopo(lista, "if")->profundidade);
//    printf("Valor 9 = %s\n", c);
    
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

