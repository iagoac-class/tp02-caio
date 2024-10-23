#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>       
#include "arvores.h"

//Funções árvore binária
struct No* inserir_binaria(struct No* raiz, int valor){
    if(raiz == NULL){
        struct No* novoNo = (struct No*)malloc(sizeof(struct No));
        novoNo->valor = valor;
        novoNo->esquerda = novoNo->direita = NULL;
        return novoNo;
    }

    if(valor < raiz->valor){
        raiz->esquerda = inserir_binaria(raiz->esquerda, valor);
    }else if(valor > raiz->valor){
        raiz->direita = inserir_binaria(raiz->direita, valor);
    }

    return raiz;
}

struct No* remover_binaria(struct No* raiz, int valor){
    if(raiz == NULL){
        return raiz;
        printf("\n");
        printf("Erro na remoção árvore vazia!\n");
    }

    if(valor < raiz->valor){
        raiz->esquerda = remover_binaria(raiz->esquerda, valor);
    }else if(valor > raiz->valor){
        raiz->direita = remover_binaria(raiz->direita, valor);
    }else{
        if(raiz->esquerda == NULL){
            struct No* temp = raiz->direita;
            free(raiz);
            return temp;
        }else if(raiz->direita == NULL){
            struct No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        struct No* temp = menor_valor_no(raiz->direita);
        raiz->valor = temp->valor;
        raiz->direita = remover_binaria(raiz->direita, temp->valor);
    }
    return raiz;
}

struct No* menor_valor_no(struct No* no){
    struct No* atual = no;
    while(atual && atual->esquerda != NULL){
        atual = atual->esquerda;
    }
    return atual;
}

double arvore_binaria(int instancia_num) {
    double tempo = 0;
    clock_t begin = clock();

    struct No* raiz = NULL;
    
    // Processar o arquivo correspondente à instância
    char nome_arquivo[30];
    sprintf(nome_arquivo, "instancias/%d.txt", instancia_num);

    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de instância.\n");
        exit(1);
    }

    //int i = 0, r = 0;

    char operacao;
    int valor;
    while (fscanf(arquivo, " %c %d", &operacao, &valor) != EOF) {
        if (operacao == 'I') {
            raiz = inserir_binaria(raiz, valor);
            //i++;
        } else if (operacao == 'R') {
            raiz = remover_binaria(raiz, valor);
            //r++;
        }
    }

    fclose(arquivo);
    
    clock_t end = clock();
    // calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
    tempo += (double)(end - begin) / CLOCKS_PER_SEC;
    //printf("\nForam inseridos: %d números | Foram removidos: %d números", i, r);
    return (tempo);
}

//Funções árvore AVL
int altura(struct NoAVL* no){
    if(no == NULL){
        return 0;
    }
    return no->altura;
}

int max(int a, int b){
    return (a > b) ? a : b;
}

int fator_balanceamento(struct NoAVL *no){
    if(no == NULL){
        return 0;
    }
    return altura(no->esquerda) - altura(no->direita);
}

struct NoAVL* rotacao_direita(struct NoAVL* y){
    struct NoAVL* x = y->esquerda;
    struct NoAVL* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}

struct NoAVL* rotacao_esquerda(struct NoAVL* x){
    struct NoAVL* y = x->direita;
    struct NoAVL* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(x->direita)) + 1;

    return y;
}

struct NoAVL* rotacao_esquerda_direita(struct NoAVL* raiz){
    raiz->esquerda = rotacao_esquerda(raiz->esquerda);
    return rotacao_direita(raiz);
}

struct NoAVL* rotacao_direita_esquerda(struct NoAVL* raiz){
    raiz->direita = rotacao_direita(raiz->direita);
    return rotacao_esquerda(raiz);
}

struct NoAVL* inserir_AVL(struct NoAVL* raiz, int valor){
    if(raiz == NULL){
        struct NoAVL* novoNo = (struct NoAVL*) malloc(sizeof(struct NoAVL));
        novoNo->valor = valor;
        novoNo->esquerda = novoNo->direita = NULL;
        novoNo->altura = 1;
        return novoNo;
    }

    if (valor < raiz->valor){
        raiz->esquerda = inserir_AVL(raiz->esquerda, valor);
    }else if(valor > raiz->valor){
        raiz->direita = inserir_AVL(raiz->direita, valor);
    }else{
        return raiz;
    }

    raiz->altura = 1 + max(altura(raiz->esquerda), altura(raiz->direita));

    int balance = fator_balanceamento(raiz);

    if(balance > 1 && valor < raiz->esquerda->valor){
        return rotacao_direita(raiz);
    }

    if(balance < -1 && valor > raiz->direita->valor){
        return rotacao_esquerda(raiz);
    }

    if(balance > 1 && valor > raiz->esquerda->valor){
        return rotacao_esquerda_direita(raiz);
    }

    if(balance < -1 && valor < raiz->direita->valor){
        return rotacao_direita_esquerda(raiz);
    }

    return raiz;
}

struct NoAVL* menor_valor_no_AVL(struct NoAVL* no) {
    struct NoAVL* atual = no;
    while (atual && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}


struct NoAVL* remover_AVL(struct NoAVL* raiz, int valor) {
    if (raiz == NULL) {
        printf("Erro: Valor não encontrado!\n");
        return raiz;
    }

    if (valor < raiz->valor) {
        raiz->esquerda = remover_AVL(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = remover_AVL(raiz->direita, valor);
    } else {
        // Caso 1: Nó com apenas um filho ou nenhum
        if (raiz->esquerda == NULL) {
            struct NoAVL* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            struct NoAVL* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        // Caso 2: Nó com dois filhos
        struct NoAVL* temp = menor_valor_no_AVL(raiz->direita);
        raiz->valor = temp->valor;
        raiz->direita = remover_AVL(raiz->direita, temp->valor);
    }

    // Atualiza a altura do nó pai
    raiz->altura = 1 + max(altura(raiz->esquerda), altura(raiz->direita));

    // Verifica o fator de balanceamento
    int balance = fator_balanceamento(raiz);

    // Se o nó ficou desbalanceado, existem 4 casos a serem tratados

    // Caso 1: Rotação à direita
    if (balance > 1 && fator_balanceamento(raiz->esquerda) >= 0) {
        return rotacao_direita(raiz);
    }

    // Caso 2: Rotação à esquerda-direita
    if (balance > 1 && fator_balanceamento(raiz->esquerda) < 0) {
        raiz->esquerda = rotacao_esquerda(raiz->esquerda);
        return rotacao_direita(raiz);
    }

    // Caso 3: Rotação à esquerda
    if (balance < -1 && fator_balanceamento(raiz->direita) <= 0) {
        return rotacao_esquerda(raiz);
    }

    // Caso 4: Rotação à direita-esquerda
    if (balance < -1 && fator_balanceamento(raiz->direita) > 0) {
        raiz->direita = rotacao_direita(raiz->direita);
        return rotacao_esquerda(raiz);
    }

    return raiz;
}

double arvore_balanceada(int instancia_num) {
    double tempo = 0;
    clock_t begin = clock();

    struct NoAVL* raiz = NULL;

    char nome_arquivo[30];
    sprintf(nome_arquivo, "instancias/%d.txt", instancia_num);

    FILE *arquivo = fopen(nome_arquivo, "r");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo de instância.\n");
        exit(1);
    }

    //int i = 0, r = 0;

    char operacao;
    int valor;
    while(fscanf(arquivo, "%c %d", &operacao, &valor) != EOF){
        if(operacao == 'I'){
            raiz = inserir_AVL(raiz, valor);
            //i++;
        }else if(operacao == 'R'){
            //raiz = remover_AVL(raiz, valor);
            //r++;
        }
    }

    fclose(arquivo);

    
    clock_t end = clock();
    // calcula o tempo decorrido encontrando a diferença (end - begin) e
    //printf("\nForam inseridos: %d números | Foram removidos: %d números\n", i, r);
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
    tempo += (double)(end - begin) / CLOCKS_PER_SEC;
    return (tempo);
}


int main(int argc, char* argv[]) {
    ///////////////////////////////////////////////////////////
    /////////////////// Leitor de instâncias //////////////////
    ///////////////// Não deve ser modificado /////////////////
    ///////////////////////////////////////////////////////////
    int instancia_num = -1;
    instancia_num = atoi(argv[1]);
    if (instancia_num <= 0 || instancia_num > 10) {
        printf("Para executar o código, digite ./arvores x\nonde x é um número entre 1 e 10 que simboliza a instância utilizada\n");
        exit(0);
    }
    
    double tempo_n_balanceada = arvore_binaria(instancia_num);
    double tempo_balanceada = arvore_balanceada(instancia_num);

    printf("Árvore binária não-balanceada: %f\n", tempo_n_balanceada);
    printf("Árvore balanceada (AVL): %f\n", tempo_balanceada);

    return (1);
}