

#ifndef AUTOMATO_H
#define AUTOMATO_H

struct token {
    char conteudo[255];
    char tipo[255];
};

char* analisarToken(char string[]);


#endif /* AUTOMATO_H */

