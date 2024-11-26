#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

int max(int a, int b) {
    return (a > b) ? a : b;
}

int altura(Node* no) {
    if (no == NULL) return 0;
    return no->altura;
}

int fator_balanceamento(Node* no) {
    if (no == NULL) return 0;
    return altura(no->left) - altura(no->rigth);
}

Node* rot_direita(Node* y) {
    Node* x = y->left;
    Node* T2 = x->rigth;

    x->rigth = y;
    y->left = T2;

    y->altura = max(altura(y->left), altura(y->rigth)) + 1;
    x->altura = max(altura(x->left), altura(x->rigth)) + 1;

    return x;
}

Node* rot_esquerda(Node* x) {
    Node* y = x->rigth;
    Node* T2 = y->left;

    y->left = x;
    x->rigth = T2;

    x->altura = max(altura(x->left), altura(x->rigth)) + 1;
    y->altura = max(altura(y->left), altura(y->rigth)) + 1;

    return y;
}

Node* add(Node* raiz, int val) {
    if (raiz == NULL) {
        Node* novo_no = (Node*)malloc(sizeof(Node));
        novo_no->val = val;
        novo_no->left = NULL;
        novo_no->rigth = NULL;
        novo_no->altura = 1;
        return novo_no;
    }

    if (val < raiz->val) {
        raiz->left = add(raiz->left, val);
    } else if (val > raiz->val) {
        raiz->rigth = add(raiz->rigth, val);
    } else {
        return raiz;
    }

    raiz->altura = max(altura(raiz->left), altura(raiz->rigth)) + 1;

    int balanceamento = fator_balanceamento(raiz);

    if (balanceamento > 1 && val < raiz->left->val) {
        return rot_direita(raiz);
    }

    if (balanceamento < -1 && val > raiz->rigth->val) {
        return rot_esquerda(raiz);
    }

    if (balanceamento > 1 && val > raiz->left->val) {
        raiz->left = rot_esquerda(raiz->left);
        return rot_direita(raiz);
    }

    if (balanceamento < -1 && val < raiz->rigth->val) {
        raiz->rigth = rot_direita(raiz->rigth);
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

    return search(raiz->rigth, val);
}

Node* del(Node* raiz, int val) {
    if (raiz == NULL) return raiz;

    if (val < raiz->val) {
        raiz->left = del(raiz->left, val);
    } else if (val > raiz->val) {
        raiz->rigth = del(raiz->rigth, val);
    } else {
        if (raiz->left == NULL || raiz->rigth == NULL) {
            Node* temp = raiz->left ? raiz->left : raiz->rigth;

            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }

            free(temp);
        } else {
            Node* temp = raiz->rigth;
            while (temp && temp->left != NULL) {
                temp = temp->left;
            }

            raiz->val = temp->val;
            raiz->rigth = del(raiz->rigth, temp->val);
        }
    }

    if (raiz == NULL) return raiz;

    raiz->altura = max(altura(raiz->left), altura(raiz->rigth)) + 1;

    int balanceamento = fator_balanceamento(raiz);

    if (balanceamento > 1 && fator_balanceamento(raiz->left) >= 0) {
        return rot_direita(raiz);
    }

    if (balanceamento < -1 && fator_balanceamento(raiz->rigth) <= 0) {
        return rot_esquerda(raiz);
    }

    if (balanceamento > 1 && fator_balanceamento(raiz->left) < 0) {
        raiz->left = rot_esquerda(raiz->left);
        return rot_direita(raiz);
    }

    if (balanceamento < -1 && fator_balanceamento(raiz->rigth) > 0) {
        raiz->rigth = rot_direita(raiz->rigth);
        return rot_esquerda(raiz);
    }

    return raiz;
}

void pre_ord(Node* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->val);
        pre_ord(raiz->left);
        pre_ord(raiz->rigth);
    }
}

void pos_ord(Node* raiz) {
    if (raiz != NULL) {
        pos_ord(raiz->left);
        pos_ord(raiz->rigth);
        printf("%d ", raiz->val);
    }
}

void em_ord(Node* raiz) {
    if (raiz != NULL) {
        em_ord(raiz->left);
        printf("%d ", raiz->val);
        em_ord(raiz->rigth);
    }
}
