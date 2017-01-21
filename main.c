#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "estruturas.h"
#include "lexico.h"
#include "sintatico.h"
#include "gerador-intermediario.h"
#include "semantico.h"

char* nomeArquivo;

void help();
void opcoes_entrada(int argc, char** argv);
void escreve_assembly(char* arq_sem_extensao);
void gera_executavel(char* arq_sem_extensao);  

void help(){
    printf("\nBem vindo ao compilador. Os comandos disponíveis são:\n");
    printf("\t-f\tFile\tExecuta o compilador para o arquivo de entrada. Exemplo: ./compilador -f <arquivo>\n");
    printf("\t-h\tHelp\tMostra na tela os comandos disponíveis para o programa\n");
    exit(EXIT_SUCCESS);
}
void opcoes_entrada(int argc, char** argv){
    int opt;
    while((opt = getopt(argc, argv, "f:hv")) != -1){
        switch(opt){
            case 'f':
                nomeArquivo = optarg;
                break;
            case 'h':
                help();
                break;
        }
    }
}
void escreve_assembly(char* arq_sem_extensao){
    FILE *entrada;
    char cmd[256];
    
    sprintf(cmd, "%s%s%s",  "llc ", arq_sem_extensao, ".ll ");
    
    if(!(entrada = popen(cmd, "r"))){
        exit(EXIT_FAILURE);
    }
    pclose(entrada);
}
void gera_executavel(char* arq_sem_extensao){
    FILE *entrada;
    
    char cmd[256];
    
    sprintf(cmd, "%s%s%s%s",  "clang ", arq_sem_extensao,".s -o 2>/dev/null ", arq_sem_extensao);
    
    if(!(entrada = popen(cmd, "r"))){
        exit(EXIT_FAILURE);
    }
    
    pclose(entrada);
}
void executa_assembly(char* arq_sem_extensao){
    char cmd[256];
    sprintf(cmd, "./%s ", arq_sem_extensao);
    system(cmd);
}

void exclui_temporarios(char* arq_sem_extensao){
    char file_ll[34], file_s[34];
    sprintf(file_ll, "%s.ll", arq_sem_extensao);
    sprintf(file_s,  "%s.s", arq_sem_extensao);
    remove(file_ll);
    remove(file_s);
//    remove(arq_sem_extensao);
    
}

int main(int argc, char** argv) {
    
    opcoes_entrada(argc, argv);
    char arq_no_extension[64]; 
    sprintf(arq_no_extension, "%s", nomeArquivo);
    arq_no_extension[strlen(nomeArquivo) -2] = 0;
    
    FILE * arquivo;
    if ((arquivo = fopen(nomeArquivo, "r")) == NULL) {
        printf("Arquivo não encontrado!");
    }
    
    arquivo_leitura(arquivo); 
    
    Tree* raiz = preditivoDescendente();
    
    fclose(arquivo);
    
    executa_semantico(raiz);
    
    gerador_intermediario(raiz, arq_no_extension);
    
//    escreve_assembly(arq_no_extension);
//    
//    gera_executavel(arq_no_extension);
//
//    executa_assembly(arq_no_extension);
    
//    exclui_temporarios(arq_no_extension);
    return (EXIT_SUCCESS);
}

