#ifndef FUNCOES_H
#define FUNCOES_H

typedef struct node {
    int val;
    struct node* left;
    struct node* right;
    int height;
} Node;

Node* add(Node* raiz, int valor);
Node* search(Node* raiz, int valor);
Node* del(Node* raiz, int valor);
void pre_ord(Node* raiz);
void pos_ord(Node* raiz);
void em_ord(Node* raiz);
Node* rot_direita(Node* y);
Node* rot_esquerda(Node* x);
int max(int a, int b);
int altura(Node* node);
int fator_balanceamento(Node* node);

#endif
