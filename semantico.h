#ifndef SEMANTICO_H
#define SEMANTICO_H

#ifdef __cplusplus
extern "C" {
#endif
    char** get_prints(int* size);
    Tree* executa_semantico(Tree* arvore);
    Escopo* get_raiz_escopo();
    ItemVariavel* get_raiz_variavel();

#ifdef __cplusplus
}
#endif

#endif /* SEMANTICO_H */


