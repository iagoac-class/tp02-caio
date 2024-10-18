#ifndef _H_ARVORES
#define _H_ARVORES

// Estrutura da árvore binária
struct No{
    int valor;
    struct No* esquerda;
    struct No* direita;
};

//Funções para árvore binária
struct No* inserir_binaria(struct No* raiz, int valor);
struct No* remover_binaria(struct No* raiz, int valor);
struct No* menor_valor_no(struct No* no);

//Funções para calcular tempo de execução
double arvore_binaria(int instancia_num);
// double arvore_balanceada(int instancia_num);

//Falta definir a estrutura da árvore balanceada e qual árvore balanceada
//Definir às funções de inserção e remoção da árvore balanceada

#endif // _H_ARVORES