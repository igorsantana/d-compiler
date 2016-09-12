

#ifndef AUTOMATO_H
#define AUTOMATO_H

struct token {
    char conteudo[255];
    char tipo[255];
};

struct token analisarToken(char string[]);


#endif /* AUTOMATO_H */

