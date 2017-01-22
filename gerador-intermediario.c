/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "semantico.h"


#define NUMBER "number"
#define SYMBOL "SIMBOLO"
#define LOCAL_V "%T"
#define GLOBAL_V "%G"

FILE * arq_llvm;
Escopo* lista_escopo;
ItemVariavel* lista_variavel; 

int contador_label;
int contador_variavel;
int contador_print_gerador = 0;
int contador_escopo = 0;
int ponteiro_escopo = -1;
int escopo[10];


int gerador_intermediario(Tree* arvore, char* file);
void abrirArquivoLLVM(char* filename);
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
char* gerar_uso_variavel(Tree* no);
char* gera_id(Tree* no);
char* gera_if(Tree* no);
char* gera_comparacao(Tree* no);
char* gera_loop(Tree* no);
void gera_constantes_write();
char* gera_write(Tree* no);
//Funções auxiliares para geração de codigo
char* gera_operador(char str);
char* gerar_if_label();
char* gerar_loop_label();
char* gerar_variavel();
char* gerar_global();
char* gerar_temporario();
char* gerar_rotulo(int* contador, char* label);
char* concat_str(char* des, char* src);
ValorVariavel* pega_valor_variavel(char* var);
char* comando_comp_LLVM(char * str);
void cria_str_global(char* str_global, int i);
// Teste:
char* gera_caractere(Tree* no);

int gerador_intermediario(Tree* arvore, char* filename) {
    lista_escopo = get_raiz_escopo();
    lista_variavel = get_raiz_variavel();
    
    abrirArquivoLLVM(filename);
    
    int contador_prints;
    contador_print_gerador = 0;
    char** prints = get_prints(&contador_prints);
    
    int i = 0;
    for (i; i < contador_prints; i++) {
        gera_constantes_write(i, prints[i]);
    }
    fprintf(arq_llvm, "declare i32 @printf(i8* , ...)\n");
    
    fprintf(arq_llvm, "define i32 @main(){\n");
    analisa_funcao(arvore);
    fprintf(arq_llvm, "ret i32 0\n}");
    fclose(arq_llvm);
    return 1;
}

void abrirArquivoLLVM(char* filename) {
    char nome_arq_llv[34];
    sprintf(nome_arq_llv, "%s.%s", filename, "ll");
    if ((arq_llvm = fopen(nome_arq_llv, "w")) == NULL) {
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
    int i;
    for (i = 0; i < 3; i++) {
        if (!strcmp(tipos[i], tok->token)) {
            return 1;
        }
    }
    return 0;
}

int eh_operacao(Token* tok) {
    char operandos[4][2] = {"+", "-", "*", "/"};
    int i;
    for (i = 0; i < 4; i++) {
        if (!strcmp(operandos[i], tok->token)) {
            return 1;
        }
    }

    return 0;
}

int eh_comparacao(Token* tok) {
    char simbolos[6][5] = {"==", "!=", ">", ">=", "<", "<="};
    int i ;
    for (i = 0; i < 6; i++) {
        if (!strcmp(simbolos[i], tok->token)) {
            return 1;
        }
    }
    return 0;
}

char* gera_escopo(Tree* no) {
    escopo[++ponteiro_escopo] = contador_escopo++;
    no = no->filhos;
    char* ret = analisa_funcao(no);
    ponteiro_escopo--;
    
    return ret;
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
    char* variavel = NULL;
    char* a = NULL;
    char* b = NULL;
    Tree* current = no->filhos;
    a = analisa_funcao(current);
    current = current->irmaos;
    b = analisa_funcao(current);
    variavel = gerar_variavel();
    char* op = gera_operador(no->token.token[0]);
    fprintf(arq_llvm, "%s = %s i32 %s, %s\n", variavel,op,a,b);
    return variavel;
}

char* gera_declaracao(Tree* no) {
    Tree* atual = no = no->filhos;
    char* esq = NULL;
    char* dir = NULL;    
    if (!strcmp("=", atual->token.token)) {
        atual = atual->filhos; //  vai do = pro id
    }
    ValorVariavel* item = pega_valor_variavel(atual->token.token); 
    if(!item->escapa && atual == no){
        return;
    }else if(item->escapa){
        esq = gerar_uso_variavel(atual);
        fprintf(arq_llvm, "%s = alloca i32\n", esq);       
    }
    if (strcmp("=", no->token.token)) {
        return esq;
    }
    return analisa_funcao(no);
}

char* gera_atribuicao(Tree* no) {
    char buffer[100];
    char* esq;
    char* dir;
    Tree* atual = no->filhos;
    no = no->filhos;
    ValorVariavel* item = pega_valor_variavel(atual->token.token); 
    esq = gerar_uso_variavel(no);
    no = no->irmaos;
    dir = analisa_funcao(no);
    if(item->escapa){
        fprintf(arq_llvm, "store i32 %s, i32* %s\n", dir, esq);
    }else{
        fprintf(arq_llvm, "%s = add i32 %s, 0 \n", esq, dir);
    }

    return esq;
}

char* gerar_uso_variavel(Tree* no){
    ValorVariavel* item = pega_valor_variavel(no->token.token);
    if(item->temp != NULL && item->temp != -1){
        return item->temp;
    }
    if(item->escapa){
        item->temp  = gerar_global();
    }else{
        item->temp  = gerar_temporario();
    }
    return item->temp;
}

char* gera_id(Tree* no) {
    ValorVariavel* item = pega_valor_variavel(no->token.token);
    if(item->escapa){
        char* temp = gerar_variavel();
        fprintf(arq_llvm,"%s = load i32, i32* %s\n",temp, item->temp);
        return temp;
    }        
    return item->temp;
    
}

ValorVariavel* pega_valor_variavel(char* var){
    char nome_escopo[10];
    sprintf(nome_escopo,"scope_%i", escopo[ponteiro_escopo]);
    return encontra_escopo_declarado(lista_variavel,lista_escopo,nome_escopo,var);
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
    Tree* bloco_tree = no->irmaos;
    if(!strcmp(exp_tree->token.token,")")){
        bloco_tree = exp_tree->irmaos;
        exp_tree = exp_tree->filhos;
    }
    char* exp_rst = analisa_funcao(exp_tree);
    char* if_label = gerar_if_label();
    fprintf(arq_llvm, "br i1 %s, label %_t_%s, label %_end_%s\n_t_%s:\n", exp_rst, if_label, if_label, if_label);
    analisa_funcao(bloco_tree);
    fprintf(arq_llvm, "br label %_end_%s\n_end_%s:", if_label, if_label);
    if(!strcmp(no->filhos->token.token,")")){
        analisa_funcao(no->irmaos);
    }
    return NULL;

}

char* gera_comparacao(Tree* no) {
    char * comando_cmp = comando_comp_LLVM(no->token.token);
    no = no->filhos;
    char* esquerda = analisa_funcao(no);
    no = no->irmaos;
    char* direita = analisa_funcao(no);
    char* ret = gerar_variavel();
    fprintf(arq_llvm, "%s = icmp %s i32 %s, %s\n", ret, comando_cmp, esquerda, direita);
    return ret;
}

char* gera_loop(Tree* no) {
    no = no->filhos;
    Tree* exp_tree = no->filhos;
    Tree* bloco_tree = no->irmaos;
    if(!strcmp(exp_tree->token.token,")")){
        bloco_tree = exp_tree->irmaos;
        exp_tree = exp_tree->filhos;
    }
    char * label1 = gerar_loop_label();
    char * label2 = gerar_loop_label();
    char * label3 = gerar_loop_label();
    char cond[100];

    fprintf(arq_llvm, "br label %_%s\n", label1);
    fprintf(arq_llvm, "_%s:\n", label1);
    char* exp_rst = analisa_funcao(exp_tree);
    fprintf(arq_llvm, "br i1 %s, label %_%s, label %_%s\n", exp_rst, label2, label3);
    fprintf(arq_llvm, "_%s:\n", label2);
    analisa_funcao(bloco_tree);
    fprintf(arq_llvm, "br label %_%s\n", label1);
    fprintf(arq_llvm, "_%s:\n", label3);
    
    if(!strcmp(no->filhos->token.token,")")){
        analisa_funcao(no->irmaos);
        
    }
    return NULL;
}

void gera_constantes_write(int i, char* str) {
    int length = strlen(str)-2;
    char str_global[20];
    cria_str_global(&str_global, i);
    fprintf(arq_llvm, "%s = internal constant [%i x i8] c%s\n", str_global, length, str);
}

char* gera_write(Tree* no) {
    if (!strcmp(no->filhos->token.token, "(")) {
        Tree* t_aux;

        t_aux = no->filhos;
        while (t_aux->filhos != NULL) {
            Tree* t_aux_irmaos = t_aux;
            while (t_aux_irmaos != NULL) {
                t_aux_irmaos = t_aux_irmaos->irmaos;
            }
            t_aux = t_aux->filhos;
        }

        int length = strlen(t_aux->token.token)-2;
        char* params = gera_caractere(t_aux->irmaos);
        fprintf(arq_llvm, "call i32 (i8*, ...) @printf(i8* getelementptr ([%i x i8], [%i x i8]* @STR_%i, i32 0, i32 0) %s)\n", length, length, contador_print_gerador,params);
        contador_print_gerador++;
    }
    return NULL;
}

void cria_str_global (char* str_global, int i) {
    char to_return[20];
    sprintf(to_return, "%s_%i", "@STR", i);
    strcpy(str_global, to_return);
}

char* gera_caractere(Tree* no) {
    if (no == NULL || !strcmp(no->token.token, ")")) return "";
    char buffer[100];
    char* ret = malloc(sizeof(char) * 100);
    strcpy(buffer,ret);
    if (strcmp(no->token.token, ",") == 0) {
        char* param = analisa_funcao(no->filhos);
        sprintf(buffer, ", i32 %s", param);
        strcat(buffer,gera_caractere(no->filhos->irmaos));
    } else {
        char* param = analisa_funcao(no);
        sprintf(buffer, ", i32 %s", param);
    }
    strcpy(ret,buffer);
    return ret;
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

char* gerar_global() {
    char* var = gerar_rotulo(&contador_variavel, GLOBAL_V);
    return var;
}

char* gerar_temporario() {
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