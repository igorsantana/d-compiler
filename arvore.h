/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   arvore.h
 * Author: igorsantana
 *
 * Created on December 5, 2016, 8:04 PM
 */

#ifndef ARVORE_H
#define ARVORE_H
typedef struct Tree Tree;

struct Tree{
    Token token;
    Tree *pai;
    Tree *irmaos;
    Tree *filhos;
};

typedef struct Tree Tree;

Tree*   create_tree (Tree * pai, Token tok);
Tree*   find_node   (Tree* root, Token tok );
int     add_son     (Tree* root, Token tok_node, Token tok_son);
int     add_brother (Tree* root, Token tok_node, Token tok_son);
void    iterate_sons(Tree* root, void (*f)(Tree*, int) );


#endif /* ARVORE_H */

