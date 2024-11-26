#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

int main() {
    int op, num;
    Node* raiz = NULL;

    do {
        printf("Digite a operacao que deseja: \n");
        printf("1. Incluir\n");
        printf("2. Pesquisar\n");
        printf("3. Excluir\n");
        printf("4. Exibir ordens\n");
        printf("5. Sair\n");
        scanf("%i", &op);

        switch (op) {
            case 1:
                printf("Digite o número a ser incluído: ");
                scanf("%i", &num);
                raiz = add(raiz, num);
                break;
            case 2:
                printf("Digite o número que deseja encontrar: ");
                scanf("%i", &num);
                Node* encontrado = search(raiz, num);
                if (encontrado != NULL) {
                    printf("Número encontrado: %d\n", encontrado->val);
                } else {
                    printf("Número não encontrado.\n");
                }
                break;
            case 3:
                printf("Digite o número a ser deletado: ");
                scanf("%i", &num);
                raiz = del(raiz, num);
                break;
            case 4:
                printf("Pré-ordem: ");
                pre_ord(raiz);
                printf("\n");
                printf("Pós-ordem: ");
                pos_ord(raiz);
                printf("\n");
                printf("Ordem: ");
                em_ord(raiz);
                printf("\n");
                break;
            case 5:
                printf("Tchau!\n");
                break;
            default:
                printf("Opção inválida.\n");
                break;
        }
    } while (op != 5);

    return 0;
}
