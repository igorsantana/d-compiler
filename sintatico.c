#include "sintatico.h"
#include "estruturas.h"
#include "lexico.h"
#include "tabelapreditiva.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAO_TERMINAL "NAO_TERMINAL"

Pilha p;
Tree* arvore;

Tree* criaArvore(Tree* arv, char* nome, char* categoria);
Tree* adicionaFilho(Tree* arv, Token token);
Tree* adicionaFilhoLabel(Tree* arv, char* nome, char* categoria);
Tree* ajustaPonteiro(Tree* arv, char* token);
Tree* buscaAntecessor(Tree* arv,char* token);
Tree* voltaTopo(Tree* arv);
void printaArvore(Tree* arvore);

Tree* preditivoDescendente();
int comparaTerminal(char * str, Token token);
int retornaIndiceTerminal(Token token);


Tree* preditivoDescendente() {
    carregaTabela();
    p = inicializa_pilha("$");
    empilha(&p, "Start");
    Token a = getToken();
    //    Empilhrar inicial
    Elemento * X = p.topo;
    int indexX = retornaIndiceNT(X->c);
    int indexA = retornaIndiceTerminal(a);

    arvore = criaArvore(arvore, X->c, NAO_TERMINAL);

    while (strcmp(X->c, "$")) {
        if (!strcmp("lambda", X->c)) {
            desempilha(&p);
        } else if (!comparaTerminal(X->c, a)) {
            arvore = adicionaFilho(arvore,a);
            a = getToken();
            indexA = retornaIndiceTerminal(a);
            desempilha(&p);
        } else if (!isupper(X->c[0])) {
            printf("Símbolo inválido.%s\n",X->c);
            return NULL;
        } else if (matrizPreditiva[indexX][indexA].indexCaracter <= 0) {
            printf("Erro. erro de gramática.\n");
            return NULL;
        } else if (matrizPreditiva[indexX][indexA].indexCaracter > 0) {
            desempilha(&p);
            int i;
            for (i = matrizPreditiva[indexX][indexA].indexCaracter - 1; i >= 0; i--) {
                empilha(&p, matrizPreditiva[indexX][indexA].caracteres[i].c);
            }
            int j;
            for (j = 0; j < matrizPreditiva[indexX][indexA].indexCaracter; j++) {
                arvore = adicionaFilhoLabel(arvore,matrizPreditiva[indexX][indexA].caracteres[j].c,NAO_TERMINAL);
            }
        }
        X = p.topo;
        arvore = ajustaPonteiro(arvore,X->c);
        indexX = retornaIndiceNT(X->c);
    }
    
    arvore = voltaTopo(arvore);
//    printaArvore(arvore);
    reduce_tree(arvore);
//    printaArvore(arvore);
    
    return arvore;
}

/**
 * Cria uma arvore com um token
 * @param arvore
 * @param nome
 * @param categoria
 * @return 
 */
Tree* criaArvore(Tree* arv, char* nome, char* categoria){
    Token token;
    strcpy(token.token,nome);
    token.categoria = categoria;
    arv = create_tree (NULL, token);
    return arv;
}


/**
 * Adiciona um filho no nó passado um Token
 * @param arv Nô da arvore que será adicionado o filho
 * @param token
 * @return 
 */
Tree* adicionaFilho(Tree* arv, Token token){
    if (!strcmp(token.categoria, "SIMBOLO")) {
        arv->token.categoria = "SIMBOLO";
        return arv;
    }
    add_son(arv, token);
    return arv;
}

/**
 * 
 * @param arv
 * @param nome
 * @param categoria
 * @return 
 */
Tree* adicionaFilhoLabel(Tree* arv, char* nome, char* categoria){
    Token token;
    strcpy(token.token,nome);
    token.categoria = categoria;
    add_son(arv,token);    
    return arv;
}

/**
 * 
 * @param arv
 * @param token
 * @return 
 */
Tree* ajustaPonteiro(Tree* arv, char* token){
    if(!strcmp("$",token)){
        return arv;
    }
    
    Tree* current = arv->filhos;
    while(current!= NULL){
        if(!strcmp(token,current->token.token)){
            return current;
        }
        current = current->irmaos;
    }
    return buscaAntecessor(arv,token);
}


/**
 * 
 * @param arv
 * @return 
 */
Tree* voltaTopo(Tree* arv){
    while(arv != NULL){
        if(arv->pai == NULL){
            return arv;
        }
        arv = arv->pai;
    }
    return NULL;
}

/**
 * 
 * @param arv
 * @param token
 * @return 
 */
Tree* buscaAntecessor(Tree* arv,char* token){
    Tree* current = arv;

    while(current != NULL){
        if(!strcmp(current->token.token,token)){
            return current;
        }
        if(current->irmaos == NULL){
            current = current->pai;
        }else{
            current = current->irmaos;
        }
    }
    return NULL;
}

/**
 * 
 * @param arvore
 */
void printaArvore(Tree* arvore){
    
    
    Tree* atual = arvore->filhos;
    while(atual != NULL){
        atual = atual->irmaos;
    }
    atual = arvore->filhos;
    while(atual != NULL){
//        printaArvore(atual);
        atual = atual->irmaos;
    }
    
}

int comparaTerminal(char * str, Token token) {
    if (!strcmp(token.categoria, "SIMBOLO")  || !strcmp(token.categoria, "PALAVRA_RESERVADA")) {
        return strcmp(str, token.token);
    }
    return strcmp(str, token.categoria);
}

int retornaIndiceTerminal(Token token) {
    if (!strcmp(token.categoria, "SIMBOLO") || !strcmp(token.categoria, "PALAVRA_RESERVADA")) {
        return retornaIndiceT(token.token);
    }
    return retornaIndiceT(token.categoria);
}