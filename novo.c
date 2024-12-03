#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int valor;
    struct no *esquerdo, *direito;
    int altura;
}No;

/*
    Função que cria um novo nó
    x -> valor a ser inserido no nó
    Retorna: o endereço do nó criado
*/
No* novoNo(int x){
    No *novo = malloc(sizeof(No));

    if(novo){
        novo->valor = x;
        novo->esquerdo = NULL;
        novo->direito = NULL;
        novo->altura = 0;
    }
    else
        printf("\nERRO ao alocar nó em novoNo!\n");
    return novo;
}

/*
    Retorna o maior dentre dois valores
    a, b -> altura de dois nós da árvore
*/
int maior(int a, int b){
    return (a > b)? a: b;
}


//  Retorna a altura de um nó ou -1 caso ele seja null
int alturaDoNo(No *no){
    if(no == NULL)
        return -1;
    else
        return no->altura;
}

//   Calcula e retorna o fator de balanceamento de um nó
int fatorDeBalanceamento(No *no){
    if(no)
        return (alturaDoNo(no->esquerdo) - alturaDoNo(no->direito));
    else
        return 0;
}

// --------- ROTAÇÕES ---------------------------

// função para a rotação à esquerda
No* rotacaoEsquerda(No *r){
    printf("Ocorreu uma rotação para esquerda\n");
    No *y, *f;

    y = r->direito;
    f = y->esquerdo;

    y->esquerdo = r;
    r->direito = f;

    r->altura = maior(alturaDoNo(r->esquerdo), alturaDoNo(r->direito)) + 1;
    y->altura = maior(alturaDoNo(y->esquerdo), alturaDoNo(y->direito)) + 1;

    return y;
}

// função para a rotação à direita
No* rotacaoDireita(No *r){
    printf("Ocorreu uma rotação para direita\n");
    No *y, *f;

    y = r->esquerdo;
    f = y->direito;

    y->direito = r;
    r->esquerdo = f;

    r->altura = maior(alturaDoNo(r->esquerdo), alturaDoNo(r->direito)) + 1;
    y->altura = maior(alturaDoNo(y->esquerdo), alturaDoNo(y->direito)) + 1;

    return y;
}

No* rotacaoEsquerdaDireita(No *r){
    printf("Ocorreu uma rotação para esquerda-direita: \n");
    r->esquerdo = rotacaoEsquerda(r->esquerdo);
    return rotacaoDireita(r);
}

No* rotacaoDireitaEsquerda(No *r){
    printf("Ocorreu uma rotação para direita-esquerda: \n");
    r->direito = rotacaoDireita(r->direito);
    return rotacaoEsquerda(r);
}


/*
    Função para realizar o balanceamento da árvore após uma inserção ou remoção
    Recebe o nó que está desbalanceado e retorna a nova raiz após o balanceamento
*/
No* balancear(No *raiz){
    int fb = fatorDeBalanceamento(raiz);

    // Rotação à esquerda
    if(fb < -1 && fatorDeBalanceamento(raiz->direito) <= 0)
        raiz = rotacaoEsquerda(raiz);

    // Rotação à direita
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerdo) >= 0)
        raiz = rotacaoDireita(raiz);

    // Rotação dupla à esquerda
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerdo) < 0)
        raiz = rotacaoEsquerdaDireita(raiz);

    // Rotação dupla à direita
    else if(fb < -1 && fatorDeBalanceamento(raiz->direito) > 0)
        raiz = rotacaoDireitaEsquerda(raiz);

    return raiz;
}

/*
    Insere um novo nó na árvore
    raiz -> raiz da árvore
    x -> valor a ser inserido
    Retorno: endereço do novo nó ou nova raiz após o balanceamento
*/
No* inserir(No *raiz, int x){
    if(raiz == NULL) // árvore vazia
        return novoNo(x);
    else{ // inserção será à esquerda ou à direita
        if(x < raiz->valor)
            raiz->esquerdo = inserir(raiz->esquerdo, x);
        else if(x > raiz->valor)
            raiz->direito = inserir(raiz->direito, x);
        else
            printf("\nInsercao nao realizada!\nO elemento %d a existe!\n", x);
    }

    // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
    raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;

    // verifica a necessidade de rebalancear a árvore
    raiz = balancear(raiz);

    return raiz;
}

/*
    Função para remover um nó da Árvore binária balanceada
    Pode ser necessário rebalancear a árvore e a raiz pode ser alterada
    por isso precisamos retornar a raiz
*/
No* remover(No *raiz, int chave) {
    if(raiz == NULL){
        printf("Valor nao encontrado!\n");
        return NULL;
    } else { // procura o nó a remover
        if(raiz->valor == chave) {
            // remove nós folhas (nós sem filhos)
            if(raiz->esquerdo == NULL && raiz->direito == NULL) {
                free(raiz);
                printf("Elemento folha removido: %d !\n", chave);
                return NULL;
            }
            else{
                // remover nós que possuem 2 filhos
                if(raiz->esquerdo != NULL && raiz->direito != NULL){
                    No *aux = raiz->esquerdo;
                    while(aux->direito != NULL)
                        aux = aux->direito;
                    raiz->valor = aux->valor;
                    aux->valor = chave;
                    printf("Elemento trocado: %d !\n", chave);
                    raiz->esquerdo = remover(raiz->esquerdo, chave);
                    return raiz;
                }
                else{
                    // remover nós que possuem apenas 1 filho
                    No *aux;
                    if(raiz->esquerdo != NULL)
                        aux = raiz->esquerdo;
                    else
                        aux = raiz->direito;
                    free(raiz);
                    printf("Elemento com 1 filho removido: %d !\n", chave);
                    return aux;
                }
            }
        } else {
            if(chave < raiz->valor)
                raiz->esquerdo = remover(raiz->esquerdo, chave);
            else
                raiz->direito = remover(raiz->direito, chave);
        }

        // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
        raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;

        // verifica a necessidade de rebalancear a árvore
        raiz = balancear(raiz);

        return raiz;
    }
}

void imprimir(No *raiz, int espaco) {
    if (raiz == NULL) return;

    // Aumenta o espaço entre os níveis
    espaco += 5;

    // Imprime o filho direito primeiro
    imprimir(raiz->direito, espaco);

    // Imprime o nó atual no mesmo nível
    printf("\n");
    for (int i = 5; i < espaco; i++)
        printf(" ");
    printf("%d\n", raiz->valor);

    // Imprime o filho esquerdo
    imprimir(raiz->esquerdo, espaco);
}


// Função para percorrer a árvore em ordem
void percursoInOrder(No *raiz) {
    if (raiz) {
        percursoInOrder(raiz->esquerdo);
        printf("%d ", raiz->valor);
        percursoInOrder(raiz->direito);
    }
}

// Função para percorrer a árvore em pré-ordem
void percursoPreOrder(No *raiz) {
    if (raiz) {
        printf("%d ", raiz->valor);
        percursoPreOrder(raiz->esquerdo);
        percursoPreOrder(raiz->direito);
    }
}

// Função para percorrer a árvore em pós-ordem
void percursoPostOrder(No *raiz) {
    if (raiz) {
        percursoPostOrder(raiz->esquerdo);
        percursoPostOrder(raiz->direito);
        printf("%d ", raiz->valor);
    }
}

// Função para imprimir fatores de balanceamento
void imprimirFatoresDeBalanceamento(No *raiz) {
    if (raiz) {
        imprimirFatoresDeBalanceamento(raiz->esquerdo);
        printf("Nó: %d, Fator de Balanceamento: %d\n", raiz->valor, fatorDeBalanceamento(raiz));
        imprimirFatoresDeBalanceamento(raiz->direito);
    }
}

int main() {
    No *raiz = NULL;

    printf("Inserindo valores iniciais...\n");
    int valoresIniciais[] = {50, 57, 45, 25, 44, 27, 12, 55, 80, 95};
    for (int i = 0; i < 10; i++) {
        printf("Inserido: %d\n", valoresIniciais[i]);
        raiz = inserir(raiz, valoresIniciais[i]);
        imprimir(raiz, 1);
    }

    printf("\nInserindo valores adicionais...\n");
    int valoresAdicionais[] = {14, 23, 8};
    for (int i = 0; i < 3; i++) {
        printf("Inserido: %d\n", valoresAdicionais[i]);
        raiz = inserir(raiz, valoresAdicionais[i]);
        imprimir(raiz, 1);
    }

    printf("\nRemovendo valores...\n");
    int valoresParaRemover[] = {4, 44, 55};
    for (int i = 0; i < 3; i++) {
        printf("Removido: %d\n", valoresParaRemover[i]);
        raiz = remover(raiz, valoresParaRemover[i]);
        imprimir(raiz, 1);
    }

    printf("\nRealizando buscas...\n");
    int valoresParaBuscar[] = {14, 12};
    for (int i = 0; i < 2; i++) {
        printf("Buscando: %d\n", valoresParaBuscar[i]);
        No *busca = raiz;
        while (busca && busca->valor != valoresParaBuscar[i]) {
            if (valoresParaBuscar[i] < busca->valor)
                busca = busca->esquerdo;
            else
                busca = busca->direito;
        }
        if (busca)
            printf("Valor encontrado: %d\n", busca->valor);
        else
            printf("Valor não encontrado: %d\n", valoresParaBuscar[i]);
    }

    printf("\nPercursos da árvore:\n");
    printf("In-Order: ");
    percursoInOrder(raiz);
    printf("\nPre-Order: ");
    percursoPreOrder(raiz);
    printf("\nPost-Order: ");
    percursoPostOrder(raiz);
    printf("\n");

    printf("\nFatores de balanceamento:\n");
    imprimirFatoresDeBalanceamento(raiz);

    return 0;
}
