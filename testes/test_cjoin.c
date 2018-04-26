#include "../include/support.h"
#include "../include/cthread.h"
#include <stdio.h>


void* parOuImpar(void *i) {
     int numero;
     numero = *(int *)i;

     if(numero % 2 == 0) {
       printf("      O numero %d eh par.\n", numero);
     } else {
       printf("      O numero %d eh impar.\n", numero);
     }
     return 0;
}

int main(int argc, char **argv) {
	int id0, id1 = 123;
	int par = 2;

	id0 = ccreate(parOuImpar, (void *)&par, 0);

  printf("Threads Par ou Impar criadas...\n");
  printf("1 - Realizando cjoin da thread id0...\n");
	if(cjoin(id0) == 0) {
    printf("    cjoin executado corretamente!\n");
  } else {
    printf("    Erro na funcao cjoin!\n");
  }

  printf("2 - Realizando cjoin para a mesma thread, logo, deve resultar em erro...\n");
	if(cjoin(id0) != 0) {
    printf("    cjoin retornou erro como esperado!\n");
  } else {
    printf("    Erro na funcao cjoin!\n");
  }

  printf("3 - Realizando cjoin para uma thread inexistente, logo, deve resultar em erro...\n");
  if(cjoin(id1) != 0) {
    printf("    cjoin retornou erro como esperado!\n");
  } else {
    printf("    Erro na funcao cjoin!\n");
  }

	printf("Main retornando para terminar o programa\n");
}
