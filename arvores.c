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

// double arvore_balanceada(int instancia_num) {
//     double tempo = 0;
//     clock_t begin = clock();

    
//     clock_t end = clock();
//     // calcula o tempo decorrido encontrando a diferença (end - begin) e
//     // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
//     tempo += (double)(end - begin) / CLOCKS_PER_SEC;
//     return (tempo);
// }


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
    // double tempo_balanceada = arvore_balanceada(instancia_num);

    // printf("%f\n", tempo_balanceada);
    printf("%f\n", tempo_n_balanceada);

    return (1);
}