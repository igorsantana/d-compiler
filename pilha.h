/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pilha.h
 * Author: igorsantana
 *
 * Created on December 8, 2016, 3:13 PM
 */

#ifndef PILHA_H

#define PILHA_H


typedef struct Elemento Elemento;
typedef struct Pilha Pilha;

struct Elemento {
    Token token;
    Elemento *abaixo;
    Elemento *acima;
};

struct Pilha {
    Elemento *topo;
};
void        empilha(Pilha* pilha, Token token); 
Elemento*   desempilha(Pilha* pilha);
Pilha       inicializa_pilha(Token t);



#endif /* PILHA_H */

