#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "estruturas.h"

#define NAO_TERMINAL "NAO_TERMINAL"
#define LAMBDA       "lambda"
#define SEM_VALOR    -1

/* COMEÇO FUNÇÕES RELACIONADAS A PILHA */
Pilha inicializa_pilha(char * t);
Elemento* desempilha(Pilha* pilha);
void empilha(Pilha* pilha, char * elemento);

void printa_pilha(Elemento* pilha);

Pilha inicializa_pilha(char * t) {
    Pilha p;
    p.topo = malloc(sizeof (Elemento));
    strcpy(p.topo->c, t);
    return p;
}

Elemento* desempilha(Pilha* pilha) {
    if (pilha->topo == NULL) return NULL;

    Elemento* topo_atual = pilha->topo;
    free(pilha->topo);
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

void printa_pilha(Elemento* pilha) {
    if (pilha->abaixo != NULL) {
        printa_pilha(pilha->abaixo);
    }
}

/* FIM FUNÇÕES RELACIONADAS A PILHA */


/* COMEÇO FUNÇÕES RELACIONADAS A LISTA*/

ItemLista* create_list(Tree* root);
void add_list(ItemLista* root, Tree* to_add);
void print_list(ItemLista* root);
ItemLista* concat_list(ItemLista* l1, ItemLista* l2);
ItemLista* last_element(ItemLista*);
ItemLista* find_element(ItemLista* list);

ItemLista* create_list(Tree* root) {
    ItemLista* raiz = (ItemLista*) malloc(sizeof (ItemLista));
    if (raiz == NULL) return NULL;
    raiz->el = root;
    raiz->irmao = NULL;
    return raiz;
}

void add_list(ItemLista* root, Tree* to_add) {
    ItemLista* current = last_element(root);
    current->irmao = create_list(to_add);
}

void print_list(ItemLista* root) {
    ItemLista* c = root;
    while (c != NULL) {
        c = c->irmao;
    }
}

ItemLista* concat_list(ItemLista* l1, ItemLista* l2) {
    if (l1 == NULL) return l2;
    if (l2 == NULL) return l1;

    ItemLista* current = l1;

    ItemLista* aux = l1->irmao;

    while (aux != NULL) {
        current = aux;
        aux = aux->irmao;
    }

    aux = l2;

    while (aux != NULL) {
        add_list(current, aux->el);
        aux = aux->irmao;
    }
    return l1;
}

ItemLista* last_element(ItemLista* list) {
    ItemLista* last = list;
    while (last->irmao != NULL) {
        last = last->irmao;
    }
    return last;
}

ItemLista* find_leafs(Tree* root, int* number) {
    ItemLista* l = NULL;

    if (root->filhos == NULL) {
        *number += 1;
        return create_list(root);
    }

    Tree* filho = root->filhos;

    while (filho != NULL) {
        l = concat_list(l, find_leafs(filho, number));
        filho = filho->irmaos;
    }

    return l;
}

/* FIM FUNÇÕES RELACIONADAS A LISTA */

/* COMEÇO FUNÇÕES RELACIONADAS A LISTA DA TABELA DE SIMBOLOS */

ValorVariavel* create(Escopo* escopo, char* tipo, void* valor);
ItemVariavel*  create_lista();
void           print_variavel(ItemVariavel* raiz);
void            add_variavel(ItemVariavel* raiz, char* nome) ;
void           add_item(ItemVariavel* raiz, char* nome, ValorVariavel* variavel);
//void*          get_valor(ItemVariavel* raiz, char* nome, int profundidade);
ValorVariavel* get_valor(ItemVariavel* raiz, Escopo* escopo, char* nome_escopo, char* variavel);
ItemVariavel*  get_variavel(ItemVariavel* raiz, char* variavel);
ValorVariavel* encontra_escopo_declarado(ItemVariavel* raiz, Escopo* lista_escopo, char* nome_escopo, char* variavel);

ValorVariavel* create(Escopo* escopo, char* tipo, void* valor) {
    ValorVariavel* to_return = malloc(sizeof(ValorVariavel));
                   to_return->proximo   = NULL;
                   to_return->anterior  = NULL;
                   to_return->escopo    = escopo;
                   to_return->valor     = valor;
                   to_return->tipo      = tipo;
                   to_return->escapa    = 0;
    return to_return;
}

ItemVariavel* create_lista() {
    ItemVariavel* to_return = malloc(sizeof(ItemVariavel));
                  to_return->primeiro       = NULL;
                  to_return->proximo        = NULL;
                  to_return->nome           = NULL;
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
        raiz->nome = nome;
        return;
    }
    ItemVariavel* current = raiz;
    while (current->proximo != NULL) {
        current = current->proximo;
    }
    current->proximo = create_lista();
    current->proximo->nome = nome;
}

void add_item(ItemVariavel* raiz, char* nome, ValorVariavel* variavel) {
    ItemVariavel* index = raiz;
    
    while(index->proximo != NULL) {
        if (strcmp(index->nome, nome) == 0) {
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
        variavel->anterior = current;
        
        current ->proximo  = variavel;
        variavel->proximo  = NULL;
    }
}

ItemVariavel* get_variavel(ItemVariavel* raiz, char* variavel) {
    ItemVariavel* index = raiz;
    if(index->nome == NULL) return NULL;
    while(index->nome != NULL) {
        if (strcmp(index->nome, variavel) == 0) {
            return index;
        }
        if(index->proximo == NULL) return NULL;
        index = index->proximo;
    }
    
    return NULL;
}

ValorVariavel* get_valor(ItemVariavel* raiz, Escopo* escopo, char* nome_escopo, char* variavel) {
    ItemVariavel* item_variavel = get_variavel(raiz, variavel);
    if (item_variavel == NULL) return NULL;
    
    // Define ponteiro no ultimo:
    ValorVariavel* index = item_variavel->primeiro;
    while(index->proximo != NULL) {
        index = index->proximo;
    }
    
    // Vai do Fim ao Inicio comparando:
    while(index != NULL) {
        if (strcmp(index->escopo->nome, nome_escopo) == 0) {
            return index;
        }
        index = index->anterior;
    }
    return NULL;
}

ValorVariavel* encontra_escopo_declarado(ItemVariavel* raiz, Escopo* lista_escopo, char* nome_escopo, char* variavel) {
    ValorVariavel* current = get_valor(raiz, lista_escopo, nome_escopo, variavel);
    if (current != NULL) return current;
    Escopo* current_escopo = get_escopo(lista_escopo, nome_escopo);
    while (current_escopo->pai != NULL) {
        
        current_escopo = current_escopo->pai;
        current = get_valor(raiz, lista_escopo, current_escopo->nome, variavel);
        
        
        if (current != NULL) {
            return current;
        }
    }
    return NULL;
}

//void* get_valor(ItemVariavel* raiz, char* nome, int profundidade) {
//    ItemVariavel* index = raiz;
//    while (index->proximo != NULL) {
//        if (strcmp(&index->nome, nome) == 0) {
//            break;
//        }
//        index = index->proximo;
//    }
//    
//    // Entrada nao encontrada:
//    if (strcmp(&index->nome, nome) != 0) return SEM_VALOR;
//    
//    ValorVariavel* current = index->primeiro;
//    while (current != NULL) {
//        if (current->profundidade == profundidade) {
//            return current->valor;
//        }
//        current = current->proximo;
//    }
//    return SEM_VALOR;
//}

/* FIM FUNÇÕES RELACIONADAS A LISTA DA TABELA DE SIMBOLOS */

/* COMEÇO FUNÇÕES RELACIONADAS AO ESCOPO */
Escopo* create_escopo();
Escopo*    add_escopo(Escopo* raiz, char* nome, int profundidade, Escopo* pai);
Escopo* get_escopo(Escopo* raiz, char* nome);

Escopo* create_escopo() {
    Escopo* to_return = malloc(sizeof (Escopo));
            to_return->profundidade = 0;
            to_return->nome         = NULL;
            to_return->pai          = NULL;
            to_return->proximo      = NULL;
    return  to_return;
}

Escopo* add_escopo(Escopo* raiz, char* nome, int profundidade, Escopo* pai) {
    if ((raiz->nome == NULL)) {
        raiz->nome         = nome;
        raiz->profundidade = profundidade;
        raiz->pai          = NULL;
        return raiz;
    }
    
    Escopo* novo = create_escopo();
            novo->nome =  nome;
            novo->profundidade = profundidade;
            novo->pai = pai;
    
    Escopo* current;
    for (current = raiz; current->proximo != NULL; current = current->proximo);
    current->proximo = novo;
    
    return current->proximo;
}

Escopo* get_escopo(Escopo* raiz, char* nome) {
    if (raiz->proximo == NULL) {
        return raiz;
    }
    
    Escopo* current = raiz;
    while (current != NULL) {
        if (strcmp(current->nome, nome) == 0) {
            return current;
        }
        current = current->proximo;
    }
    return NULL;
}

/* FIM FUNÇÕES RELACIONADAS AO ESCOPO */

/* COMEÇO FUNÇÕES RELACIONADAS A ÁRVORE */
Tree* create_tree(Tree * pai, Token tok);
Tree* last_brother(Tree * t);
int add_son(Tree* root, Token tok_son);
Tree* find_node(Tree* root, Token tok);
int add_brother(Tree* root, Token tok_node, Token tok_son);
void iterate_sons(Tree* root, void (*f)(Tree*, int));
int separador_inutil(Token token);

void substituir_filhos(Tree* pai, Tree* filho);
void atualiza_pai(Tree* arv);
Tree* ultimo_irmao(Tree* arv);

ItemLista* remove_lambda(Tree* pai, Tree* filho, ItemLista* lista, ItemLista* atual);
void remove_no(Tree* pai, Tree* filho);
void remove_filho(Tree* pai, Tree* filho);
int tamanho_filhos(Tree* pai);

Tree* create_tree(Tree* pai, Token tok) {
    Tree* no = (Tree*) malloc(sizeof (Tree));
    if (no == NULL) return NULL;
    no->token = tok;
    no->pai = pai;
    no->irmaos = NULL;
    no->filhos = NULL;
    return no;
}

Tree* last_brother(Tree * t) {
    if (t->irmaos == NULL) {
        return t;
    }
    Tree* node = t->irmaos;
    while (node->irmaos != NULL) {
        node = node->irmaos;
    }
    return node;
}

Tree* find_node(Tree* root, Token tok) {

    if (root == NULL) return 0;
    if (strcmp(tok.token, root->token.token) == 0) {
        return root;
    }
    Tree* ret = NULL;
    if (root->filhos != NULL) {
        ret = find_node(root->filhos, tok);
    }
    if (ret == NULL && root->irmaos) {
        ret = find_node(root->irmaos, tok);
    }
    return ret;
}

int add_son(Tree* root, Token tok_son) {
    Tree* node = root;

    if (node->filhos == NULL) {
        node->filhos = create_tree(node, tok_son);
        return 1;
    }
    Tree* brother = last_brother(node->filhos);
    brother->irmaos = create_tree(node, tok_son);

    if (node->irmaos == NULL) return 0;

    return 1;

}

int add_brother(Tree* root, Token tok_node, Token tok_brother) {
    if (root == NULL) return 0;
    Tree* primeiro_irmao = find_node(root, tok_node);
    Tree* node = last_brother(primeiro_irmao);

    node->irmaos = create_tree(primeiro_irmao->pai, tok_brother);

    if (node->irmaos == NULL) {
        return 0;
    }
    return 1;
}

void iterate_sons(Tree* root, void (*f)(Tree*, int)) {
    Tree* son = root->filhos;
    int i = 0;
    while (son != NULL) {
        (*f)(son, i);
        son = son->irmaos;
        i++;
    }
}

int reduce_tree(Tree* root) {
    int size = 0;
    int new_size = -1;
    ItemLista* folhas = find_leafs(root, &size);
    ItemLista* atual;

    atual = folhas;
    while (atual != NULL) {
        Tree* pai = atual->el->pai;
        if (!strcmp(atual->el->token.token, LAMBDA)
                ) {
            folhas = remove_lambda(pai, atual->el, folhas, atual);
        }
        atual = atual->irmao;
    }
    atual = folhas;
    while (atual != NULL) {
        atual = atual->irmao;
    }


    while (new_size) {
        atual = folhas;
        new_size = 0;
        while (atual != NULL) {
            Tree* pai = atual->el->pai;
            if (pai != NULL && strcmp(pai->token.categoria, NAO_TERMINAL) == 0) {
                if (pai->filhos == atual->el && atual->el->irmaos == NULL) {
                    substituir_filhos(pai, atual->el);
                    pai->token = atual->el->token;
                    free(atual->el);
                } else {
                    pai->token = atual->el->token;
                    if (atual->el->filhos == NULL) {
                        substituir_filhos(pai, atual->el);
                    }
                    atual->el->token.categoria = NAO_TERMINAL;
                }
                atual->el = pai;
                new_size++;
            }
            atual = atual->irmao;
        }
    }
}

/**
 * 
 * @param token
 * @return 
 */
int separador_inutil(Token token) {
    char separadores_inuteis[3][3] = {";", "{", "}"};
    int i;
    for (i = 0; i < 3; i++) {
        if (!strcmp(separadores_inuteis[i], token.token)) {
            return 1;
        }
    }
    return 0;
}

/**
 * Faz a substituição dos filhos no seu lugar no array de filhos do seu pai
 * @param pai Porteiro para a arvore do pai onde será substituidos os filhos
 * @param filho Ponteiro da arvore do filho o qual sera substituido por seus filhos na arvore pai
 */
void substituir_filhos(Tree* pai, Tree* filho) {
    Tree* antes;
    if (filho->filhos == NULL) {
        if (pai->filhos == filho) {
            pai->filhos = filho->irmaos;
            return;
        }
        antes = pai->filhos;
        while (antes->irmaos != filho) {
            antes = antes->irmaos;
        }
        antes->irmaos = filho->irmaos;
        return;
    }
    Tree* depois;
    if (pai->filhos == filho) {
        depois = ultimo_irmao(filho->filhos);

        depois->irmaos = filho->irmaos;
        pai->filhos = filho->filhos;
        atualiza_pai(pai);
        return;
    }
    antes = ultimo_irmao(pai->filhos);
    depois = ultimo_irmao(filho->filhos);

    antes->irmaos = filho->filhos;
    depois->irmaos = filho->irmaos;
    atualiza_pai(pai);
}

/**
 * Atualiza o pai que está contido no array dos filhos de arv para o proprio arv
 * @param arv Ponteiro para o nó pai
 */
void atualiza_pai(Tree* arv) {
    Tree* atual = arv->filhos;
    while (atual != NULL) {
        atual->pai = arv;
        atual = atual->irmaos;
    }
}

Tree* ultimo_irmao(Tree* arv) {
    if (arv == NULL) {
        return NULL;
    }
    while (arv->irmaos != NULL) {
        arv = arv->irmaos;
    }
    return arv;
}

ItemLista* remove_lambda(Tree* pai, Tree* filho, ItemLista* lista, ItemLista* atual) {
    if (lista == atual) {
        lista = lista->irmao;
    } else {
        ItemLista* current = lista;
        while (current->irmao != atual) {
            current = current->irmao;
        }
        current->irmao = atual->irmao;
    }
    free(atual);
    remove_no(pai, filho);
    return lista;
}

void remove_no(Tree* pai, Tree* filho) {
    if (!strcmp(pai->token.categoria, NAO_TERMINAL) && tamanho_filhos(pai) == 1) {
        pai->filhos = NULL;
        free(filho);
        remove_no(pai->pai, pai);
        return;
    }
    remove_filho(pai, filho);
}

void remove_filho(Tree* pai, Tree* filho) {
    Tree* atual = pai->filhos;

    if (atual == filho) {
        pai->filhos = filho->irmaos;
        free(filho);
        return;
    }

    while (atual->irmaos != filho) {
        atual = atual->irmaos;
    }
    atual->irmaos = filho->irmaos;
    free(filho);
}

int tamanho_filhos(Tree* pai) {
    int tamanho = 0;
    Tree* atual = pai->filhos;
    while (atual != NULL) {
        tamanho++;
        atual = atual->irmaos;
    }
    return tamanho;
}

/* FIM FUNÇÕES RELACIONADAS A ÁRVORE */
