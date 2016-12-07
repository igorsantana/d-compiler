/* 
 * File:   lexico.h
 * Author: rafael
 *
 * Created on September 12, 2016, 7:42 PM
 */

#ifndef LEXICO_H
#define LEXICO_H

    //estruturas
    struct Token{
        char* categoria;
        char token[50];
        int linha;
        int coluna;
    };
    
    typedef struct Token Token;

    extern void abrirArquivo(char* nome);

    extern Token getToken();
    
    Token pegaProximoToken();
    
    char le_char_arq();
    
    void setaLinhaColuna(Token* token);
    
    int verifica_separador(char c);

#endif /* LEXICO_H */

