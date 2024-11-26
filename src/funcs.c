#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

int max(int a, int b) {
    return (a > b) ? a : b;
}

int altura(Node* node) {
    if (node == NULL) return 0;
    return node->height;
}

int fator_balanceamento(Node* node) {
    if (node == NULL) return 0;
    return altura(node->left) - altura(node->right);
}

Node* rot_direita(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(altura(y->left), altura(y->right)) + 1;
    x->height = max(altura(x->left), altura(x->right)) + 1;

    return x;
}

Node* rot_esquerda(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(altura(x->left), altura(x->right)) + 1;
    y->height = max(altura(y->left), altura(y->right)) + 1;

    return y;
}

Node* add(Node* raiz, int val) {
    if (raiz == NULL) {
        Node* novo_no = (Node*)malloc(sizeof(Node));
        novo_no->val = val;
        novo_no->left = NULL;
        novo_no->right = NULL;
        novo_no->height = 1;
        return novo_no;
    }

    if (val < raiz->val) {
        raiz->left = add(raiz->left, val);
    } else if (val > raiz->val) {
        raiz->right = add(raiz->right, val);
    } else {
        return raiz;
    }

    raiz->height = max(altura(raiz->left), altura(raiz->right)) + 1;

    int balanceamento = fator_balanceamento(raiz);

    if (balanceamento > 1 && val < raiz->left->val) {
        return rot_direita(raiz);
    }

    if (balanceamento < -1 && val > raiz->right->val) {
        return rot_esquerda(raiz);
    }

    if (balanceamento > 1 && val > raiz->left->val) {
        raiz->left = rot_esquerda(raiz->left);
        return rot_direita(raiz);
    }

    if (balanceamento < -1 && val < raiz->right->val) {
        raiz->right = rot_direita(raiz->right);
        return rot_esquerda(raiz);
    }

    return raiz;
}

Node* search(Node* raiz, int val) {
    if (raiz == NULL || raiz->val == val) {
        return raiz;
    }

    if (val < raiz->val) {
        return search(raiz->left, val);
    }

    return search(raiz->right, val);
}

Node* del(Node* raiz, int val) {
    if (raiz == NULL) return raiz;

    if (val < raiz->val) {
        raiz->left = del(raiz->left, val);
    } else if (val > raiz->val) {
        raiz->right = del(raiz->right, val);
    } else {
        if (raiz->left == NULL || raiz->right == NULL) {
            Node* temp = raiz->left ? raiz->left : raiz->right;

            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }

            free(temp);
        } else {
            Node* temp = raiz->right;
            while (temp && temp->left != NULL) {
                temp = temp->left;
            }

            raiz->val = temp->val;
            raiz->right = del(raiz->right, temp->val);
        }
    }

    if (raiz == NULL) return raiz;

    raiz->height = max(altura(raiz->left), altura(raiz->right)) + 1;

    int balanceamento = fator_balanceamento(raiz);

    if (balanceamento > 1 && fator_balanceamento(raiz->left) >= 0) {
        return rot_direita(raiz);
    }

    if (balanceamento < -1 && fator_balanceamento(raiz->right) <= 0) {
        return rot_esquerda(raiz);
    }

    if (balanceamento > 1 && fator_balanceamento(raiz->left) < 0) {
        raiz->left = rot_esquerda(raiz->left);
        return rot_direita(raiz);
    }

    if (balanceamento < -1 && fator_balanceamento(raiz->right) > 0) {
        raiz->right = rot_direita(raiz->right);
        return rot_esquerda(raiz);
    }

    return raiz;
}

void pre_ord(Node* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->val);
        pre_ord(raiz->left);
        pre_ord(raiz->right);
    }
}

void pos_ord(Node* raiz) {
    if (raiz != NULL) {
        pos_ord(raiz->left);
        pos_ord(raiz->right);
        printf("%d ", raiz->val);
    }
}

void em_ord(Node* raiz) {
    if (raiz != NULL) {
        em_ord(raiz->left);
        printf("%d ", raiz->val);
        em_ord(raiz->right);
    }
}
