#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

#define TAM_MAX_CARACTER 100
#define TAM_MAX_CONJUNTO 100


FILE *      arquivo_preditivo;
Caracter    conjuntoT[TAM_MAX_CONJUNTO];
Caracter    conjuntoNT[TAM_MAX_CONJUNTO];
Producao    matrizPreditiva[TAM_MAX_CONJUNTO][TAM_MAX_CONJUNTO];
int         indexT = 0;
int         indexNT = 0;


void carregaTabela();
void abrirArquivoTabelaPreditiva();
void leituraDosConjuntos();
int retornaIndiceNT(char * str);
int retornaIndiceT(char * str);

void carregaTabela() {
    abrirArquivoTabelaPreditiva();
    leituraDosConjuntos();
}
void abrirArquivoTabelaPreditiva() {
    if ((arquivo_preditivo = fopen("loadfile.txt", "r")) == NULL) {
        printf("Falha na abertura do arquivo");
    }
}
void leituraDosConjuntos() {
    char bufferAux[TAM_MAX_CARACTER];
    char str1[TAM_MAX_CARACTER], str2[TAM_MAX_CARACTER], str3[TAM_MAX_CARACTER];
    int j = 0, linha, coluna;
    indexT = 0;
    indexNT = 0;


    while (fgets(conjuntoT[indexT].c, sizeof (conjuntoT[indexT].c), arquivo_preditivo)) {
        if (strcmp(conjuntoT[indexT].c, "\n") == 0) {
            break;
        }
        int k;
        for (k = 0; k < strlen(conjuntoT[indexT].c); k++) {
            if (conjuntoT[indexT].c[k] == '\n' || conjuntoT[indexT].c[k] == ' ') {
                conjuntoT[indexT].c[k] = '\0';
            }
        }
        indexT++;
    }

    while (fgets(conjuntoNT[indexNT].c, sizeof (conjuntoNT[indexNT].c), arquivo_preditivo)) {
        if (strcmp(conjuntoNT[indexNT].c, "\n") == 0) {
            break;
        }
        int k;
        for (k = 0; k < strlen(conjuntoNT[indexNT].c); k++) {
            if (conjuntoNT[indexNT].c[k] == '\n' || conjuntoNT[indexNT].c[k] == ' ') {
                conjuntoNT[indexNT].c[k] = '\0';
            }
        }

        indexNT++;
    }
    
    while (fscanf(arquivo_preditivo, "%s %s %[^\n]s\n", &str1, &str2, &str3) != EOF) {
        int i = 0;
        while (i <= strlen(str3)) {
            if (str3[i] != ' ' && str3[i] != '\0') {
                bufferAux[j] = str3[i];
                j++;
                bufferAux[j] = '\0';
            } else {
                linha = retornaIndiceNT(str2);
                coluna = retornaIndiceT(str1);
                
                strcpy(matrizPreditiva[linha][coluna].caracteres[matrizPreditiva[linha][coluna].indexCaracter].c,
                        bufferAux);
                matrizPreditiva[linha][coluna].indexCaracter++;
                bufferAux[0] = '\0';
                j = 0;
            }
            i++;
        }
    }
}

int retornaIndiceNT(char * str) {
    int i;
    for (i = 0; i < indexNT; i++) {
        if (strcmp(conjuntoNT[i].c, str) == 0) {
            return i;
        }
    }
    return -1;
}
int retornaIndiceT(char * str) {
    int i;
    for (i = 0; i < indexT; i++) {
        if (strcmp(conjuntoT[i].c, str) == 0) {
            return i;
        }
    }
    return -1;
}



void printaMatrizPreditiva() {
    int j;
    for (j = 0; j < indexT; j++) {
    }
    int i ;
    for (i = 0; i < indexNT; i++) {
        int j;
        for (j = 0; j < indexT; j++) {
            if (matrizPreditiva[i][j].indexCaracter > 0) {
                int k;
                for (k = 0; k < matrizPreditiva[i][j].indexCaracter; k++) {
                }
            } else {
            }
        }
    }
}