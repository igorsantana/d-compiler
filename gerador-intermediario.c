/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"


#define NUMBER "number"
#define SYMBOL "SIMBOLO"
#define LOCAL_V "%T"
#define GLOBAL_V "@T"


int contador_label;
int contador_variavel;


int gerador_intermediario(Tree* arvore);
char* analisa_funcao(Tree* no);
char* gera_simbolo(Tree* no);
char* gera_operador(char str);
char* gerar_variavel();
char* gerar_rotulo(int* contador, char* label);
char* concat_str(char* des, char* src);


int gerador_intermediario(Tree* arvore){
    analisa_funcao(arvore);
    
    return 1;
}

char* analisa_funcao(Tree* no){
    if(eh_operacao(no)){
        return gera_simbolo(no);
    }
    
    return no->token.token;
}

char* gera_simbolo(Tree* no){
    char* buffer = NULL;
    char* variavel = NULL;
    char* a = NULL;
    char* b = NULL;
    Tree* current = no->filhos;
    a = analisa_funcao(current);
    current = current->irmaos;
    b = analisa_funcao(current);
    
    variavel = gerar_variavel();
    buffer = variavel;
   
    buffer = concat_str(buffer," = ");
    buffer = concat_str(buffer,gera_operador(no->token.token[0]));
    buffer = concat_str(buffer," i32 ");
    buffer = concat_str(buffer,a);
    buffer = concat_str(buffer," , ");
    buffer = concat_str(buffer,b);
    buffer = concat_str(buffer,"\n");

    printf(buffer);
    
    return variavel;
}

char* gera_operador(char str){
    switch(str){
        case '+':
            return "add";
        case '-':
            return "sub";
        case '*':
            return "mul";
        case '/':
            return "udiv";
        default:
            return NULL;
    }    
}

char* gerar_variavel(){
    char* var = gerar_rotulo(&contador_variavel,LOCAL_V);
    return var;
}

char* gerar_rotulo(int* contador, char* label){    
    char retorno[10];
    char numero[11];
    strcpy(retorno,label);
    sprintf(numero,"%d",(*contador)++);
    strcat(retorno,numero);
    char* ret = malloc(sizeof(char)*10);
    strcpy(ret,retorno);
    
    return ret;
}

char* concat_str(char* des, char* src){
    char* ret;
    char a[500];
    char b[500];
    strcpy(a,des);
    strcpy(b,src);
    strcat(a,b);
    ret = a;
    return ret;
}