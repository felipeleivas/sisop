/*
 *	Test Program - cyield
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/cthread.h"

int id;

csem_t sem;

void* func1(void *arg) {
  printf("Entering in the first thread\n");

  cyield();

	return 0;
}

void* func2(void *arg) {
  printf("Entering in the second thread\n");
  printf("Second thread suspending first thread\n");
  csuspend(id);
  printf("Second thread blocking itself\n");
  cwait(&sem);


	return 0;
}

int main(int argc, char *argv[]) {

  csem_init(&sem, 0);
	printf("TEST INITIATED\n");

	printf("Main CYIELD\n");

	cyield();

	printf("Main after being only thread on system and have cyielded correctly\n");


  ccreate(func2, NULL, 0);
  id = ccreate(func1, NULL, 0);

  printf("Ending main, func2 should be executed next\n");

	return 0;
}
