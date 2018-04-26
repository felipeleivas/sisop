#include "../include/support.h"
#include "../include/cthread.h"
#include <stdio.h>

int tidThread0 = 0;
int tidThread1 = 0;
int tidThread2 = 0;
int tidThread3 = 0;
int tidThread4 = 0;

void* funcTest0(void *i) {
  printf("1 - func0: Entrei na thread id0...\n");
  printf("2 - func0: Vou dar cjoin na thread id2. Logo, vou ir para o estado bloqueado.\n");
  cjoin(tidThread2);
  printf("19 - func0: Voltei!\n");
  printf("20 - func0: Vou acabar...\n");
  return 0;
}

void* funcTest1(void *i) {
  printf("3 - func1: Entrei na thread id1...\n");
  printf("4 - func1: Vou dar cjoin na thread id4. Logo, vou ir para o estado bloqueado.\n");
  cjoin(tidThread4);
  printf("17 - func1: Voltei!\n");
  printf("18 - func1: Vou acabar...\n");

  return 0;
}

void* funcTest2(void *i) {
  int delay = 1000000000;

  printf("5 - func2: Entrei na thread id2...\n");
  printf("6 - func2: Vou dormir por um tempo...\n");
  while(delay > 0)
    delay--;
  printf("7 - func2: Acordei!\n");
  printf("8 - func2: Vou dar csuspend na thread id1, com tid = %d, que deve ir para o estado bloqueado-suspenso.\n", tidThread1);
  csuspend(tidThread1);
  printf("9 - func2: Vou dar cyield. Logo, a thread id3 deve assumir...\n");
  cyield();
  printf("15 - func2: Voltei!\n");
  printf("16 - func2: Vou acabar...\n");

  return 0;
}

void* funcTest3(void *i) {
  printf("10 - func3: Entrei na thread id3...\n");
  printf("11 - func3: Vou dar cjoin na thread id1, que esta no estado bloqueado-suspenso. Logo, devo ir para o estado bloqueado...\n");
  cjoin(tidThread1);
  printf("21 - func3: Voltei!\n");
  printf("22 - func3: Vou acabar...\n");
  return 0;
}

void* funcTest4(void *i) {
  printf("12 - func4: Entrei na thread id4...\n");
  printf("13 - func4: Vou dar cresume na thread id1, com tid = %d, que deve ir para o estado bloqueado...\n", tidThread1);
  cresume(tidThread1);
  printf("14 - func4: Vou acabar...\n");
  return 0;
}

int main(int argc, char **argv) {
	int id0 = 0, id1 = 0, id2 = 0, id3 = 0, id4 = 0;


	id0 = ccreate(funcTest0, NULL, 0);
  tidThread0 = id0;

  id1 = ccreate(funcTest1, NULL, 0);
  tidThread1 = id1;

  id2 = ccreate(funcTest2, NULL, 0);
  tidThread2 = id2;

  id3 = ccreate(funcTest3, NULL, 0);
  tidThread3 = id3;

  id4 = ccreate(funcTest4, NULL, 0);
  tidThread4 = id4;

  cjoin(id0);

  printf("Main retornando para terminar o programa\n");
  return 0;
}
