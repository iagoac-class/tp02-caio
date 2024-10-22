#ifndef _H_ARVORES
#define _H_ARVORES

// Estrutura da árvore binária
struct No{
    int valor;
    struct No* esquerda;
    struct No* direita;
};

// Estrtura da árvore AVL
struct NoAVL{
    int valor;
    struct NoAVL *esquerda;
    struct NoAVL *direita;
    int altura;
};

//Funções para árvore AVL
int altura(struct NoAVL* no);
int fator_balanceamento(struct NoAVL* no);
int max(int a, int b);
//struct NoAVL* menor_valor_no_AVL(struct NoAVL* no);
struct NoAVL* inserir_AVL(struct NoAVL* raiz, int valor);
//struct NoAVL* remover_AVL(struct NoAVL* raiz, int valor);

//Funções de rotação
struct NoAVL* rotacao_direita(struct NoAVL* y);
struct NoAVL* rotacao_esquerda(struct NoAVL* x);
struct NoAVL* rotacao_esquerda_direita(struct NoAVL* raiz);
struct NoAVL* rotacao_direita_esquerda(struct NoAVL* raiz);

//Funções para árvore binária
struct No* inserir_binaria(struct No* raiz, int valor);
struct No* remover_binaria(struct No* raiz, int valor);
struct No* menor_valor_no(struct No* no);

//Funções para calcular tempo de execução
double arvore_binaria(int instancia_num);
double arvore_balanceada(int instancia_num);

#endif // _H_ARVORES