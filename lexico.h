/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   lexico.h
 * Author: rafael
 *
 * Created on September 12, 2016, 7:42 PM
 */

#ifndef LEXICO_H
#define LEXICO_H

#ifdef __cplusplus
extern "C" {
#endif

    struct Token {
        char* palavra;
    };
    typedef struct Token Token;

    extern void abrirArquivo(char* nome);

    extern Token getToken();

    int isPalavraReservada(Token token);

    int isIdentificador(Token token);

    int isSimbulo(Token token);

    int isNumero(Token token);
    
    int isString(Token token);
    
    int pegaProximoToken();
    
    char* tipoToken(Token token);



#ifdef __cplusplus
}
#endif

#endif /* LEXICO_H */

