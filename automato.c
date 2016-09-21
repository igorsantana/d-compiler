#include "automato.h"
#include <string.h>
#include <regex.h>

char* analisarToken(char string[]) {
    char identificadoresExp[]   = "^(([:alpha:]{1}([.]*))|(_[^_][.]*))$";
    char stringsExp[]           = "^\".*\"[cwd]{0,1}$";
    char integerExp[]           = "^[[:digit:]]*[ulUL]?$";
    char caracterExp[]          = "\'\\?[[:word:]]{1}\'";
    
    regex_t regExpIdentificador;
    regex_t regExpString;
    regex_t regExpInteger;
    regex_t caracterExp;
    
    regcomp(&regExpIdentificador, identificadoresExp, REG_EXTENDED|REG_NOSUB);
    regcomp(&regExpString, stringsExp, REG_EXTENDED|REG_NOSUB);
    regcomp(&regExpInteger, integerExp, REG_EXTENDED|REG_NOSUB);
    
    if(regexec(&regExpInteger, string, 0, (regmatch_t *)NULL, 0)){
        return "INTEGER";
    }
    if(regexec(&regExpIdentificador, string, 0, (regmatch_t *)NULL, 0)){
        return "IDENTIFICADOR";
    }
    if(regexec(&regExpString, string, 0, (regmatch_t *)NULL, 0)){
        return "STRING";
    }
    
    
   
    return "ERROR";

}
