#include "../include/support.h"
#include "../include/cthread.h"
#include <stdio.h>

csem_t semaforo_1, semaforo_2;

void* funcTest0(void *i) {
  int delay = 1000000000;

  printf("5 - func0: Entrei na thread id0!\n");
  printf("6 - func0: Vou dar cwait no semaforo 1. Logo, devo continuar minha execucao normalmente...\n");
  cwait(&semaforo_1);
  printf("7 - func0: Vou dormir por um tempo...\n");
  while(delay > 0)
    delay--;
  printf("8 - func0: Vou dar cyield. Logo, a thread id1 deve assumir...\n");
  cyield();
  printf("11 - func0: Voltei!\n");
  printf("12 - func0: Vou dar csignal no semaforo 1. Logo, devo liberar o recurso para o proximo na fila...\n");
  csignal(&semaforo_1);
  printf("13 - func0: Vou acabar!\n");

  return 0;
}

void* funcTest1(void *i) {
  printf("9 - func1: Entrei na thread id1!\n");
  printf("10 - func1: Vou dar cwait no semaforo 1. Logo, devo ir para o bloqueado...\n");
  cwait(&semaforo_1);
  printf("14 - func1: Voltei!\n");
  printf("15 - func1: Vou dar csignal no semaforo 1. Logo, devo liberar o recurso, e nao deve ter ninguem na fila...\n");
  csignal(&semaforo_1);
  printf("16 - func1: Vou acabar!\n");
  return 0;
}

int main(int argc, char **argv) {
  int recursos_1 = 1, id0 = 0, id1 = 0;
  id1++;

  printf("1 - Inicializando semaforo 1...\n");
  if(csem_init(&semaforo_1, recursos_1) == 0) {
    printf("2 - Semaforo 1 inicializado corretamente como esperado...\n");
    printf("3 - Semaforo 1 possui 1 de recursos...\n");
  }

  id0 = ccreate(funcTest0, NULL, 0);
  id1 = ccreate(funcTest1, NULL, 0);

  printf("4 - As 4 threads foram iniciadas!\n");
  cjoin(id0);

  printf("Main retornando para terminar o programa\n");
  return 0;
}
