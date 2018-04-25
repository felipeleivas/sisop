#include "../include/support.h"
#include "../include/cthread.h"
#include <stdio.h>


void* parOuImpar(void *i) {
     printf("      Entrei na thread...\n");
     int numero;
     numero = *(int *)i;

     if(numero % 2 == 0) {
       printf("      O numero %d eh par.\n", numero);
     } else {
       printf("      O numero %d eh impar.\n", numero);
     }
     printf("      Acabei a thread...\n");
     return 0;
}

int main(int argc, char **argv) {
	int id0, id1;
	int par = 2, impar = 1;

  printf("1 - Criando thread id0...\n");
	id0 = ccreate(parOuImpar, (void *)&par, 0);
  if(id0 >= 0) {
    printf("    Thread id0 criada com sucesso como esperado!\n");
  } else {
    printf("    Erro ao criar thread id0, problema na funcao ccreate!\n");
  }

  printf("2 - Criando thread id1 com argumentos...\n");
	id1 = ccreate(parOuImpar, (void *)&impar, 0);
  if(id1 >= 0) {
    printf("    Thread id1 criada com sucesso como esperado!\n");
  } else {
    printf("    Erro ao criar thread id1, problema na funcao ccreate!\n");
  }
  printf("Threads Par ou Impar criadas...\n");

  printf("3 - Realizando cjoin da thread id0...\n");
	if(cjoin(id0) == 0) {
    printf("    cjoin executado corretamente!\n");
  } else {
    printf("    Erro na funcao cjoin!\n");
  }
  printf("4 - Realizando cjoin da thread id1 que já executou, logo, deve retornar erro...\n");
	if(cjoin(id1) != 0) {
    printf("    cjoin retornou erro corretamente!\n");
  } else {
    printf("    Erro na funcao cjoin!\n");
  }

	printf("Main retornando para terminar o programa\n");
}
