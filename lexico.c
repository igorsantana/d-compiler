/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "lexico.h"
#include <stdio.h>
#include <string.h>
#include "automato.h"

FILE* arquivo;
int offsetGeral = 0;
int posicaoLinha = 1;
int posicaoColuna = 0;
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
            i = 1;
        } else {
            c = ultimoLido = leCharArq();
        }
    } while (!isCaracterValido(c));

    toReturn = setaLinhaColuna(toReturn);
    if (isSeparador(c)) {
        buffer[0] = c;
        buffer[1] = '\0';
        i = 1;
        ultimoLido = leCharArq();
    }
    //                printf("\n %c %i ----",c,isSeparador(c));
    while (isSeparador(c) != 1 && c != EOF) {

        if (c == '/') { // tratamentos de comentários
            c = leCharArq();
            if (c == '/') { // comentários em mesma linha
                while (c != 13 && c != EOF) {
                    c = leCharArq();
                }
            } else if (c == '*') { //comentários entre /**/
                c = leCharArq();

                while (c != EOF) {
                    c = leCharArq();

                    if (c == '*') {
                        c = leCharArq();

                        if (c == '/') {
                            break;
                        }
                    }
                }
            }
        }// fim de tratamento de comentários
        else if (c == '"') {
            do {
                if (c == '\\') { //tratamento de caracteres de controle
                    c = leCharArq();
                    switch (c) {
                        case 'n':
                            c = '\n';
                            break;
                        case 't':
                            c = '\t';
                            break;
                        case '\\':
                            c = '\\';
                            break;
                            
                        //default: retornar um erro bem aqui; 
                    } //fim de tratamento de caracter de controle
                }
                buffer[i] = c;
                buffer[++i] = '\0';
                c = ultimoLido = leCharArq();
            }while(c != '"');
        }
        buffer[i] = c;
        buffer[++i] = '\0';
        c = ultimoLido = leCharArq();
    }

    //    printf("%c %i\t",ultimoLido, ultimoLido);
    strcpy(toReturn.token, buffer);

    return toReturn;
}

Token setaLinhaColuna(Token token) {
    token.coluna = posicaoColuna;
    token.linha = posicaoLinha;

    return token;
}

char leCharArq() {
    offsetGeral++;
    posicaoColuna++;
    char c = fgetc(arquivo);
    switch (c) {
        case '\n':
            posicaoColuna = 0;
            posicaoLinha++;
            break;
        case '\t':
            posicaoColuna += 3;
            offsetGeral += 3;
            break;
    }

    return c;
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
    Token token = pegaProximoToken();

    token.categoria = analisarToken(token.token);

    return token;
}

int isSeparador(char c) {
    int i;

    char arraySeparadores[5];
    arraySeparadores[0] = ' ';
    arraySeparadores[1] = ';';
    arraySeparadores[2] = '{';
    arraySeparadores[3] = '}';
    arraySeparadores[4] = '\t';
    arraySeparadores[5] = '\n';

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
