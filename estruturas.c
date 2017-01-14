#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "estruturas.h"

#define NAO_TERMINAL "NAO_TERMINAL"
#define LAMBDA       "lambda"
#define SEM_VALOR    -1

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


/* COMEÇO FUNÇÕES RELACIONADAS A LISTA*/

ItemLista*  create_list(Tree* root);
void        add_list(ItemLista* root, Tree* to_add);
void        print_list(ItemLista* root);
ItemLista*  concat_list(ItemLista* l1, ItemLista* l2);
ItemLista*  last_element(ItemLista*);
ItemLista*  find_element(ItemLista* list);

ItemLista*  create_list(Tree* root){
    ItemLista* raiz = (ItemLista*) malloc(sizeof(ItemLista));
    if(raiz == NULL) return NULL;
    raiz->el = root;
    raiz->irmao = NULL;
    return raiz;
}
void        add_list(ItemLista* root, Tree* to_add){
    ItemLista* current = last_element(root);
    current->irmao = create_list(to_add);
}
void        print_list(ItemLista* root){
    ItemLista* c = root;
    while(c != NULL){
        printf("Element: %s\n", c->el->token.token);
        c = c->irmao;
    }
}
ItemLista*  concat_list(ItemLista* l1, ItemLista* l2){
    if(l1 == NULL) return l2;
    if(l2 == NULL) return l1;
    
    printf("\nl1\n");
    print_list(l1);
    printf("\nl2\n");
    print_list(l2);
    ItemLista* current = l1;
    
    ItemLista* aux = l1->irmao;
    
    while(aux != NULL){
        current = aux;
        aux = aux->irmao;
    }
    
    aux = l2;
    
    while(aux != NULL){
        add_list(current, aux->el);
        aux = aux->irmao;
    }
    return l1;
}
ItemLista*  last_element(ItemLista* list){
    ItemLista* last = list;
    while(last->irmao != NULL) {
        last = last->irmao;
    }
    return last;
}
ItemLista*  find_leafs(Tree* root, int* number){
    ItemLista* l = NULL;
    
    if(root->filhos == NULL){
        *number += 1;
        printf("%s\n",root->token.token);
        return create_list(root);
    }

    Tree* filho = root->filhos;
    
    while(filho != NULL){
        l  = concat_list(l, find_leafs(filho, number));
        filho = filho->irmaos;
    }
        
    return l;
}

/* FIM FUNÇÕES RELACIONADAS A LISTA */

/* COMEÇO FUNÇÕES RELACIONADAS A LISTA DA TABELA DE SIMBOLOS */

ValorVariavel* create(int profundidade, char* tipo, char* categoria, void* valor);
ItemVariavel*  create_lista();
void           print_variavel(ItemVariavel* raiz);
void           add_variavel(ItemVariavel* raiz, char* nome);
void           add_item(ItemVariavel* raiz, char* nome, ValorVariavel* variavel);
void*          get_valor(ItemVariavel* raiz, char* nome, int profundidade);

ValorVariavel* create(int profundidade, char* tipo, char* categoria, void* valor) {
    ValorVariavel* to_return = malloc(sizeof(ValorVariavel));
                   to_return->proximo = NULL;
                   to_return->profundidade = profundidade;
                   strcpy(&to_return->tipo, tipo);
                   strcpy(&to_return->categoria, categoria);
                   to_return->valor = valor;
    return to_return;
    
}

ItemVariavel* create_lista() {
    ItemVariavel* to_return = malloc(sizeof(ItemVariavel));
                  to_return->primeiro = NULL;
                  to_return->proximo  = NULL;
                  to_return->nome     = NULL;
    return to_return;
}

void print_variavel(ItemVariavel* raiz) {
    ItemVariavel* current = raiz;
    while (current != NULL) {
        current = current->proximo;
    }
}

void add_variavel(ItemVariavel* raiz, char* nome) {
    if (raiz->nome == NULL) {
        strcpy(&raiz->nome, nome);
        return;
    }
    ItemVariavel* current = raiz;
    int flag = 0;
    while (current->proximo != NULL) {
        if (strcmp(&current->nome, nome) == 0) {
            flag = 1;
            break;
        }
        current = current->proximo;
    }
    
    if (flag == 0) { // Nome nao inserido
        ItemVariavel* novo = create_lista();
            strcpy(&novo->nome, nome);
        current->proximo = novo;
    }
}

void add_item(ItemVariavel* raiz, char* nome, ValorVariavel* variavel) {
    ItemVariavel* index = raiz;
    while(index->proximo != NULL) {
        if (strcmp(&index->nome, nome) == 0) {
            break;
        }
        index = index->proximo;
    }
    
    if (index != NULL) {
        ValorVariavel* current = index->primeiro;
        
        if (current == NULL) {
           index->primeiro = variavel;
           return;
        }
        while (current->proximo != NULL) {
            current = current->proximo;
        }
        current->proximo  = variavel;
        variavel->proximo = NULL;
    }
}

void* get_valor(ItemVariavel* raiz, char* nome, int profundidade) {
    ItemVariavel* index = raiz;
    while (index->proximo != NULL) {
        if (strcmp(&index->nome, nome) == 0) {
            break;
        }
        index = index->proximo;
    }
    
    // Entrada nao encontrada:
    if (strcmp(&index->nome, nome) != 0) return SEM_VALOR;
    
    ValorVariavel* current = index->primeiro;
    while (current != NULL) {
        if (current->profundidade == profundidade) {
            return current->valor;
        }
        current = current->proximo;
    }
    return SEM_VALOR;
}

/* FIM FUNÇÕES RELACIONADAS A LISTA DA TABELA DE SIMBOLOS */

/* COMEÇO FUNÇÕES RELACIONADAS AO ESCOPO */
Escopo* create_escopo();
void    add_escopo(Escopo* raiz, char* nome, int profundidade);
Escopo* get_escopo(Escopo* raiz, char* nome);

Escopo* create_escopo() {
    Escopo* to_return = malloc(sizeof (Escopo));
            to_return->profundidade = 0;
            to_return->proximo      = NULL;
    return  to_return;
}

void add_escopo(Escopo* raiz, char* nome, int profundidade) {
    if ((raiz->nome == NULL) && (raiz->profundidade == 0)) {
        strcpy(&raiz->nome, nome);
        raiz->profundidade = profundidade;
        return;
    }
    
    Escopo* novo = create_escopo();
            strcpy(&novo->nome, nome);
            novo->profundidade = profundidade;
    
    Escopo* current;
    for (current = raiz; current->proximo != NULL; current = current->proximo);
    current->proximo = novo;
}

Escopo* get_escopo(Escopo* raiz, char* nome) {
    if (raiz->proximo == NULL) {
        return raiz;
    }
    
    Escopo* current = raiz;
    while (current != NULL) {
        if (strncmp(&current->nome, nome, strlen(&current->nome) - 1) == 0) {
            return current;
        }
        current = current->proximo;
    }
    return NULL;
}

/* FIM FUNÇÕES RELACIONADAS AO ESCOPO */

/* COMEÇO FUNÇÕES RELACIONADAS A ÁRVORE */
Tree*   create_tree (Tree * pai, Token tok);
Tree*   last_brother(Tree * t);
int     add_son(Tree* root, Token tok_son);
Tree*   find_node   (Tree* root, Token tok );
int     add_brother (Tree* root, Token tok_node, Token tok_son);
void    iterate_sons(Tree* root, void (*f)(Tree*, int) );
void    substituir_filhos(Tree* pai, Tree* filho);

void remove_lambda(Tree* pai,Tree* filho,ItemLista* lista, ItemLista* atual);
void remove_no(Tree* pai,Tree* filho);
void remove_filho(Tree* pai, Tree* filho);
int tamanho_filhos(Tree* pai);

Tree*       create_tree(Tree* pai, Token tok){
    Tree* no = (Tree*) malloc(sizeof(Tree));
    if(no == NULL) return NULL;
    no->token   = tok;
    no->pai     = pai;
    no->irmaos  = NULL;
    no->filhos  = NULL;
    return no;
}
Tree*       last_brother(Tree * t){
    if(t->irmaos == NULL){
        return t;
    }
    Tree* node = t->irmaos;
    while(node->irmaos != NULL){
        node = node->irmaos;
    }
    return node;
}
Tree*       find_node(Tree* root, Token tok){
    
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

int     add_son(Tree* root, Token tok_son){
    Tree* node = root;
    
    if(node->filhos == NULL){
        node->filhos = create_tree(node, tok_son);
        return 1;
    }
    Tree* brother   = last_brother(node->filhos);
    brother->irmaos = create_tree(node, tok_son);
    
    if(node->irmaos == NULL) return 0;
    
    return 1;
    
}
int         add_brother(Tree* root, Token tok_node, Token tok_brother){
    if(root == NULL) return 0;
    Tree* primeiro_irmao    = find_node(root, tok_node);
    Tree* node              = last_brother(primeiro_irmao);
    
    node->irmaos = create_tree(primeiro_irmao->pai, tok_brother);
    
    if(node->irmaos == NULL) {
        return 0;
    }
    return 1;
}
void        iterate_sons(Tree* root, void (*f)(Tree*, int) ){
    Tree* son = root->filhos;
    int i = 0;
    while(son != NULL){
        (*f)(son, i);
        son = son->irmaos;
        i++;
    }
}




int         reduce_tree  (Tree* root){
    int size = 0;
    int new_size = -1;
    ItemLista* folhas = find_leafs(root, &size);
    ItemLista* atual;
    
    printf("\n\n");
    atual = folhas;
    while(atual!=NULL){
        printf("%s\n",atual->el->token.token);
        atual = atual->irmao;
    }
    printf("\n");
    
    while(new_size){
        atual = folhas;
        new_size = 0;
        while(atual != NULL){
            Tree* pai = atual->el->pai;
            if(!strcmp(atual->el->token.token,LAMBDA)){
                remove_lambda(pai,atual->el,folhas,atual);
            }else if(pai != NULL && strcmp(pai->token.categoria, NAO_TERMINAL) == 0){
                substituir_filhos(pai,atual->el);
                pai->token = atual->el->token;
                free(atual->el);
                atual->el = pai;
                new_size++;
            }
            atual = atual->irmao;
        }
    }
}

void substituir_filhos(Tree* pai,Tree* filho){
    Tree* antes;
    if(filho->filhos == NULL){
        antes = pai->filhos;
        if(pai->filhos == filho){
            pai->filhos = filho->irmaos;
            return;
        }
        while(antes->irmaos != filho){
            antes = antes->irmaos;
        }
        antes->irmaos = filho->irmaos;
        return;
    }
    Tree* depois;
    if(pai->filhos == filho){
        depois = filho->filhos;
        while(depois->irmaos != NULL){
            depois = depois->irmaos;
        }
        depois->irmaos = filho->irmaos;
        pai->filhos = filho->filhos;
        return;
    }
    
    antes = pai->filhos;
    while(antes->irmaos != filho){
        antes = antes->irmaos;
    }
    depois = filho->filhos;
    while(depois->irmaos!= NULL){
        depois = depois->irmaos;
    }
    antes->irmaos = filho->filhos;
    depois->irmaos = filho->irmaos;
}

void remove_lambda(Tree* pai,Tree* filho,ItemLista* lista, ItemLista* atual){
    while(lista->irmao != atual){
        lista = lista->irmao;
    }
    lista->irmao = atual->irmao;
    free(atual);
    atual = lista;
    remove_no(pai,filho);
}

void remove_no(Tree* pai,Tree* filho){
    if(!strcmp(pai->token.categoria,NAO_TERMINAL) && tamanho_filhos(pai) == 1){
        pai->filhos = NULL;
        remove_no(pai->pai,pai);
        return;
    }
    remove_filho(pai,filho);
}

void remove_filho(Tree* pai, Tree* filho){
    Tree* atual = pai->filhos;
    
    if(atual == filho){
        pai->filhos = filho->irmaos;
        free(filho);
        return;
    }
    
    while(atual->irmaos != filho){
        atual = atual->irmaos;
    }
    
    atual->irmaos = filho->filhos;
    
    free(filho);
}

int tamanho_filhos(Tree* pai){
    int tamanho = 0;
    Tree* atual = pai->filhos;
    while(atual != NULL){
        tamanho++;
        atual = atual->irmaos;
    }
    return tamanho;
}

/* FIM FUNÇÕES RELACIONADAS A ÁRVORE */
