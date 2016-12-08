#include "lexico.h"
#include <stdio.h>
#include <string.h>
#include "automato.h"

#define NAO_SEPARADOR -1
#define SEPARADOR      0
#define SEPARADOR_UTIL 1

const struct Token token_vazio;
Token token_buf;
FILE* arquivo;
int offsetGeral = 0;
int posicaoLinha = 1;
int posicaoColuna = 0;
int   retorna_buf = 0;
int   VAZIO_FLAG = 0;
char caracter_buf = '#';

int     verifica_composicao(char a, char b);
Token   eof_token();
void    atualiza_token(Token* ret, char* buf, int valor_flag);
void    trata_composicao(char c, char* buf);
Token   pegaProximoToken();
void    setaLinhaColuna(Token* token);
char    le_char_arq();
void    abrirArquivo(char* nomeArquivo);
Token   getToken();
int     verifica_separador(char c);

Token eof_token(){
    Token eof;
    eof.coluna = -1;
    eof.linha = -1;
    eof.categoria = "EOF";;
    eof.token[0] = 'E';
    eof.token[1] = 'O';
    eof.token[2] = 'F';
    eof.token[3] = '\0';
    return eof;
}

void atualiza_token(Token* ret, char* buf, int valor_flag){
    strcpy(ret->token, buf);
    memset(&buf[0], 0, sizeof(buf));
    setaLinhaColuna(ret); 
    VAZIO_FLAG = valor_flag;
}

void trata_composicao(char c, char* buf){
    char next = le_char_arq();
    int sep_next = verifica_separador(next);
            
    if(sep_next == SEPARADOR_UTIL && verifica_composicao(c, next)){
        buf[0] = c; buf[1] = next; buf[2] = '\0';
    } else {
        buf[0] = c; buf[1] = '\0';
        caracter_buf = next;
    }
}

int verifica_composicao(char a, char b){
    int i;
    if(b == '='){
        char possiveis[8] = {'+','-','*','/','>','<','!','='};
        for(i = 0; i < 8; i++){
            if(a == possiveis[i])
                return 1;
        }
        return 0;
    }
    if((a == '&' && b == '&') ||( a == '|' && b == '|')
    || (a == '+' && b == '+') || (a == '-' && b == '-')
    || (a == '*' && b == '*')){
        return 1;
    }
    return 0;
}

Token pegaProximoToken() {
    if(retorna_buf == 1){
        retorna_buf = 0;
        return token_buf;
    }
    
    Token to_return;
    token_buf.token[0] = '\0'; //????
    token_buf = token_vazio;
    
    char buf [50];
    int  buf_inc = 0; //incrementador do buf
    char c;
    if(caracter_buf == '#'){
        c = le_char_arq();
    } else {
        c = caracter_buf;
        caracter_buf = '#';
    }
    
    while(1){
        if(c == '/'){
            c = le_char_arq();
            if(c == '*'){
                while(c != EOF){
                    c = le_char_arq();
                    if(c == '*'){
                        c = le_char_arq();
                        if(c == '/'){
                            c = le_char_arq();
                            break;
                        }
                    }
                }
                
            } else if( c == '/'){
                c = le_char_arq();
                while(c != '\n'){
                    c = le_char_arq();
                }
            }
        }

        int tipo_sep = verifica_separador(c);
        
        if(tipo_sep == NAO_SEPARADOR){
            buf[buf_inc] = c;
            buf_inc++;
            VAZIO_FLAG = 0;
        } 
        else if(tipo_sep == SEPARADOR && VAZIO_FLAG == 0){
            buf[buf_inc] = '\0';   
            atualiza_token(&to_return, buf, 1);
            buf_inc = 0;
            return to_return;
        } 
        else if(tipo_sep == SEPARADOR_UTIL && VAZIO_FLAG == 0) {
            buf[buf_inc] = '\0';   
            atualiza_token(&to_return, buf, 1);
            buf_inc = 0;
            
            char buf_aux[3];
            trata_composicao(c, buf_aux);
            atualiza_token(&token_buf, buf_aux, 1);
            retorna_buf = 1;
            return to_return;
        } 
        else if(tipo_sep == SEPARADOR_UTIL && VAZIO_FLAG == 1){
            trata_composicao(c, buf);
            
            atualiza_token(&to_return, buf, 1);
            buf_inc = 0;
            return to_return;
        }
        c = le_char_arq();
        if(c == EOF){
            break;
        }
    }
    
    return eof_token();
}

void setaLinhaColuna(Token* token) {
    token->coluna = posicaoColuna;
    token->linha = posicaoLinha;
}

char le_char_arq() {
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

void abrirArquivo(char* nomeArquivo) {
    
    if ((arquivo = fopen(nomeArquivo, "r")) == NULL) {
        printf("Arquivo não encontrado!");
    }
}

Token getToken() {
    Token token = pegaProximoToken();
    
    token.categoria = analisarToken(token.token);
    return token;
}

int verifica_separador(char c){
    char separadores[5] = {' ', '\t', '\n','\r', ';'};
    char separadores_uteis[16] = {'{','}','[',']','(',')', '-', '+', '*', '/', '=', ',', '<', '>', '.'};
    int i;
    for(i = 0; i < 5; i++){
        if(separadores[i] == c){
            return SEPARADOR;
        }
    }
    for(i = 0; i < 16; i++){
        if(separadores_uteis[i] == c) {
            return SEPARADOR_UTIL;
        }
    }
    return NAO_SEPARADOR;
}
