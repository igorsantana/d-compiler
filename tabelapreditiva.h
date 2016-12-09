#include "estruturas.h"
#ifndef TABELAPREDITIVA_H
#define TABELAPREDITIVA_H

#ifdef __cplusplus
extern "C" {
#endif

Caracter conjuntoT[TAM_MAX_CONJUNTO];
Caracter conjuntoNT[TAM_MAX_CONJUNTO];
Producao matrizPreditiva[TAM_MAX_CONJUNTO][TAM_MAX_CONJUNTO];

int retornaIndiceNT(char * str);
int retornaIndiceT(char * str);


#ifdef __cplusplus
}
#endif

#endif /* TABELAPREDITIVA_H */
