#include <stdio.h>
#include <stdlib.h>

/*
    ESTRUTURA DO NÓ
*/

// Estrutura do Nó
typedef struct No {
    int valor;
    struct No *esquerda;
    struct No *direita;
    int altura;  // Para calcular fatores de balanceamento
} No;

// Função para obter a altura de um nó
int altura(No *n) {
    return (n == NULL) ? 0 : n->altura;
}

// Função para calcular o fator de balanceamento
int fatorBalanceamento(No *n) {
    return (n == NULL) ? 0 : altura(n->esquerda) - altura(n->direita);
}

// Criação de um novo nó
No *novoNo(int valor) {
    No *no = (No *)malloc(sizeof(No));
    no->valor = valor;
    no->esquerda = NULL;
    no->direita = NULL;
    no->altura = 1; // Nó inicial tem altura 1
    return no;
}

/*
    ROTAÇÃO
*/

// Rotação simples para a direita
No *rotacaoDireita(No *y) {
    No *x = y->esquerda;
    No *T2 = x->direita;

    // Rotação
    x->direita = y;
    y->esquerda = T2;

    // Atualizar alturas
    y->altura = 1 + ((altura(y->esquerda) > altura(y->direita)) ? altura(y->esquerda) : altura(y->direita));
    x->altura = 1 + ((altura(x->esquerda) > altura(x->direita)) ? altura(x->esquerda) : altura(x->direita));

    return x; // Nova raiz
}

// Rotação simples para a esquerda
No *rotacaoEsquerda(No *x) {
    No *y = x->direita;
    No *T2 = y->esquerda;

    // Rotação
    y->esquerda = x;
    x->direita = T2;

    // Atualizar alturas
    x->altura = 1 + ((altura(x->esquerda) > altura(x->direita)) ? altura(x->esquerda) : altura(x->direita));
    y->altura = 1 + ((altura(y->esquerda) > altura(y->direita)) ? altura(y->esquerda) : altura(y->direita));

    return y; // Nova raiz
}

/*
    INSERÇÃO
*/

No *inserir(No *no, int valor) {
    // Inserção padrão em árvore binária de busca
    if (no == NULL)
        return novoNo(valor);

    if (valor < no->valor)
        no->esquerda = inserir(no->esquerda, valor);
    else if (valor > no->valor)
        no->direita = inserir(no->direita, valor);
    else
        return no; // Valores duplicados não são permitidos

    // Atualizar a altura do nó atual
    no->altura = 1 + ((altura(no->esquerda) > altura(no->direita)) ? altura(no->esquerda) : altura(no->direita));

    // Calcular o fator de balanceamento
    int balance = fatorBalanceamento(no);

    // Verificar desbalanceamento e corrigir
    // Rotação à direita (Caso Esquerda-Esquerda)
    if (balance > 1 && valor < no->esquerda->valor)
        return rotacaoDireita(no);

    // Rotação à esquerda (Caso Direita-Direita)
    if (balance < -1 && valor > no->direita->valor)
        return rotacaoEsquerda(no);

    // Rotação dupla à esquerda (Caso Esquerda-Direita)
    if (balance > 1 && valor > no->esquerda->valor) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    // Rotação dupla à direita (Caso Direita-Esquerda)
    if (balance < -1 && valor < no->direita->valor) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no; // Retornar o nó (sem mudanças)
}

/*
    PERCURSOS
*/

void inOrder(No *raiz) {
    if (raiz != NULL) {
        inOrder(raiz->esquerda);
        printf("%d ", raiz->valor);
        inOrder(raiz->direita);
    }
}

void preOrder(No *raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->valor);
        preOrder(raiz->esquerda);
        preOrder(raiz->direita);
    }
}

void postOrder(No *raiz) {
    if (raiz != NULL) {
        postOrder(raiz->esquerda);
        postOrder(raiz->direita);
        printf("%d ", raiz->valor);
    }
}

/*
    IMPRIMIR ÁRVORE
*/

void imprimirArvore(No *raiz, int espacos, char direcao) {
    if (raiz == NULL)
        return;

    // Ajustar o número de espaços para a indentação
    espacos += 5;

    // Chama recursivamente para o filho direito
    imprimirArvore(raiz->direita, espacos, '/');

    // Imprime o valor atual com a indentação
    printf("\n");
    for (int i = 5; i < espacos; i++) {
        printf(" ");
    }
    printf("%d ", raiz->valor);

    // Imprime a direção (indica se é filho esquerdo ou direito)
    if (direcao != ' ') {
        printf("%c", direcao);
    }

    // Chama recursivamente para o filho esquerdo
    imprimirArvore(raiz->esquerda, espacos, '\\');
}


/*
    MAIN
*/

int main() {
    No *raiz = NULL;

    // Inserção inicial
    int numeros[] = {50, 57, 45, 25, 44, 27, 12, 55, 80, 95};
    for (int i = 0; i < 10; i++) {
        raiz = inserir(raiz, numeros[i]);
    }

    // Exibir árvore em diferentes percursos
    printf("In-order: ");
    inOrder(raiz);
    printf("\n");
    imprimirArvore(raiz, 0, ' ');
    printf("\n\n");
    
    printf("Pre-order: ");
    preOrder(raiz);
    printf("\n");
    imprimirArvore(raiz, 0, ' ');
    printf("\n\n");
    
    printf("Post-order: ");
    postOrder(raiz);
    printf("\n");
    imprimirArvore(raiz, 0, ' ');
    
    return 0;
}
