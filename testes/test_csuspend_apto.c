#include "../include/support.h"
#include "../include/cthread.h"
#include <stdio.h>

int tidThread1 = 0;

void* funcTest0(void *i) {
  printf("1 - func0: Entrei na thread id0...\n");
  printf("2 - func0: Vou suspender a thread id1 com tid = %d\n", tidThread1);
  csuspend(tidThread1);
  printf("3 - func0: Vou passar a vez para a proxima thread, que deve ser a id2...\n");
  cyield();
  printf("8 - func0: Voltei!\n");
  printf("9 - func0: Vou resumir a thread id1 com tid = %d\n", tidThread1);
  cresume(tidThread1);
  printf("10 - func0: Vou acabar. Logo, a thread id1 deve assumir...\n");
  return 0;
}

void* funcTest1(void *i) {
  printf("11 - func1: Entrei na thread id1, como esperado!\n");
  printf("12 - func1: Vou acabar.\n");
  return 0;
}

void* funcTest2(void *i) {
  int delay = 100000000;

  printf("4 - func2: Entrei na thread id2...\n");
  printf("5 - func2: Vou dormir por um tempo...\n");
  while(delay > 0)
    delay--;
  printf("6 - func2: Acordei!\n");
  printf("7 - func2: Vou acabar. Logo, a thread id0 deve voltar...\n");
  return 0;
}

int main(int argc, char **argv) {
	int id0 = 0, id1 = 0, id2 = 0;
  id2++;

	id0 = ccreate(funcTest0, NULL, 0);

  id1 = ccreate(funcTest1, NULL, 0);
  tidThread1 = id1;

  id2 = ccreate(funcTest2, NULL, 0);

  cjoin(id0);

  printf("Main retornando para terminar o programa\n");
  return 0;

}
