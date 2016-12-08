#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "lexico.h"
#include "arvore.h"
#include "pilha.h"
#include "tabelaPreditiva.h"

Token first_token(){
    Token token;
    token.categoria = "SIMBOLO";
    token.coluna    = 0;
    token.linha     = 0;
    strcpy(token.token, "INIT_FILE");
    
    return token;
}

int main(int argc, char** argv) {
    char nomeArquivo[30] = {'e', 'e', '.', 'd'};

//    printf("Arquivo de entrada: ");
//    
//    gets(nomeArquivo);
    
    abrirArquivo(nomeArquivo);

    Token token = getToken();
    Pilha p = inicializa_pilha(token);
    
    while(token.coluna != -1 && token.linha != -1){
        token = getToken();
        empilha(&p, token);
        printf("Elemento %s foi empilhado\n", p.topo->token.token);
    }
    
    while(p.topo != NULL){
        Elemento * x = desempilha(&p);
        printf("Elemento %s foi desempilhado\n", x->token.token);
    }
    

    return 1;
}
    
    


