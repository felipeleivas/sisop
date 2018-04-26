/*
 *	Test Program - cjoin
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/cthread.h"

void* func0(void *arg) {
	printf("[04] Entering in the first thread\n");
	if (*(int *)arg == 5) {
		printf("[05] First Test SUCCEEDED\n");
	} else {
		printf("[??] First Test FAILED\n");
	}
	return 0;
}

void* func1(void *arg) {
  printf("[06] Entering in the second thread\n");

	if (*(int *)arg == 5) {
		printf("[07] Second Test SUCCEEDED\n");
	} else {
		printf("[??] Second Test FAILED\n");
	}
	return 0;
}

int main(int argc, char *argv[]) {

	int	id0, id1;
	int i = 5;

	printf("[01] TEST INITIATED\n");

	printf("[02] Creating both threads\n");

	id0 = ccreate(func0, (void *)&i, 0);

	id1 = ccreate(func1, (void *)&i, 0);

	printf("[03] Main after creating both threads\n");

	cjoin(id0);

	i = 2;

	cjoin(id1);

  printf("[08] TEST COMPLETED\n");

	return 0;
}
