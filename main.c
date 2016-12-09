#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"
#include "lexico.h"

int main(int argc, char** argv) {
    
    char nomeArquivo[30] = {'e', 'e', '.', 'd'};
    FILE * arquivo;
    if ((arquivo = fopen(nomeArquivo, "r")) == NULL) {
        printf("Arquivo não encontrado!");
    }
    arquivo_leitura(arquivo);
    Token x = getToken();
    printf("Token: %s do tipo %s", x.token, x.categoria);
    return (EXIT_SUCCESS);
}

