#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "estruturas.h"

/* COMEÇO FUNÇÕES RELACIONADAS A PILHA */
Pilha       inicializa_pilha(char * t);
Elemento*   desempilha(Pilha* pilha);
void        empilha(Pilha* pilha, char * elemento);

Pilha inicializa_pilha(char * t) {
    Pilha p;
    p.topo = malloc(sizeof (Elemento));
    strcpy(p.topo->c, t);
    return p;
}
Elemento* desempilha(Pilha* pilha) {
    if (pilha->topo == NULL) return NULL;

    Elemento* topo_atual = pilha->topo;
    pilha->topo = topo_atual->abaixo;
    return topo_atual;
}
void empilha(Pilha* pilha, char * elemento) {
    Elemento* topo = pilha->topo;
    topo->acima = (Elemento*) malloc(sizeof (Elemento));
    strcpy(topo->acima->c, elemento);
    topo->acima->abaixo = topo;
    pilha->topo = topo->acima;
}
/* FIM FUNÇÕES RELACIONADAS A PILHA */

/* COMEÇO FUNÇÕES RELACIONADAS A ÁRVORE */
Tree*   create_tree (Tree * pai, Token tok);
Tree*   last_brother(Tree * t);
Tree*   find_node   (Tree* root, Token tok );
int     add_son     (Tree* root, Token tok_node, Token tok_son);
int     add_brother (Tree* root, Token tok_node, Token tok_son);
void    iterate_sons(Tree* root, void (*f)(Tree*, int) );

Tree*   create_tree(Tree* pai, Token tok){
    Tree* no = (Tree*) malloc(sizeof(Tree));
    if(no == NULL) return NULL;
    no->token   = tok;
    no->pai     = pai;
    no->irmaos  = NULL;
    no->filhos  = NULL;
    return no;
}
Tree*   last_brother(Tree * t){
    if(t->irmaos == NULL){
        return t;
    }
    Tree* node = t->irmaos;
    while(node->irmaos != NULL){
        node = node->irmaos;
    }
    return node;
}
Tree*   find_node(Tree* root, Token tok){
    if(root == NULL) return 0;
    if(strcmp(tok.token, root->token.token) == 0){
        return root;
    }
    Tree* ret = NULL;
    if(root->filhos != NULL){
        ret = find_node(root->filhos, tok);
    }
    if(ret == NULL && root->irmaos){
        ret = find_node(root->irmaos, tok);
    }
    return ret;
}
int     add_son(Tree* root, Token tok_node, Token tok_son){
    Tree* node = find_node(root, tok_node);
    
    if(node->filhos == NULL){
        node->filhos = create_tree(node, tok_son);
        return 1;
    }
    Tree* brother   = last_brother(node->filhos);
    brother->irmaos = create_tree(node, tok_son);
    
    if(node->irmaos == NULL) return 0;
    
    return 1;
    
}
int     add_brother(Tree* root, Token tok_node, Token tok_brother){
    if(root == NULL) return 0;
    Tree* primeiro_irmao    = find_node(root, tok_node);
    Tree* node              = last_brother(primeiro_irmao);
    
    node->irmaos = create_tree(primeiro_irmao->pai, tok_brother);
    
    if(node->irmaos == NULL) {
        return 0;
    }
    return 1;
}
void    iterate_sons(Tree* root, void (*f)(Tree*, int) ){
    Tree* son = root->filhos;
    int i = 0;
    while(son != NULL){
        (*f)(son, i);
        son = son->irmaos;
        i++;
    }
}

/* FIM FUNÇÕES RELACIONADAS A ÁRVORE */