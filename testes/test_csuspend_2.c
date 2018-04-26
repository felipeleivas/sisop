/*
 *	Test Program - csuspend
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/cthread.h"

void* func0(void *arg) {
  printf("Entering First thread\n");

	if (*(int *)arg == 5) {
		printf("Thread Creation Test SUCCEEDED\n");
	} else {
		printf("Thread Creation Test FAILED\n");
    }

	cyield();


	printf("First Thread ended - Shouldn't happen\n");

	return 0;
}

void* func1(void *arg) {
  	printf("Entering Second thread\n");

	printf("Suspending First thread\n");
	csuspend(*(int *)arg);

	printf("Second Thread ended\n");

	return 0;
}

int main(int argc, char *argv[]) {

	int	id0, id1;
    int i = 5;

	printf("TEST INITIATED\n");

	printf("Creating threads\n");

	id0 = ccreate(func0, (void *)&i, 0);
	id1 = ccreate(func1, (void *)&id0, 0);

	printf("Main after creating threads\n");

	cjoin(id1);

	printf("YIELDING MAIN THREAD\n");
	cyield();
	printf("IF IT HASN'T RETURNED TO THE FIRST THREAD IT HAS SUCCEEDED\n");


	printf("TEST COMPLETED\n");

	return 0;
}
