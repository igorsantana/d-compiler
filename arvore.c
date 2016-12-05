#include <stdio.h>
#include <stdlib.h>
//#include "lexico.h"

typedef struct Tree Tree;

struct Tree{
    int identificador;
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
Tree*   create_tree (Tree * pai, int id);
Tree*   last_brother(Tree * t);
Tree*   find_node   (Tree * root,int id);
int     add_son     (Tree* root, int id_node, int id_son);
int     add_brother (Tree* root, int id_node, int id_son);
void    iterate_sons(Tree* root, void (*f)(Tree*, int) );


Tree* create_tree(Tree* pai, int id){
    Tree* no = (Tree*) malloc(sizeof(Tree));
    if(no == NULL) return NULL;
    no->identificador   = id;
    no->pai             = pai;
    no->irmaos          = NULL;
    no->filhos          = NULL;
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

Tree* find_node(Tree* root, int id){
    if(root == NULL) return 0;
    if(root->identificador == id){
        return root;
    }
    Tree* ret = NULL;
    if(root->filhos != NULL){
        ret = find_node(root->filhos, id);
    }
    if(ret == NULL && root->irmaos){
        ret = find_node(root->irmaos, id);
    }
    return ret;
}

int add_son(Tree* root, int id_node, int id_son){
    Tree* node = find_node(root, id_node);
    
    if(node->filhos == NULL){
        node->filhos = create_tree(node, id_son);
        return 1;
    }
    Tree* brother   = last_brother(node->filhos);
    brother->irmaos = create_tree(node, id_son);
    
    if(node->irmaos == NULL) return 0;
    
    return 1;
    
}

int add_brother(Tree* root, int id_node, int id_brother){
    if(root == NULL) return 0;
    Tree* primeiro_irmao    = find_node(root, id_node);
    Tree* node              = last_brother(primeiro_irmao);
    
    node->irmaos = create_tree(primeiro_irmao->pai, id_brother);
    
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

void iterate(Tree* node, int index){
    printf("Pai: [%d], filho: [%d] \n", node->pai->identificador, node->identificador);
}


int main(int argc, char** argv) {
    Tree* root = create_tree(NULL, 0);
    
    add_son(root, 0, 1);
    add_son(root, 0, 2);
    add_son(root, 0, 3);
    
    
    add_son(root, 1, 11);
    add_son(root, 1, 12);
    add_son(root, 1, 13);
        
    iterate_sons(root->filhos, &iterate);
    

}

