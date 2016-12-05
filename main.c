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
#include <string.h>
#include "lexico.h"
#include "arvore.h"

void iterator(Tree* node, int idx){
    printf("FILHO: { valor: [%s]\ttipo: [%s] } PAI: { valor: [%s]\ttipo: [%s] }\n", node->token.token, node->token.categoria, node->pai->token.token, node->pai->token.categoria);
}

Token first_token(){
    Token token;
    token.categoria = "SIMBOLO";
    token.coluna    = 0;
    token.linha     = 0;
    strcpy(token.token, "INIT_FILE");
    
    return token;
}

int main(int argc, char** argv) {
    char nomeArquivo[30];

    printf("Arquivo de entrada: ");
    gets(nomeArquivo);
    abrirArquivo(nomeArquivo);
    int i;
    
    Tree* root = create_tree(NULL, first_token());
    
    for(i = 0;i< 12;i++){
        Token token = getToken();
        
        add_son(root, root->token, token);
        
    }
    
    iterate_sons(root, &iterator);
    return (EXIT_SUCCESS);
}
    
    


