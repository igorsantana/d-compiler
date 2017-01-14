#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#ifdef __cplusplus
extern "C" {
#endif
    
typedef struct Caracter      Caracter;   
typedef struct Token         Token;
typedef struct Producao      Producao;    
typedef struct Elemento      Elemento;   
typedef struct Pilha         Pilha;   
typedef struct Tree          Tree;
typedef struct ItemLista     ItemLista;

typedef struct ItemVariavel  ItemVariavel;
typedef struct ValorVariavel ValorVariavel;

typedef struct Escopo        Escopo;

struct Caracter      { char c[100]; };
struct Token         { char* categoria; char token[50]; int linha; int coluna; };
struct Producao      { Caracter caracteres[100]; int indexCaracter; };
struct Elemento      { char c[100]; Elemento *abaixo; Elemento *acima; };
struct Pilha         { Elemento *topo; };
struct Tree          { Token token; Tree *pai; Tree *irmaos; Tree *filhos; };
struct ItemLista     { Tree* el; ItemLista* irmao; int id; };

struct ItemVariavel  { ItemVariavel*  proximo; ValorVariavel* primeiro; char* nome; };
struct ValorVariavel { ValorVariavel* proximo; int profundidade; char* tipo; char* categoria; void* valor; };

struct Escopo        { char* nome; int profundidade; Escopo* proximo; };

/* Funções relacionadas a pilha */   

Pilha       inicializa_pilha(char * t);
Elemento*   desempilha(Pilha* pilha);
void        empilha(Pilha* pilha, char * elemento);
    
/* Funções relacionadas a árvore */

Tree*   create_tree (Tree * pai, Token tok);
Tree*   find_node   (Tree* root, Token tok );
int     add_son     (Tree* root, Token tok_son);
int     add_brother (Tree* root, Token tok_node, Token tok_son);
void    iterate_sons(Tree* root, void (*f)(Tree*, int) );
int     reduce_tree (Tree* root);

/* Funções relacionadas a lista */

ItemLista*  create_list(Tree* root);
void        add_list(ItemLista* root, Tree* to_add);
void        print_list(ItemLista* root);
ItemLista*  concat_list(ItemLista* l1, ItemLista* l2);
ItemLista*  last_element(ItemLista*);
ItemLista*  find_element(ItemLista* list);

/* Funcoes relacionadas a lista da tabela de simbolos */
ValorVariavel* create(int profundidade, char* tipo, char* categoria, void* valor);
ItemVariavel*  create_lista();
void           print_variavel(ItemVariavel* raiz);
void           add_variavel(ItemVariavel* raiz, char* nome);
void           add_item(ItemVariavel* raiz, char* nome, ValorVariavel* variavel);
void*          get_valor(ItemVariavel* raiz, char* nome, int profundidade);

/* Funcoes relacionadas ao Escopo */
Escopo* create_escopo();
void    add_escopo(Escopo* raiz, char* nome, int profundidade);
Escopo* get_escopo(Escopo* raiz, char* nome);

#ifdef __cplusplus
}
#endif

#endif /* ESTRUTURAS_H */

