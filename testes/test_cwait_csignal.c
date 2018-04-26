#include "../include/support.h"
#include "../include/cthread.h"
#include <stdio.h>

csem_t semaforo_1, semaforo_2;
int tidThread0 = 0;
int tidThread1 = 0;
int tidThread2 = 0;
int tidThread3 = 0;
int tidThread4 = 0;

void* funcTest0(void *i) {
  printf("8 - func0: Entrei na thread id0!\n");
  printf("9 - func0: Vou dar cwait no semaforo 1. Logo, devo continuar a minha execucao...\n");
  cwait(&semaforo_1);
  printf("10 - func0: Vou dar cyield. Logo, a thread id1 deve assumir...\n");
  cyield();
  printf("21 - func0: Voltei!\n");
  printf("22 - func0: Vou dar csignal no semaforo 1. Logo, devo liberar o recurso para o proximo...\n");
  csignal(&semaforo_1);
  printf("23 - func0: Vou acabar!\n");

  return 0;
}

void* funcTest1(void *i) {
  printf("11 - func1: Entrei na thread id1!\n");
  printf("12 - func1: Vou dar cwait no semaforo 1. Logo, devo ir para o estado bloqueado...\n");
  cwait(&semaforo_1);
  printf("28 - func1: Voltei!\n");
  printf("29 - func1: Vou acabar!\n");
  return 0;
}

void* funcTest2(void *i) {
  printf("13 - func2: Entrei na thread id2!\n");
  printf("14 - func2: Vou dar cwait no semaforo 2. Logo, devo continuar minha execucao...\n");
  cwait(&semaforo_2);
  printf("15 - func2: Vou dar cwait no semaforo 2 novamente. Devo continuar minha execucao...\n");
  cwait(&semaforo_2);
  printf("16 - func2: Vou dar cyield. Logo, a thread id3 deve assumir...\n");
  cyield();
  printf("24 - func2: Voltei!\n");
  printf("25 - func2: Vou dar csignal no semaforo 2. Logo, devo liberar recursos para o proximo...\n");
  csignal(&semaforo_2);
  printf("26 - func2: Vou dar csinal novamente. Logo, devo liberar mais um recurso...\n");
  csignal(&semaforo_2);
  printf("27 - func2: Vou acabar!\n");

  return 0;
}

void* funcTest3(void *i) {
  printf("17 - func3: Entrei na thread id3!\n");
  printf("18 - func3: Vou dar cwait no semaforo 2. Logo, devo ir para o estado bloqueado...\n");
  cwait(&semaforo_2);
  printf("28 - func3: Voltei!\n");
  printf("29 - func3: Vou acabar!\n");

  return 0;
}

void* funcTest4(void *i) {
  printf("19 - func4: Entrei na thread id4!\n");
  printf("20 - func4: Vou dar cwait no semaforo 2. Logo, devo ir para o estado bloqueado...\n");
  cwait(&semaforo_2);
  printf("30 - func4: Voltei!\n");
  printf("31 - func4: Vou acabar!\n");

  return 0;
}

int main(int argc, char **argv) {
  int recursos_1 = 1, recursos_2 = 2;
  int id0 = 0, id1 = 0, id2 = 0, id3 = 0, id4 = 0;
  id4++;

  printf("1 - Inicializando semaforo 1...\n");
  if(csem_init(&semaforo_1, recursos_1) == 0) {
    printf("2 - Semaforo 1 inicializado corretamente como esperado...\n");
    printf("3 - Semaforo 1 possui 1 de recursos...\n");
  }

  printf("4 - Inicializando semaforo 2...\n");
  if(csem_init(&semaforo_2, recursos_2) == 0) {
    printf("5 - Semaforo 2 inicializado corretamente como esperado...\n");
    printf("6 - Semaforo 2 possui 2 de recursos...\n");
  }

  id0 = ccreate(funcTest0, NULL, 0);
  tidThread0 = id0;
  id1 = ccreate(funcTest1, NULL, 0);
  tidThread1 = id1;
  id2 = ccreate(funcTest2, NULL, 0);
  tidThread2 = id2;
  id3 = ccreate(funcTest3, NULL, 0);
  tidThread3 = id3;
  id4 = ccreate(funcTest4, NULL, 0);

  printf("7 - As 5 threads foram iniciadas!\n");
  cjoin(id0);


  return 0;
}
