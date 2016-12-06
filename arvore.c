#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexico.h"

typedef struct Tree Tree;

struct Tree{
    Token token;
    Tree *pai;
    Tree *irmaos;
    Tree *filhos;
};
/**
 * Função responsável por criar os nós da árvore.
 * @param pai Nó pai do nó que será criado
 * @param id  Identificador do nó que será criado.
 * @return O nó que foi criado.
 */
Tree*   create_tree (Tree * pai, Token tok);
/**
 * Função responsável por achar o último irmão do nó passado.
 * @param t
 * @return 
 */
Tree*   last_brother(Tree * t);
Tree*   find_node   (Tree* root, Token tok );
int     add_son     (Tree* root, Token tok_node, Token tok_son);
int     add_brother (Tree* root, Token tok_node, Token tok_son);
void    iterate_sons(Tree* root, void (*f)(Tree*, int) );


Tree* create_tree(Tree* pai, Token tok){
    Tree* no = (Tree*) malloc(sizeof(Tree));
    if(no == NULL) return NULL;
    no->token   = tok;
    no->pai     = pai;
    no->irmaos  = NULL;
    no->filhos  = NULL;
    return no;
}

Tree* last_brother(Tree * t){
    if(t->irmaos == NULL){
        return t;
    }
    Tree* node = t->irmaos;
    while(node->irmaos != NULL){
        node = node->irmaos;
    }
    return node;
}

Tree* find_node(Tree* root, Token tok){
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

int add_son(Tree* root, Token tok_node, Token tok_son){
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

int add_brother(Tree* root, Token tok_node, Token tok_brother){
    if(root == NULL) return 0;
    Tree* primeiro_irmao    = find_node(root, tok_node);
    Tree* node              = last_brother(primeiro_irmao);
    
    node->irmaos = create_tree(primeiro_irmao->pai, tok_brother);
    
    if(node->irmaos == NULL) {
        return 0;
    }
    return 1;
}

void iterate_sons(Tree* root, void (*f)(Tree*, int) ){
    Tree* son = root->filhos;
    int i = 0;
    while(son != NULL){
        (*f)(son, i);
        son = son->irmaos;
        i++;
    }
}


