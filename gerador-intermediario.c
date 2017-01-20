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

FILE * arq_llvm;
int contador_label;
int contador_variavel;


int gerador_intermediario(Tree* arvore);
void abrirArquivoLLVM();
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
char* gera_comparacao(Tree* no);
char* gera_loop(Tree* no);
char* gera_write(Tree* no);
//Funções auxiliares para geração de codigo
char* gera_operador(char str);
char* gerar_if_label();
char* gerar_loop_label();
char* gerar_variavel();
char* gerar_rotulo(int* contador, char* label);
char* concat_str(char* des, char* src);
char* comando_comp_LLVM(char * str);


// Teste:
void gera_caractere(Tree* no);


int gerador_intermediario(Tree* arvore) {
    abrirArquivoLLVM();
    analisa_funcao(arvore);
    fclose(arq_llvm);
    return 1;
}

void abrirArquivoLLVM() {
    if ((arq_llvm = fopen("intermediario.ll", "w")) == NULL) {
        printf("Erro na criação do arquivo de código intermedário.");
    }
}

char* analisa_funcao(Tree* no) {
    if (!strcmp("{", no->token.token)) {
        return gera_escopo(no);
    }
    if (!strcmp(";", no->token.token)) {
        return gera_statement(no);
    }
    if (eh_operacao(no)) {
        return gera_simbolo(no);
    }
    if (eh_declaracao(no)) {
        return gera_declaracao(no);
    }
    if (!strcmp(no->token.token, "=")) {
        return gera_atribuicao(no);
    }
    if (!strcmp(no->token.token, "writeln")) {
        return gera_write(no);
    }
    if (!strcmp(no->token.categoria, "id")) {
        return gera_id(no);
    }
    if (!strcmp(no->token.token, "if")) {
        return gera_if(no);
    }
    if (eh_comparacao(no)) {
        return gera_comparacao(no);
    }
    if (!strcmp(no->token.token, "while")) {
        return gera_loop(no);
    }

    return no->token.token;
}

int eh_declaracao(Token* tok) {
    char tipos[3][5] = {"char", "int", "float"};
    for (int i = 0; i < 3; i++) {
        if (!strcmp(tipos[i], tok->token)) {
            return 1;
        }
    }
    return 0;
}

int eh_operacao(Token* tok) {
    char operandos[4][2] = {"+", "-", "*", "/"};
    for (int i = 0; i < 4; i++) {
        if (!strcmp(operandos[i], tok->token)) {
            return 1;
        }
    }

    return 0;
}

int eh_comparacao(Token* tok) {
    char simbolos[6][5] = {"==", "!=", ">", ">=", "<", "<="};
    for (int i = 0; i < 6; i++) {
        if (!strcmp(simbolos[i], tok->token)) {
            return 1;
        }
    }
    return 0;
}

char* gera_escopo(Tree* no) {
    no = no->filhos;
    return analisa_funcao(no);
}

char* gera_statement(Tree* no) {
    no = no->filhos;
    while (no != NULL) {
        analisa_funcao(no);
        no = no->irmaos;
    }

    return NULL;
}

char* gera_simbolo(Tree* no) {
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

    buffer = concat_str(buffer, " = ");
    buffer = concat_str(buffer, gera_operador(no->token.token[0]));
    buffer = concat_str(buffer, " i32 ");
    buffer = concat_str(buffer, a);
    buffer = concat_str(buffer, " , ");
    buffer = concat_str(buffer, b);
    buffer = concat_str(buffer, "\n");

    fprintf(arq_llvm, "%s", buffer);

    return variavel;
}

char* gera_declaracao(Tree* no) {
    char buffer[100];
    char* retorno = NULL;

    no = no->filhos; //  vai do int pro =
    if (!strcmp("=", no->token.token)) {
        char* esq = NULL;
        char* dir = NULL;
        no = no->filhos; //  vai do = pro id

        //Utilizar essa label pra atualizar a label do temporario na tabela de simbulos
        dir = no->token.token;

        no = no->irmaos; //   vai do id pra atribuição

        dir = analisa_funcao(no);
        retorno = gerar_variavel();
        fprintf(arq_llvm, "%s = %s\n", retorno, dir);
    }
    return retorno;
}

char* gera_atribuicao(Tree* no) {
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
    fprintf(arq_llvm, "%s = %s\n", retorno, variavel);

    return retorno;
}

char* gera_id(Tree* no) {
    //    Adicionar nessa função a manipulacao da tabela de simbolos
    return gerar_variavel();
}

char* comando_comp_LLVM(char * str) {

    if (!strcmp(str, "==")) return "eq";
    if (!strcmp(str, "!=")) return "ne";
    if (!strcmp(str, ">")) return "ugt";
    if (!strcmp(str, ">=")) return "uge";
    if (!strcmp(str, "<")) return "ult";
    if (!strcmp(str, "<=")) return "ule";

    return "error";
}

char* gera_if(Tree* no) {
    no = no->filhos;
    Tree* exp_tree = no->filhos;
    char* exp_rst = analisa_funcao(exp_tree);
    char* if_label = gerar_if_label();



    fprintf(arq_llvm, "br i1 %s, label %_t_%s, label %_end_%s\n_t_%s:\n", exp_rst, if_label, if_label, if_label);
    no = no->irmaos;
    analisa_funcao(no);
    fprintf(arq_llvm, "br label %_end_%s\n_end_%s:", if_label, if_label);
    return NULL;

}

char* gera_comparacao(Tree* no) {
    char * comando_cmp = comando_comp_LLVM(no->token.token);
    no = no->filhos;
    char* esquerda = analisa_funcao(no);
    no = no->irmaos;
    char* direita = analisa_funcao(no);
    char* ret = gerar_variavel();
    fprintf(arq_llvm, "%s = icmp %s i32 %s %s\n", ret, comando_cmp, esquerda, direita);
    return ret;
}

char* gera_loop(Tree* no) {
    no = no->filhos;
    Tree* exp_tree = no->filhos;
    char * label1 = gerar_loop_label();
    char * label2 = gerar_loop_label();
    char * label3 = gerar_loop_label();
    char cond[100];

    fprintf(arq_llvm, "_%s\n", label1);
    char* exp_rst = analisa_funcao(exp_tree);
    fprintf(arq_llvm, "br i1 %s, label %_%s, label %_%s\n", exp_rst, label2, label3);
    fprintf(arq_llvm, "_%s\n", label2);
    no = no->irmaos;
    analisa_funcao(no);
    fprintf(arq_llvm, "br label %_%s\n", label1);
    fprintf(arq_llvm, "_%s\n", label3);
    return NULL;
}

char* gera_write(Tree* no) {
    char str_print[300];
    char msg[500];

    if (!strcmp(no->filhos->token.token, "(")) {
        Tree* t_aux;

        t_aux = no->filhos;
        printf("Raiz: %s\n", t_aux->token.token);
        
        while (t_aux->filhos != NULL) {
            Tree* t_aux_irmaos = t_aux;
            while (t_aux_irmaos != NULL) {
                //printf("= %s\n", t_aux_irmaos->token.token);                
                t_aux_irmaos = t_aux_irmaos->irmaos;
            }
            t_aux = t_aux->filhos;
        }
        
        // Testes:
        int lenght = strlen(t_aux->token.token);
        printf("%s = internal constant [%i x i8] c%s\n", "%STR0", lenght, t_aux->token.token);
        printf("call i32 (i8*, ...)* @printf(i8* getelementptr ([%i x i8]* %s, i32 0, i32 0) ", lenght, "%STR0");
        gera_caractere(t_aux->irmaos);

        //        if(!strcmp(no->filhos->filhos->token.token, ",")){
        //            printf("%s", "teste3");
        //        }else if(!strcmp(no->filhos->filhos->token.categoria, "_StringLiteral")){
        //            sprintf(msg, "%s", no->filhos->filhos->token.token);
        //        }
    }
//    sprintf(str_print, "%s %s)", "call i32 (i8*, ...)* @printf(i8*", msg);
//    fprintf(arq_llvm, "%s", str_print);
    //call i32 (i8*, ...)* @printf(i8* %msg, i32 12, i8 42)
    //    printf("no - write: %s\n", no->token);
    //    no = no->filhos;
    //    Tree* exp_tree = no->filhos;
    //    printf("write: %s", exp_tree->token);

    //    no = no->filhos;
    //    Tree* exp_tree = no->filhos;
    //    char* exp_rst = analisa_funcao(exp_tree);
    //    printf("");
    //    
    //    no = no->irmaos;
    //    analisa_funcao(no);
    //    printf("br label %_%s\n", label1);
    //    printf("_%s\n", label3);
    return NULL;
}

void gera_caractere(Tree* no) {
    if (no == NULL) return;
    if (strcmp(no->token.token, ",") == 0) {
        //printf(",\n%s\n", no->filhos->token.token);
        printf("i32 %s, ", no->filhos->token.token);
        gera_caractere(no->filhos->irmaos);
    }else {
        printf("i32 %s)", no->token.token);
//        printf(",\n%s\n", no->token.token);
    }
    //call i32 (i8*, ...)* @printf(i8* getelementptr ([7 x i8]* %STR0, i32 0, i32 0)i32 1, i32 2, i32 6, i32 5)
}

char* gera_operador(char str) {
    switch (str) {
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

char* gerar_if_label() {
    char* var = gerar_rotulo(&contador_label, "if_");
    return var;
}

char* gerar_loop_label() {
    char* var = gerar_rotulo(&contador_label, "loop_");
    return var;
}

char* gerar_variavel() {
    char* var = gerar_rotulo(&contador_variavel, LOCAL_V);
    return var;
}

char* gerar_rotulo(int* contador, char* label) {
    char retorno[10];
    char numero[11];
    strcpy(retorno, label);
    sprintf(numero, "%d", (*contador)++);
    strcat(retorno, numero);
    char* ret = malloc(sizeof (char)*10);
    strcpy(ret, retorno);

    return ret;
}

char* concat_str(char* des, char* src) {
    char* ret;
    char a[500];
    char b[500];
    strcpy(a, des);
    strcpy(b, src);
    strcat(a, b);
    ret = a;
    return ret;
}