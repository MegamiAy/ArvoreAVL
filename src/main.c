#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

int main(){
	int op, num;
	
	printf("Digite a opercao que deseja: \n");
	printf("1. Incluir\n");
	printf("2. Pesquisar\n");
	printf("3. Excluir\n");
	printf("4. Sair\n");
	scanf("%i", &op);
	
	switch(op){
		case 1:
			add();
			break;
		case 2:
      printf("Digite um numero que deseja encontrar: \n");
      scanf("%i", &num);
			search(num);
			break;
		case 3:
      printf("Digite um numero que deseja deletar: \n");
      scanf("%i", &num);
			del(num);
			break;
		case 4:
			printf("Tchau!");
			break;
		default:
			break;
	}
}
