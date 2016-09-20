/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "lexico.h"
#include <stdio.h>
#include <string.h>

FILE* arquivo;
int offsetGeral;
int posicaoLinha;
int posicaoColuna;
Token anterior;
char ultimoLido;

Token pegaProximoToken() {
    char c;
    char buffer [50];
    int i = 0; //incrementador do buffer
    struct Token toReturn;
    buffer[0] = '\0';

    do {
        c = ultimoLido;
        if (ultimoLido && isCaracterValido(c)) {
            buffer[0] = c;
            buffer[1] = '\0';
            if (isSeparador(c)) {
//                    printf("%c ---- ",c);
                ultimoLido = fgetc(arquivo);
            }
            i = 1;
        } else {
            c = ultimoLido = fgetc(arquivo);
//            if (isSeparador(c)) {
//                buffer[0] = c;
//                buffer[1] = '\0';
//                i = 1;
//            }
        }
    }while (!isCaracterValido(c));
    
                printf("\n %c %i ----",c,isSeparador(c));

    while (isSeparador(c) != 1 && c != EOF) {

        if (c == '/') { // tratamentos de comentários
            c = fgetc(arquivo);
            if (c == '/') { // comentários em mesma linha
                while (c != 13 && c != EOF) {
                    c = fgetc(arquivo);
                }
            } else if (c == '*') { //comentários entre /**/
                c = fgetc(arquivo);

                while (c != EOF) {
                    c = fgetc(arquivo);

                    if (c == '*') {
                        c = fgetc(arquivo);

                        if (c == '/') {
                            break;
                        }
                    }
                }
            }
        } // fim de tratamento de comentários

        buffer[i] = c;
        i++;
        buffer[i] = '\0';
        c = ultimoLido = fgetc(arquivo);
    }
//    toReturn.token[0] = '\0';
    strcpy(toReturn.token, buffer);

    //        printf("%s\n",buffer);
    return toReturn;
}

int isCaracterValido(char c) {
    return c != '\n' && c != ' ' && c != '\t';
}

char* tipoToken(Token token) {
    return "";
}

//função para abertura de arquivo

void abrirArquivo(char* nomeArquivo) {
    if ((arquivo = fopen(nomeArquivo, "r")) == NULL) {
        printf("Arquivo não encontrado!");
    }
}

//função que pega o proximo token do arquivo. não está pegando os separadores

Token getToken() {
    return pegaProximoToken();
}

int isSeparador(char c) {
    int i;

    char arraySeparadores[5];
    arraySeparadores[0] = ' ';
    arraySeparadores[1] = ';';
    arraySeparadores[2] = '{';
    arraySeparadores[3] = '}';
    arraySeparadores[4] = '\t';

    for (i = 0; i < 5; i++) {
        if (arraySeparadores[i] == c) {
            return 1;
            break;
        }
    }
    return 0;
}

int isSeparadorUtil(char c) {
    int i;

    char arraySeparadoresUteis[5];
    arraySeparadoresUteis[0] = ']';
    arraySeparadoresUteis[1] = '[';
    arraySeparadoresUteis[2] = '{';
    arraySeparadoresUteis[3] = '}';
    arraySeparadoresUteis[4] = ';';

    for (i = 0; i < 5; i++) {
        if (arraySeparadoresUteis[i] == c) {
            return 1;
            break;
        }
    }
    return 0;
}