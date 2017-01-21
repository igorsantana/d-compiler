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
int VERBOSE_MODE = 0;
int contador_escopo_geracao = 0;
int escopo_atual = 0;

void help();
void opcoes_entrada(int argc, char** argv);
void escreve_assembly(char* arq_sem_extensao);
void executa_assembly(char* arq_sem_extensao);  

void help(){
    printf("\nBem vindo ao compilador. Os comandos disponíveis são:\n");
    printf("\t-f\tFile\tExecuta o compilador para o arquivo de entrada. Exemplo: ./compilador -f <arquivo>\n");
    printf("\t-h\tHelp\tMostra na tela os comandos disponíveis para o programa\n");
    printf("\t-v\tVerbose\tDurante a execução do programa, mostra na tela o que está acontecendo\n\n");
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
            case 'v':
                VERBOSE_MODE = 1;
                break;
        }
    }
}
void escreve_assembly(char* arq_sem_extensao){
    FILE *entrada;
    char cmd[256];
    int c;
    
    sprintf(cmd, "%s%s%s",  "set -o pipefail; llc ", arq_sem_extensao, ".ll 2>/dev/null; echo $?");
    
    if(!(entrada = popen(cmd, "r"))){
        exit(EXIT_FAILURE);
    }
    
    c = fgetc(entrada) - '0';
    pclose(entrada);
    
    if(c == 1){
        printf("[ERRO] Houve algum erro durante a tradução do arquivo llvm para assembly.\n");
        exit(EXIT_FAILURE);
    }
}
void executa_assembly(char* arq_sem_extensao){
    FILE *entrada;
    
    char cmd[256];
    
    sprintf(cmd, "%s%s%s",  "clang ", arq_sem_extensao,".s");
    
    if(!(entrada = popen(cmd, "r"))){
        exit(EXIT_FAILURE);
    }
    
    pclose(entrada);
    
}


int main(int argc, char** argv) {
    
    opcoes_entrada(argc, argv);
    char arq_no_extension[64]; 
//    strcpy(arq_no_extension, nomeArquivo);
    
//    arq_no_extension[strlen(nomeArquivo) -2] = 0;
    
    FILE * arquivo;
    if ((arquivo = fopen("ee.d", "r")) == NULL) {
        printf("Arquivo não encontrado!");
    }
    
    arquivo_leitura(arquivo); 
    Tree* raiz = preditivoDescendente();
//    executa_semantico(raiz);
    gerador_intermediario(raiz);


    
    return (EXIT_SUCCESS);
}

