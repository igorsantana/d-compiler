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

    //estruturas
    struct Token{
        int categoria;
        char token[50];
        int linha;
        int coluna;
    };
    
    typedef struct Token Token;

    extern void abrirArquivo(char* nome);

    extern Token getToken();
    
    Token pegaProximoToken();
    
    char* tipoToken(Token token);

    int isSeparador(char c);

    int isSeparadorUtil(char c);
    
    int isCaracterValido(char c);



#ifdef __cplusplus
}
#endif

#endif /* LEXICO_H */

