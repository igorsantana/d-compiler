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
    abrirArquivo("teste.d");
    int i;
    Token token;
    for(i = 0;i< 12;i++){
        token = getToken();
        printf("%s\t[%i,%i] \n",token.token,token.linha,token.coluna);
    }
    
    return (EXIT_SUCCESS);
}

