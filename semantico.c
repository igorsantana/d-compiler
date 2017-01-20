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
    //printf(" Variáveis: %s\n", raiz_variavel->nome);
    //printf(" Variáveis: %s\n", raiz_variavel->proximo->nome);
    //printf(" Escopo:    %s\n", raiz_escopo->nome);
    //printf(" Escopo:    %s  Pai: %s\n", raiz_escopo->proximo->nome, raiz_escopo->proximo->pai->nome);
    //printf(" Variável %s tem valor %s no escopo %s e tem valor de escape %d\n", raiz_variavel->nome, raiz_variavel->primeiro->valor, raiz_variavel->primeiro->escopo->nome, raiz_variavel->primeiro->escapa);
    //printf(" Variável %s tem valor %s no escopo %s e tem valor de escape %d\n", raiz_variavel->proximo->nome, raiz_variavel->proximo->primeiro->valor, raiz_variavel->proximo->primeiro->escopo->nome, raiz_variavel->proximo-> primeiro->escapa);
    
    return arvore;
}

void declaracao(Tree* arvore, Escopo* current){
    if(raiz_variavel->nome == NULL){
        raiz_variavel->nome = arvore->filhos->token.token;
    }
    ItemVariavel* v = get_variavel(raiz_variavel, arvore->filhos->token.token);
    if(v == NULL){
        add_variavel(raiz_variavel, arvore->filhos->token.token);
    }
    add_item(raiz_variavel, arvore->filhos->token.token,
    create(current, arvore->pai->token.categoria, arvore->filhos->irmaos->token.token));
}

void atribuicao(Tree* arvore, Escopo* current) {
    ValorVariavel* declaracao = encontra_escopo_declarado(raiz_variavel, raiz_escopo, current->nome, arvore->filhos->token.token);
    if(declaracao == NULL){
        printf("[ERRO SEMÂNTICO] Variável %s [Linha: %d, Coluna: %d] não foi declarada previamente. \n", arvore->filhos->token.token,
                arvore->filhos->token.linha, arvore->filhos->token.coluna);
        exit(1);
    }
    if(strcmp(declaracao->escopo->nome, current->nome) != 0 ){
        //printf("Nome do escopo: %s, declaracao: %s, variável: %s\n", current->nome, declaracao->escopo->nome, arvore->filhos->token.token);
        declaracao->escapa = 1;
    }
}

void analisa_arvore(Tree* arvore, Escopo* pai) {
    Escopo* current = pai;
    if (strcmp(arvore->token.token, "{") == 0) {
        current = add_escopo(raiz_escopo, get_nome_escopo(), -1, pai);
    }
    if (strcmp(arvore->token.token, "=") == 0) {
        if(strcmp(arvore->pai->token.categoria, "PALAVRA_RESERVADA") == 0){
//            if (strcmp(arvore->pai->token.categoria, arvore->filhos->irmaos->token.categoria) != 0) {
//                
//            }
            declaracao(arvore, current);
        }
        if(strcmp(arvore->pai->token.token, ";") == 0){
            
            
            atribuicao(arvore, current);
        }
        
        
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