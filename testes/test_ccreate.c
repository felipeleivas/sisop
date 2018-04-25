#include "../include/support.h"
#include "../include/cthread.h"
#include <stdio.h>


void *parOuImpar(void *i) {
     int numero;
     numero = *(int *)i;

     if(numero % 2 == 0) {
       printf("O numero %d eh par.\n", numero);
     } else {
       printf("O numero %d eh impar.\n", numero);
     }
     return 0;
}

int main(int argc, char **argv) {
	int id0, id1;
	int par = 2;

  printf("1 - Criando thread id0 com argumentos...\n");
	id0 = ccreate(parOuImpar, (void *)&par, 0);
  if(id0 >= 0) {
    printf("      Thread id0 criada com sucesso como esperado!\n");
  } else {
    printf("      Erro ao criar thread id0, problema na funcao ccreate!\n");
  }

  printf("2 - Criando thread id1 sem argumentos...\n");
	id1 = ccreate(parOuImpar, NULL, 0);
  if(id1 >= 0) {
    printf("      Thread id1 criada com sucesso como esperado!\n");
  } else {
    printf("      Erro ao criar thread id1, problema na funcao ccreate!\n");
  }

	printf("Main retornando para terminar o programa\n");
}
