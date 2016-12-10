#include <stdio.h>
#ifndef LEXICO_H
#define LEXICO_H

#ifdef __cplusplus
extern "C" {
#endif

Token getToken();
void  arquivo_leitura(FILE* arq);


#ifdef __cplusplus
}
#endif

#endif /* LEXICO_H */

