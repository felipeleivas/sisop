/*
 *	Test Program - cyield
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/cthread.h"

int id1,id2;

csem_t sem;

void* func1(void *arg) {
  printf("2 Entering in the first thread and locking itself\n");
  cwait(&sem);
  cyield();
  printf("RETURNED TO FUNC1 PREVIOUSLY BLOCKED\n");

	return 0;
}

void* func2(void *arg) {
  printf("3 Second thread suspending id1\n");
  csuspend(id1);
  cyield();
  printf("5 Second thread normal pq resumir func1 nao deveria mudar nada no wait\n");
	return 0;
}

int main(int argc, char *argv[]) {

  csem_init(&sem, 0);
	printf("TEST INITIATED\n");

  id1 = ccreate(func1, NULL, 0);
  id2 = ccreate(func2, NULL, 0);

  printf("1 Main dando cyield\n");
	cyield();

  printf("4 Main resumindo id1 e id2  edando cyield\n");
  cresume(id1);
  cresume(id2);
	cyield();


	return 0;
}
