#include <stdio.h>
#include <string.h>
#include "automato.h"
#include "estruturas.h"

#define NAO_SEPARADOR -1
#define SEPARADOR      0
#define SEPARADOR_UTIL 1
/* Variáveis globais */
Token token_vazio;
Token token_buf;

FILE* arquivo_lexico;

int offsetGeral = 0;
int posicaoLinha = 1;
int posicaoColuna = 0;
int retorna_buf = 0;
int VAZIO_FLAG = 0;

char caracter_buf = '#';

/*  Funções externas */
Token   getToken();
void    arquivo_leitura(FILE* arq);

 /* Funções internas (privadas)*/

int     verifica_composicao(char a, char b);
int     verifica_separador(char c);

void    atualiza_token(Token* ret, char* buf, int valor_flag);
void    trata_composicao(char c, char* buf);
void    setaLinhaColuna(Token* token);

char    le_char_arq();

Token   eof_token();
Token   pegaProximoToken();
int eh_caracter_com_quebra(char c);
char pega_ascii(char c);

/* Implementação das funções externas */

Token getToken() {
    Token token = pegaProximoToken();
    token.categoria = analisarToken(token.token);
    if (strcmp(token.categoria, "TOKEN_INVALIDO") == 0) {
        printf("[ERRO LÉXICO] Token %s [Linha: %d, Coluna: %d] não foi identificado.\n", token.token, token.linha, token.coluna);
        exit(1);
    }
    return token;
}

void arquivo_leitura(FILE* arq) {
    arquivo_lexico = arq;
}

/* Implementação das funções internas */

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
int verifica_separador(char c){
    char separadores[5] = {' ', '\t', '\n','\r'};
    char separadores_uteis[16] = {'{','}','[',']','(',')', '-', '+', '*', '/', '=', ',', '<', '>', '.', ';'};
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
        buf[0] = c; 
        buf[1] = next; 
        buf[2] = '\0';
    } else {
        buf[0] = c;
        buf[1] = '\0';
        caracter_buf = next;
    }
}
void setaLinhaColuna(Token* token) {
    token->coluna = posicaoColuna;
    token->linha = posicaoLinha;
}

char le_char_arq() {
    offsetGeral++;
    posicaoColuna++;
    char c = fgetc(arquivo_lexico);
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

Token eof_token(){
    Token eof;
    eof.coluna = -1;
    eof.linha = -1;
    eof.categoria = "$";
    eof.token[0] = '$';
    eof.token[1] = '\0';
    return eof;
}


Token pegaProximoToken() {
    if(retorna_buf == 1){
        retorna_buf = 0;
        return token_buf;
    }
    
    Token to_return;
    token_buf.token[0] = '\0'; 
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
            caracter_buf = le_char_arq();
            if(caracter_buf == '*'){
                while(caracter_buf != EOF){
                    caracter_buf = le_char_arq();
                    if(caracter_buf == '*'){
                        caracter_buf = le_char_arq();
                        if(caracter_buf == '/'){
                            caracter_buf = le_char_arq();
                            break;
                        }
                    }
                }
                
            } else if( caracter_buf == '/'){
                caracter_buf = le_char_arq();
                while(caracter_buf != '\n'){
                    caracter_buf = le_char_arq();
                }
            }
        }
        if(caracter_buf == EOF){
            c = caracter_buf;
        }
        
        int tipo_sep = verifica_separador(c);
//        printf("%c#%i\n",c,tipo_sep);
        if(tipo_sep == NAO_SEPARADOR){
            buf[buf_inc] = c;
            buf_inc++;
            
            if(c == '\"'){
                c = fgetc(arquivo_lexico);
                buf[buf_inc] = c;
                buf_inc++;
                offsetGeral++;
                posicaoColuna++;
                while(c!= '\"'){
                    c = fgetc(arquivo_lexico);
                    if(c == '\\'){
                        char aux = fgetc(arquivo_lexico);
                        if(eh_caracter_com_quebra(aux)){
                            aux = pega_ascii(aux);
                            buf[buf_inc] = aux;
                            offsetGeral++;
                            posicaoColuna++;                    
                        }else{
                            buf[buf_inc++] = c;
                            buf[buf_inc] = aux;
                            offsetGeral+=2;
                            posicaoColuna+=2;                    
                        }
                    }else{
                        buf[buf_inc] = c;
                        offsetGeral++;
                        posicaoColuna++;                    
                    }

                    buf_inc++;
                }
            }
            VAZIO_FLAG = 0;
        } 
        else if(tipo_sep == SEPARADOR && VAZIO_FLAG == 0){
            buf[buf_inc] = '\0';   
            atualiza_token(&to_return, buf, 1);
            buf_inc = 0;
            return to_return;
        } 
        else if(tipo_sep == SEPARADOR_UTIL && VAZIO_FLAG == 0) {
            if(c == '.'){
               buf[buf_inc] = '\0';
               if (strcmp(analisarToken(buf), "INTEGER") == 0){
                   Token aux = pegaProximoToken();
                   if(strcmp(analisarToken(aux.token), "INTEGER") == 0){
                       buf[buf_inc] = '.';
                       buf[++buf_inc] = '\0';
                       strcat(buf, aux.token);
                   } else {
                       buf[buf_inc] = '.';
                       buf[++buf_inc] = '\0';
                   } 
                   atualiza_token(&to_return, buf, 1);
                   buf_inc = 0;   
                   return to_return;
               }
            }
            char buf_aux[3];
            trata_composicao(c, buf_aux);
            atualiza_token(&token_buf, buf_aux, 1);
            retorna_buf = 1;
            
            if(!buf_inc){
                retorna_buf = 0;
                return token_buf;
            }
            buf[buf_inc] = '\0';   
            atualiza_token(&to_return, buf, 1);
            buf_inc = 0;   
                    
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


int eh_caracter_com_quebra(char c){
    char especiais[3] = {'n','t','0'};
    int i;
    for(i=0;i<3;i++){
        if(especiais[i]==c){
            return 1;
        }
    }
    return 0;
}

char pega_ascii(char c){
    if(c=='n'){
        return '\n';
    }
    
    if(c == 't'){
        return '\t';
    }
    if(c == '0'){
        return '\0';
    }
    return 0;
}