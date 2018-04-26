#include "../include/support.h"
#include "../include/cthread.h"
#include <stdio.h>

int tidThread0 = 0;
int tidThread1 = 0;
int tidThread2 = 0;

void* funcTest0(void *i) {
  printf("1 - func0: Entrei na thread id0...\n");
  printf("2 - func0: Vou dar cjoin na thread id2. Logo, vou ir para o estado bloqueado.\n");
  cjoin(tidThread2);
  printf("10 - func0: Voltei!\n");
  printf("11 - func0: Vou acabar. Não existem outras thread. Logo, deve voltar para a main.\n");
  return 0;
}

void* funcTest1(void *i) {
  printf("3 - func1: Entrei na thread id1...\n");
  printf("4 - func1: Vou suspender a thread id0, com tid = %d, que esta no estado bloqueado.\n", tidThread0);
  printf("5 - func1: Logo, a thread id0 deve ir para o estado bloqueado-suspenso.\n");
  csuspend(tidThread0);
  printf("6 - func1: Vou acabar.\n");
  return 0;
}

void* funcTest2(void *i) {
  printf("7 - func2: Entrei na thread id2...\n");
  printf("8 - func2: Vou resumir a thread id0, com tid = %d, que deve retornar para o estado bloqueado.\n", tidThread0);
  cresume(tidThread0);
  printf("9 - func2: Vou acabar. Logo, a thread id0 deve voltar...\n");
  return 0;
}

int main(int argc, char **argv) {
	int id0 = 0, id1 = 0, id2 = 0;
  id2++;

	id0 = ccreate(funcTest0, NULL, 0);
  tidThread0 = id0;

  id1 = ccreate(funcTest1, NULL, 0);
  tidThread1 = id1;

  id2 = ccreate(funcTest2, NULL, 0);
  tidThread2 = id2;

  cjoin(id0);

  printf("Main retornando para terminar o programa\n");
  return 0;

}
