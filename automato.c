#include "automato.h"
#include <string.h>
#include <regex.h>

int analisaIdentificador(char string[]){
    char identificadores[] = "^(([:alpha:]{1}([.]*))|(_[^_][.]*))";
    regex_t reg;
    regcomp(&reg, identificadores, REG_EXTENDED|REG_NOSUB);
    return regexec(&reg, string, 0, (regmatch_t *)NULL, 0);
}
int analisaString(char string[]){
    char identificadores[] = "^\".*\"[cwd]{0,1}";
    regex_t reg;
    regcomp(&reg, identificadores, REG_EXTENDED|REG_NOSUB);
    return regexec(&reg, string, 0, (regmatch_t *)NULL, 0);
}

char* analisarToken(char string[]) {
    char* ret = "NÃO IDENTIFICADOR";
    if(analisaIdentificador(string) == 0){
        ret = "IDENTIFICADOR";
        return ret;
    }
    if(analisaString(string) == 0){
        ret = "STRING";
        return ret;
    }
    return ret;

}
