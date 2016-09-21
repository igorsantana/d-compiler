#include "automato.h"
#include <string.h>
#include <stdio.h>
#include <regex.h>

int FLAG = REG_EXTENDED|REG_NOSUB;
const char IDENTIFICADOR[]    = "^([A-Za-z]{1}[a-zA-Z0-9_]*)$|^([_]{1}[a-zA-Z0-9]+[a-zA-Z0-9_]*)$";
const char STRING[]           = "^([A-Za-z]{1}[a-zA-Z0-9_]*)$|^([_]{1}[a-zA-Z0-9]+[a-zA-Z0-9_]*)$";
const char INTEGER[]          = "^[0-9]*[ulUL]?$";
const char CARACTER[]         = "^'{1}[\\]?.{1}'{1}$";
const char PONTO_FLUTUANTE[]  = "^[0-9]+\\.[0-9]+$";
int exec_reg(regex_t regex, char string[]){
    return regexec(&regex, string, 0, (regmatch_t *)NULL, 0) == 0;
}

char* analisarToken(char string[]) {
    regex_t regExpIdentificador, regExpString, regExpInteger,
            regExpCaracter, regExpPontoFlutuante;
//    
    regcomp(&regExpIdentificador,IDENTIFICADOR, FLAG);
    regcomp(&regExpString,STRING, FLAG);
    regcomp(&regExpInteger,INTEGER, FLAG);
    regcomp(&regExpCaracter,CARACTER, FLAG);
    regcomp(&regExpPontoFlutuante,PONTO_FLUTUANTE, FLAG);
    
    if(exec_reg(regExpIdentificador, string))   return "IDENTIFICADOR";
    if(exec_reg(regExpString, string))          return "STRING";
    if(exec_reg(regExpInteger, string))         return "INTEGER";
    if(exec_reg(regExpCaracter, string))        return "CARACTER";
    if(exec_reg(regExpPontoFlutuante, string))  return "PONTO_FLUTUANTE";
    return "TOKEN_INVALIDO";

}
