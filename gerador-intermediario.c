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

//Funções para selecao de regra
int eh_declaracao(Token* tok);
int eh_operacao(Token* tok);

//funções de geração de codigo
char* gera_escopo(Tree* no);
char* gera_statement(Tree* no);
char* gera_simbolo(Tree* no);
char* gera_declaracao(Tree* no);
char* gera_atribuicao(Tree* no);
char* gera_id(Tree* no);
char* gera_if(Tree* no);

//Funções auxiliares para geração de codigo
char* gera_operador(char str);
char* gerar_if_label();
char* gerar_variavel();
char* gerar_rotulo(int* contador, char* label);
char* concat_str(char* des, char* src);


int gerador_intermediario(Tree* arvore){
    analisa_funcao(arvore);
    
    return 1;
}

char* analisa_funcao(Tree* no){
    if(!strcmp("{",no->token.token)){
        return gera_escopo(no);
    }
    if(!strcmp(";",no->token.token)){
        return gera_statement(no);
    }
    if(eh_operacao(no)){
        return gera_simbolo(no);
    }
    if(eh_declaracao(no)){
        return gera_declaracao(no);
    }
    if(!strcmp(no->token.token,"=")){
        return gera_atribuicao(no);
    }
    if(!strcmp(no->token.categoria,"id")){
        return gera_id(no);
    }
    if(!strcmp(no->token.token,"if")){
        return gera_if(no);
    }
    
    
    return no->token.token;
}

int eh_declaracao(Token* tok){
    char tipos[3][5] = {"char","int","float"};
    for(int i = 0; i<3;i++){
        if(!strcmp(tipos[i],tok->token)){
            return 1;
        }
    }
    return 0;
}

int eh_operacao(Token* tok){
    char operandos[4][2]={"+","-","*","/"};
    for(int i = 0; i<4;i++){
        if(!strcmp(operandos[i],tok->token)){
            return 1;
        }
    }
    
    return 0;
}


char* gera_escopo(Tree* no){
    no = no->filhos;
    return analisa_funcao(no);
}

char* gera_statement(Tree* no){
    no = no->filhos;
    while(no != NULL){
        analisa_funcao(no);
        no = no->irmaos;
    }
    
    return NULL;
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

char* gera_declaracao(Tree* no){
    char buffer[100];
    char* retorno = NULL;
    
    no = no->filhos;//  vai do int pro =
    if(!strcmp("=",no->token.token)){
        char* esq = NULL;
        char* dir = NULL;
        no = no->filhos;//  vai do = pro id

        //Utilizar essa label pra atualizar a label do temporario na tabela de simbulos
        dir = no->token.token;

        no = no->irmaos;//   vai do id pra atribuição
        
        dir = analisa_funcao(no);
        retorno = gerar_variavel();
        printf("%s = %s\n",retorno,dir);
    }
    return retorno;
}

char* gera_atribuicao(Tree* no){
    char buffer[100];
    char* esq;
    char* variavel;
    char* retorno;
    no = no->filhos;
//    buscar na tabela de simbulo e adicionar a label
    esq = no->token.token;
    
    no = no->irmaos;
    variavel = analisa_funcao(no);
    retorno = gerar_variavel();
    printf("%s = %s\n",retorno,variavel);
    
    return retorno;
}

char* gera_id(Tree* no){
//    Adicionar nessa função a manipulacao da tabela de simbolos
    return gerar_variavel();
}

char* gera_if(Tree* no){
    no = no->filhos;
    Tree* exp_tree = no->filhos;
    char* exp_rst = analisa_funcao(exp_tree);
    char* if_label = gerar_if_label();
    printf("br i1 %s, label %_t_%s, label %_end_%s\n_t_%s:\n",exp_rst,if_label,if_label,if_label);
    no = no->irmaos;
    analisa_funcao(no);
    printf("br label %_end_%s\n_end_%s:",if_label,if_label);
    return NULL;
    
    
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

char* gerar_if_label(){
    char* var = gerar_rotulo(&contador_label,"if_");
    return var;
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