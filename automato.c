#include <string.h>
#include <stdio.h>
#include <regex.h>
#include <stdlib.h>

#define TAMANHO 102
#define FALHA   -1

int FLAG = REG_EXTENDED|REG_NOSUB;
const char IDENTIFICADOR[]    = "^([A-Za-z]{1}[a-zA-Z0-9_]*)$|^([_]{1}[a-zA-Z0-9]+[a-zA-Z0-9_]*)$";
const char STRING[]           = "^\".*\"[cwd]{0,1}$";
const char INTEGER[]          = "^[0-9]*[ulUL]?$";
const char CARACTER[]         = "^'{1}[\\]?.{1}'{1}$";
const char PONTO_FLUTUANTE[]  = "^[0-9]+\\.[0-9]+$";
const char SIMBOLOS[]         = "(^-$|^\\|$|^&){2}$|^>{1,3}=?$|^<>=?$|^<{1,2}=?$|^\\^{1,2}=?$|^=>$|^==$|^\\.{1,3}$|^!(<>$|^<$|^>)?=?$|^(%$|^\\*$|^~$|^\\+{1,2}$|^\\$|^$|^\\-$|^&$|^\\/)=?$|^(\\($|^\\)$|^\\[$|^\\]$|^\\{$|^\\}$|^\\?$|^,$|^;$|^:$|^\\$$|^=$|^@$|^#$)";
const char* PALAVRAS_RESERVADAS[102] = {"abstract", "alias", "align", "asm", "assert", "auto",
                                        "body", "bool", "break", "byte",
                                        "case", "cast", "catch", "cdouble", "cent", "cfloat", "char", "class", "const", "continue", "creal", 
                                        "dchar", "debug", "default", "delegate", "delete", "deprecated", "do", "double", 
                                        "else", "enum", "export", "extern", 
                                        "false", "final", "finally", "float", "for", "foreach", "foreach_reverse", "function", 
                                        "goto", 
                                        "idouble", "if", "ifloat", "immutable", "import", "in", "inout", "int", "interface", "invariant", "ireal", "is", 
                                        "lazy", "long", 
                                        "macro", "mixin", "module", "new", "nothrow", "null", 
                                        "out", "override",
                                        "package", "pragma", "private", "protected", "public", "pure", 
                                        "real", "ref", "return", 
                                        "scope", "shared", "short", "static", "struct", "super", "switch", "synchronized", 
                                        "template", "this", "throw", "true", "try", "typedef", "typeid", "typeof", 
                                        "ubyte", "ucent", "uint", "ulong", "union", "unittest", "ushort", 
                                        "version", "void", "volatile", "wchar", "while", "with"};

/* Funções Externas */

char* analisarToken(char* string);

/* Funções Internas */

int busca_binaria(char *chave);
int exec_reg(regex_t regex, char string[]);

/* Implementações*/

int busca_binaria(char *chave) {
    int inicio = 0;
    int fim    = TAMANHO - 1;
    int meio;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        if (strcmp(PALAVRAS_RESERVADAS[meio], chave) == 0){
            return (meio + 1);
        } else if (strcmp(PALAVRAS_RESERVADAS[meio], chave) > 0){
            fim    = meio - 1;
        } else if (strcmp(PALAVRAS_RESERVADAS[meio], chave) < 0){
            inicio = meio + 1;
        }
    }
    return -1;
}
int exec_reg(regex_t regex, char string[]){
    return regexec(&regex, string, 0, (regmatch_t *)NULL, 0) == 0;
}
char* analisarToken(char* string) {
    regex_t regExpIdentificador, regExpString, regExpInteger,
            regExpCaracter, regExpPontoFlutuante, regExpSimbolos;

    regcomp(&regExpIdentificador,IDENTIFICADOR, FLAG);
    regcomp(&regExpString,STRING, FLAG);
    regcomp(&regExpInteger,INTEGER, FLAG);
    regcomp(&regExpCaracter,CARACTER, FLAG);
    regcomp(&regExpPontoFlutuante,PONTO_FLUTUANTE, FLAG);
    regcomp(&regExpSimbolos,SIMBOLOS, FLAG);
    
    if (busca_binaria(string) > 0)               return "PALAVRA_RESERVADA";
    if (exec_reg(regExpSimbolos, string))        return "SIMBOLO";
    if (exec_reg(regExpIdentificador, string))   return "id";
    if (exec_reg(regExpString, string))          return "_StringLiteral";
    if (exec_reg(regExpInteger, string))         return "_IntegerLiteral";
    if (exec_reg(regExpCaracter, string))        return "CARACTER";
    if (exec_reg(regExpPontoFlutuante, string))  return "PONTO_FLUTUANTE";
    return "TOKEN_INVALIDO";
}


