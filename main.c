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
#include "automato.h"

/*
 * 
 */
int main(int argc, char** argv) {
    char *tokenType1 = analisarToken("1");
    printf("%s\n", tokenType1);
    char *tokenType2 = analisarToken("_1");
    printf("%s\n", tokenType2);
    char *tokenType3 = analisarToken("1121_12123_12121");
    printf("%s\n", tokenType3);
    char *tokenType4 = analisarToken("121aeriejrçiewo");
    printf("%s\n", tokenType4);
    char *tokenType5 = analisarToken("__FILE__");
    printf("%s\n", tokenType5);
    char *tokenType6 = analisarToken("byte");
    printf("%s\n", tokenType6);
    char *tokenType7 = analisarToken("byte2");
    printf("%s\n", tokenType7);
    
    return (EXIT_SUCCESS);
}

