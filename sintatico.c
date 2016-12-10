#include "sintatico.h"
#include "estruturas.h"
#include "lexico.h"
#include "tabelapreditiva.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Pilha p;

void preditivoDescendente();
int comparaTerminal(char * str,Token token);
int retornaIndiceTerminal(Token token);

void preditivoDescendente() {
    carregaTabela();
//    printaMatrizPreditiva();
    p = inicializa_pilha("$");
    empilha(&p, "Start");
    Token a = getToken();
    //    EMpilhrar inicial
    Elemento * X = p.topo;
    int indexX = retornaIndiceNT(X->c);
    int indexA = retornaIndiceTerminal(a);
    while (strcmp(X->c, "$")) {
        printf("%s/%s\n", X->c,a.token);
        if(!strcmp("lambda",X->c)){
            desempilha(&p);
        }else if (!comparaTerminal(X->c,a)) {
            //inserir a na árvore
            a = getToken();
            indexA = retornaIndiceTerminal(a);
            desempilha(&p);
        } else if (!isupper(X->c[0])) {
            printf("Símbolo inválido, Errouuuuuuu");
            break;
        } else if (matrizPreditiva[indexX][indexA].indexCaracter <= 0) {
            printf("%i/%i",indexX,indexX);
            printf("Erro. erro de gramática. Errouuuuuuuu");
            break;
        } else if (matrizPreditiva[indexX][indexA].indexCaracter > 0) {
            desempilha(&p);
            for (int i = matrizPreditiva[indexX][indexA].indexCaracter - 1; i >= 0; i--) {
                empilha(&p, matrizPreditiva[indexX][indexA].caracteres[i].c);
            }
        }
        X = p.topo;
        indexX = retornaIndiceNT(X->c);
    }
    
}
    int comparaTerminal(char * str, Token token){
        if(!strcmp(token.categoria,"SIMBOLO")){
            return strcmp(str,token.token);
        }
//        printf("")
        return strcmp(str, token.categoria);
    }
    int retornaIndiceTerminal(Token token){
        if(!strcmp(token.categoria,"SIMBOLO")){
            return retornaIndiceT(token.token);
        }
//        printf("")
        return retornaIndiceT(token.categoria);
    }