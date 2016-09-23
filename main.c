/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: igorsantana
 *
 * Created on September 9, 2016, 1:22 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "lexico.h"

/*
 * 
 */
int main(int argc, char** argv) {
//    char *tokenType1 = analisarToken("+");
//    printf("%s\n", tokenType1);
//    char *tokenType2 = analisarToken("/");
//    printf("%s\n", tokenType2);
//    char *tokenType3 = analisarToken("__a");
//    printf("%s\n", tokenType3);
//    char *tokenType4 = analisarToken("121");
//    printf("%s\n", tokenType4);
//    char *tokenType5 = analisarToken("__FILE__");
//    printf("%s\n", tokenType5);
//    char *tokenType6 = analisarToken("byte");
//    printf("%s\n", tokenType6);
//    char *tokenType7 = analisarToken("byte2");
//    printf("%s\n", tokenType7);
//    char *tokenType8 = analisarToken("2321312asddsa");
//    printf("%s\n", tokenType8);
    abrirArquivo("teste.d");
    int i;
    Token token;
    for(i = 0;i< 12;i++){
        token = getToken();
        printf("%s\t %s\n",token.token,token.categoria);
    }
    
    return (EXIT_SUCCESS);
}

