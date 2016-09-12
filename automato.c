#include "automato.h"
#include <string.h>

struct token analisarToken(char string[]) {
    struct token x;
    strcpy(x.conteudo, string);
    strcpy(x.tipo, "palavra reservada");
    return x;
}
