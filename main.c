#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"
#include "lexico.h"
#include "sintatico.h"

int main(int argc, char** argv) {
    
    char nomeArquivo[30] = {'e', 'e', '.', 'd'};
    FILE * arquivo;
    if ((arquivo = fopen(nomeArquivo, "r")) == NULL) {
        printf("Arquivo não encontrado!");
    }
    arquivo_leitura(arquivo);
//    Token x;
//    do{
//        x = getToken();
//        printf("%s ", x.token, x.categoria);
//    } while (x.linha != -1);

        preditivoDescendente();
    
    
    return (EXIT_SUCCESS);
}

