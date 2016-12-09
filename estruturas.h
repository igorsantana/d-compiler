#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#ifdef __cplusplus
extern "C" {
#endif
    
typedef struct Caracter Caracter;   
typedef struct Token    Token;
typedef struct Producao Producao;    
typedef struct Elemento Elemento;   
typedef struct Pilha    Pilha;   
typedef struct Tree     Tree;

struct Caracter { char c[100]; };
struct Token    { char* categoria; char token[50]; int linha; int coluna; };
struct Producao { Caracter caracteres[100]; int indexCaracter; };
struct Elemento { char c[100]; Elemento *abaixo; Elemento *acima; };
struct Pilha    { Elemento *topo; };
struct Tree     { Token token; Tree *pai; Tree *irmaos; Tree *filhos; };

/* Funções relacionadas a pilha */   

Pilha       inicializa_pilha(char * t);
Elemento*   desempilha(Pilha* pilha);
void        empilha(Pilha* pilha, char * elemento);
    
/* Funções relacionadas a árvore */

Tree*   create_tree (Tree * pai, Token tok);
Tree*   find_node   (Tree* root, Token tok );
int     add_son     (Tree* root, Token tok_node, Token tok_son);
int     add_brother (Tree* root, Token tok_node, Token tok_son);
void    iterate_sons(Tree* root, void (*f)(Tree*, int) );

#ifdef __cplusplus
}
#endif

#endif /* ESTRUTURAS_H */

