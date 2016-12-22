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
Tree* voltaTopo(Tree* arvore);
Tree* printaArvore(Tree* arvore);

void preditivoDescendente();
int comparaTerminal(char * str, Token token);
int retornaIndiceTerminal(Token token);


void preditivoDescendente() {
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
//            arvore = removeLambda(arvore);
            desempilha(&p);
        } else if (!comparaTerminal(X->c, a)) {
            arvore = adicionaFilho(arvore,a);
//            printf("\n%s\n",X->c);
            a = getToken();
            indexA = retornaIndiceTerminal(a);
            desempilha(&p);
        } else if (!isupper(X->c[0])) {
            printf("Símbolo inválido.");
            break;
        } else if (matrizPreditiva[indexX][indexA].indexCaracter <= 0) {
            printf("%i/%i", indexX, indexX);
            printf("Erro. erro de gramática.");
            break;
        } else if (matrizPreditiva[indexX][indexA].indexCaracter > 0) {
//            printf("\nPai->%s == Filho -> ",X->c);
            desempilha(&p);
            for (int i = matrizPreditiva[indexX][indexA].indexCaracter - 1; i >= 0; i--) {
                empilha(&p, matrizPreditiva[indexX][indexA].caracteres[i].c);
            }
            for (int i = 0; i < matrizPreditiva[indexX][indexA].indexCaracter; i++) {
                arvore = adicionaFilhoLabel(arvore,matrizPreditiva[indexX][indexA].caracteres[i].c,NAO_TERMINAL);
            }
        }
        X = p.topo;
        arvore = ajustaPonteiro(arvore,X->c);
        indexX = retornaIndiceNT(X->c);
//        printf("\naki1\n");
    }
    
    arvore = voltaTopo(arvore);
    
    reduce_tree(arvore);
    
    printaArvore(arvore);
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
//    printf("\nNó raiz -> %s\n",arv->token.token);
    return arv;
}

/**
 * Remove todo pai que não tem outro filho a não ser o lambda
 * @param arv
 * @return 
 */
Tree* removeLambda(Tree* arv){
    
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
//        printf("\naki2\n");
        return arv;
    }
//    printf("nó -> %s", token.token);
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
//    printf("\tfilho->%s|",nome);
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
 * @param arvore
 * @return 
 */
Tree* voltaTopo(Tree* arvore){
    while(arvore != NULL){
        if(arvore->pai == NULL){
            return arvore;
        }
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
//            printf("\n%s-%s\n",token,current->token.token);
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

Tree* printaArvore(Tree* arvore){
//    while()
    return NULL;
}

int comparaTerminal(char * str, Token token) {
    if (!strcmp(token.categoria, "SIMBOLO")) {
        return strcmp(str, token.token);
    }
    return strcmp(str, token.categoria);
}

int retornaIndiceTerminal(Token token) {
    if (!strcmp(token.categoria, "SIMBOLO")) {
        return retornaIndiceT(token.token);
    }
    return retornaIndiceT(token.categoria);
}