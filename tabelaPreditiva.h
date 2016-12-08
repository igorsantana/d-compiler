#ifndef SINTATICO_H
#define SINTATICO_H
#define TAM_MAX_CARACTER 100
#define QTDE_MAX_PRODUCAO 100
#define TAM_MAX_CONJUNTO 100

#ifdef __cplusplus
extern "C" {
#endif

struct caracter {
    char c[TAM_MAX_CARACTER];
};

struct producao {
    struct caracter caracter[QTDE_MAX_PRODUCAO];
    int indexCaracter;
};


struct caracter conjuntoT[TAM_MAX_CONJUNTO];
int indexT = 0;
struct caracter conjuntoNT[TAM_MAX_CONJUNTO];
int indexNT = 0;

struct producao matrizPreditiva[TAM_MAX_CONJUNTO][TAM_MAX_CONJUNTO];

void carregaTabela();
int retornaIndiceNT(char * caracter);
int retornaIndiceT(char * caracter);

#ifdef __cplusplus
}
#endif

#endif /* SINTATICO_H */

