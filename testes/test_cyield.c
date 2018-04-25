
//
// Programa de teste para primitivas de criação e sincronização
//
// Disclamer: este programa foi desenvolvido para auxiliar no desenvolvimento
//            de testes para o micronúcleo. NÃO HÁ garantias de estar correto.

#include "../include/support.h"
#include "../include/cthread.h"
#include <stdio.h>


void* contaDeDoisEmDois(void *i) {
  int n = *(int *)i;
  int j = 0, contador = 0;
  printf("func1: vou contar ate %d, mas vou castar cyield a cada 2 unidades...\n", n);
  for(j = 1; j <= n; j++) {
    if(contador == 2) {
      contador = 0;
      printf("func1: estou dando cyield...\n");
      if(cyield() == 0) {
        printf("func1: cyield executado corretamente...\n");
      } else {
        printf("func1: erro na cyield!\n");
      }
    }
    contador++;
    printf("func1: %d\n", j);
  }

  printf("func1: acabei!\n");
  return 0;
}

void* ContaDeTresEmTres(void *i) {
  int n = *(int *)i;
  int j = 0, contador = 0;
  printf("func2: vou contar ate %d, mas vou castar cyield a cada 3 unidades...\n", n);
  for(j = 1; j <= n; j++) {
    if(contador == 3) {
      contador = 0;
      printf("func2: estou dando cyield...\n");
      if(cyield() == 0) {
        printf("func2: cyield executado corretamente...\n");
      } else {
        printf("func2: erro na cyield!\n");
      }
    }
    contador++;
    printf("func2: %d\n", j);
  }

  printf("func2: acabei!\n");
  return 0;
}

int main(int argc, char **argv) {
	int id0, id1;
	int i = 10;

	id0 = ccreate(contaDeDoisEmDois, (void *)&i, 0);
	id1 = ccreate(ContaDeTresEmTres, (void *)&i, 0);

  printf("Threads criadas...\n");

	cjoin(id0);
	cjoin(id1);

	printf("Main retornando para terminar o programa\n");
}
