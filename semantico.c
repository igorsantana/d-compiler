#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

int             inc_escopo = 0;
Escopo*         raiz_escopo;
ItemVariavel*   raiz_variavel;
char*           prints[5];
int             contador_print;


Tree*   executa_semantico(Tree* arvore);
char*   get_nome_escopo();
void    analisa_arvore(Tree* arvore, Escopo* pai);
int     get_escopo_atual();
void    erro_declaracao(Tree* arvore);
void    atribuicao(Tree* arvore, Escopo* current);
void    declaracao(Tree* arvore, Escopo* current);
void    print_variaveis();

Escopo* get_raiz_escopo(){
    return raiz_escopo;
}

ItemVariavel* get_raiz_variavel(){
    return raiz_variavel;
}


int get_escopo_atual(){
    int atual = inc_escopo;
    inc_escopo++;
    return atual;
}

Tree* executa_semantico(Tree* arvore) {
    raiz_escopo     = create_escopo();
    raiz_variavel   = create_lista();
    analisa_arvore(arvore, NULL);
    print_variaveis();
    return arvore;
}

void declaracao(Tree* arvore, Escopo* current) {
    if (raiz_variavel->nome == NULL) {
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
//    if(declaracao == NULL){
//        printf("[ERRO SEMÂNTICO] Variável %s [Linha: %d, Coluna: %d] não foi declarada previamente. \n", arvore->filhos->token.token,
//                arvore->filhos->token.linha, arvore->filhos->token.coluna);
//        exit(1);
//    }
    if(strcmp(declaracao->escopo->nome, current->nome) != 0 ){
        declaracao->escapa = 1;
    }
}

void erro_declaracao(Tree* arvore){
//    if (strcmp(arvore->pai->token.token, "int") == 0 &&
//    strcmp(arvore->filhos->irmaos->token.categoria, "_IntegerLiteral") != 0) {
//        printf("[ERRO SEMÂNTICO] Atribuição de tipos incompatíveis na variável %s [Linha: %d, Coluna: %d] \n",
//                arvore->filhos->token.token, arvore->filhos->token.linha, arvore->filhos->token.coluna);
//        exit(1);
//    }
//    if (strcmp(arvore->pai->token.token, "string") == 0 &&
//        strcmp(arvore->filhos->irmaos->token.categoria, "_StringLiteral") != 0) {
//            printf("[ERRO SEMÂNTICO] Atribuição de tipos incompatíveis na variável %s [Linha: %d, Coluna: %d] \n",
//                    arvore->filhos->token.token, arvore->filhos->token.linha, arvore->filhos->token.coluna);
//            exit(1);
//    }
}

void print_variaveis() {
    ItemVariavel* current = raiz_variavel;
    printf("%s - %s\n", current->nome, current->primeiro->escopo->nome);
    printf("%s - %s\n", current->proximo->nome, current->proximo->primeiro->escopo->nome);
    printf("%s - %s\n", current->proximo->proximo->nome, current->proximo->proximo->primeiro->escopo->nome);
//    printf("%s/ - %s\n", current->proximo->proximo->nome, current->proximo->proximo->primeiro->escopo->nome);
//    
//    printf("%s - %s\n", current->nome, current->primeiro->escopo->nome);
//    printf("%s - %s\n", current->proximo->nome, current->proximo->primeiro->escopo->nome);
//    printf("%s - %s\n", current->proximo->proximo->nome, current->proximo->proximo->primeiro->escopo->nome);
}

void analisa_arvore(Tree* arvore, Escopo* pai) {
    Escopo* current = pai;
    
    // Novo Bloco:
    if (strcmp(arvore->token.token, "{") == 0) {
        current = add_escopo(raiz_escopo, get_nome_escopo(), -1, pai);
    }
    
    // Nova Declaracao:
    if ((strcmp(arvore->token.token, "int") == 0)
     || (strcmp(arvore->token.token, "string") == 0)) {
        Tree* filho = arvore->filhos;
        if (filho != NULL) {
            if (strcmp(filho->token.categoria, "id") == 0) {
                
//                printf("%s - %s\n", filho->token.token, current->nome);
                add_variavel(raiz_variavel, filho->token.token);
                add_item(raiz_variavel, filho->token.token, create(current, arvore->token.token, NULL));
            }
        }
    }
    
    // Nova Atribuicao/Declaracao:
    if (strcmp(arvore->token.token, "=") == 0) {
        if(strcmp(arvore->pai->token.categoria, "PALAVRA_RESERVADA") == 0){
            
            erro_declaracao(arvore);
            declaracao(arvore, current);
        }
        if(strcmp(arvore->pai->token.token, ";") == 0){
            atribuicao(arvore, current);
        }
    }
    if(strcmp(arvore->token.token, "writeln") == 0){
        Tree* aux = arvore->filhos->filhos;
        if(strcmp(aux->token.categoria, "_StringLiteral") == 0){
            prints[contador_print] = aux->token.token;
        }
        if(strcmp(aux->token.token, ",") == 0){
            prints[contador_print]  = aux->filhos->token.token;
        }
        contador_print++;
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

char** get_prints(int* size){
    (*size) = contador_print;
    return prints;
}