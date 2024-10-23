[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/K7_2VYVB)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-2e0aaae1b6195c2367325f4f02e2d04e9abb55f0b24a779b69b11b9e10269abc.svg)](https://classroom.github.com/online_ide?assignment_repo_id=16159211&assignment_repo_type=AssignmentRepo)

# Comparação entre árvores balanceada e não-balanceadas


<img align="center" height="20px" width="60px" src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white"/>

<img align="center" height="20px" width="80px" src="https://img.shields.io/badge/Made%20for-VSCode-1f425f.svg"/> 
</a> 
</div>

<h2><a>Proposta do exercício</a></h2>

Árvores podem sofrer um grande desbalanceamento. Desta forma, o objetivo desse trabalho é verificar o quão lento é uma árvore não balanceada em comparação a uma árvore balanceada. Portanto, iremos implementar duas árvores, uma balanceada e outra não-balanceada e comparar o seu tempo de processamento.

<h2><a>Estrutura do Projeto</a></h2>

- **arvore.h**: Definição da estrutura das arvores utilizadas para comparação e suas respectivas funções.
- **arovre.c**: Implementação da estrutura das arvores e suas funções de remoção e inserçaõ, como também a main e a leitura dos arquivos de instâncias.
- **Makefile**: Arquivo de build para compilar e executar o projeto.
- **/instancias/1.txt**: Diretório contendo os arquivos txt com as instâncias das árvores.

<h2><a> Arquivo de Entrada </h2></a>

Exemplo das intâncias (`1.txt`):

```
I 1
I 2
I 3
I 4
I 5
I 6
I 7
I 8
I 9
I 10

```

Onde a letra 'I' ou 'R', representa respectivamente inserção ou remoção, seguido do número do nó.

---

<h2><a>Explicando a lógica</h2></a>

```c
// Estrutura da árvore binária
struct No{
    int valor;
    struct No* esquerda;
    struct No* direita;
};
```

No trecho de código acima foi implementado a estrutura básica de uma árvore binária, com seu valor de cada nó e seus nó filhos, da subárvore esquerda e direita.

```c
//Funções para árvore binária
struct No* inserir_binaria(struct No* raiz, int valor);
struct No* remover_binaria(struct No* raiz, int valor);
struct No* menor_valor_no(struct No* no);
```

Duas funções padrões de inserir e remover na árvore binária, e uma função chamada menor_valor_no para quando ocorrer a remoção e o nó a ser removido ter dois filhos, essa função menor_valor_no procura o menor valor do nó na subárvore direita, ou sejam o seu substituto.

```c
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
```

A função de inserir da árvore binária é bem simples e intuitiva, no primeiro if verificamos se a raiz é nula, ou seja, não existe árvore. Caso seja, o nó inserido se torna a raiz. Logo abaixo no if e no else if, verificamos se o valor é menor ou maior que a raiz, caso ele seja maior, ele caminha para subárvore esquerda, caso contrário ele vai para subárvore direita. Assim recursivamente, garantindo a estrutura da árvore binária.

```c
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
```

A lógica da remoção da árvore binária também é bem simples, a utlização da função deve gerar mais dúvidas, bom, caso o nó tenha filho direito e esquerdo. Nossa função menor_valor_no irá procurar na subárvore direita, o menor nó que será o substituto do nó removido matendendo assim a estrutura da árvore binária, pois o menor nó da subárvore direta é maior que todos da subárvore esquerda e menor que todos da subárvore direta matendo assim a integridade da estrutura.

```c
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
```
Por fim, o incremento na função já pré implementada que retorna o tempo de execução em milesegundos do algoritmo. Basicamente, ele abre o arquivo e verifca a primeira letra para decidir se será uma remoção ou inserção e já realiza a operação, assim recursivamente até o fim do arquivo de instância.

```c
// Estrtura da árvore AVL
struct NoAVL{
    int valor;
    struct NoAVL *esquerda;
    struct NoAVL *direita;
    int altura;
};
```

No trecho acima, estamos declarando a estrutura do árvore AVL que é semelhante a da árvore binária adicionando apenas o int altura para fim de calcular se um nó está balanceado ou não.

```c
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
```

Declaração das funções para o funcionamento da árvore AVL, uma função para calcular altura, outra para verificar o fator de balanceamento, outra para verificar o maior valor entre dois nós e as funções de inserção e remoção, como também uma função para encontrar o menor_valor_no para aulixar a remoção a encontrar um nó para substituir o nó a ser removido. Como também, às funções de rotação simples e dupla.

```c
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
```

Implementação das funções para a execução da árvore AVL.

<h2><a>Tabela de comparação de tempo de execução</h2></a>

| Arquivo | Árv. balanceada | Árv. Não balanceada |
|---------|-----------------|---------------------|
| 1.txt   | 0.005020        | 0.488574            |
| 2.txt   | 0.006404        | 0.006307            |
| 3.txt   | 0.005764        | 0.971890            |

<b>1.txt:</b> O arquivo em questão tem 10.000 inserções em ordem crescente e 10.000 remoções em ordem crescente.

<b>2.txt:</b> O arquivo em questão tem 10.000 inserções aleatórias e 10.000 remoções aleatórias.

<b>3.txt:</b> O arquivo em questão tem 10.000 inserções em ordem crescente e 10.000 remoções em ordem decrescente.

Bom interpretando a tabela, fica evidente que árvores balanceadas possuem uma vantagem, entretanto há casos que ela pode ser mais lenta que uma simples árvore binária como foi o caso do documento 2.txt, em contrapartida no caso do arquivo 1.txt onde às 10.000 inserções são feitas em ordem crescente formando assim uma grande lista, o custo para removê-las é bem mais alto comparada com uma árvore balanceada para a mesma entrada de dados, é interessante de se reparar que à diferença no tempo de execução na árvore não balanceada no arquivos 1.txt para o 3.txt, é quase o dobro. Isto ocorre, pois como nosso arquivo 3.txt está removendo em ordem decrescente, nosso algoritmo deve fazer o dobro de comparações comparado ao arquivo 1.txt onde ocorre a remoção em ordem crescente. 


---

<h2><a>Compilando</a></h2>


| Comando                |  Função                                                                                           |                     
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make all`                | Compila o programa utilizando o gcc           |
|  `./arvore 1 ou 2 ou 3`            | Executa o programa com base no arquivo de entreda desejado após a realização da compilação                                 |


<h2><a>Observações</h2></a>

- Os arquivos na pasta instancias foram modificados para a extensão .txt, anteriormente estavam sem extensão.

<h2><a>Dados</a></h2>

<p>Disciplina: Algoritmos e Estrutura De Dados II 2024-2

Aluno: Caio Fernando Dias RA: 2020.1.08.046
Aluno: Eurico Santiago Climaco Rodrigues

Professor: Iago Augusto de Carvalho

Data: 23/10/2024</p>

<h2><a>Contato</a></h2>

<div> 
  <a href="https://github.com/Caio-Fernando-Dias"><img src="https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white"></a>
  <a href = "mailto:caio.dias@sou.unifal-mg.edu.br"><img src="https://img.shields.io/badge/-Gmail-%23333?style=for-the-badge&logo=gmail&logoColor=white" target="_blank"></a>
</div>