/*
 *	Test Program - cjoin-critical2
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/cthread.h"

int id0, id1, id2, id3;

void* func1(void *arg) {
  printf("[07] Entering in the second thread\n");

	if (*(int *) arg == 10) {
		printf("[08] SECOND TEST SUCCEEDED\n");
	} else {
		printf("[??] SECOND TEST FAILED\n");
	}

	return 0;
}

void* func0(void *arg) {
	printf("[04] Entering in the first thread\n");
	int i2 = 10;
	id1 = ccreate(func1, (void *)&i2, 0);

	if(csuspend(id1) != 0) {
		printf("[??] SUSPENDING SECOND THREAD\n");
	}

	printf("[05] CYIELDING without any thread in apt\n");

	cyield();

	if (cresume(id1) == 0)
		printf("[06] RESUMING SECOND THREAD\n");

	cyield();

	printf("[09] BACKING TO FIRST THREAD\n");

	if (*(int *) arg == 5) {
		printf("[10] FIRST TEST SUCCEEDED\n");
	} else {
		printf("[??] FIRST TEST FAILED\n");
	}
	return 0;
}


int main(int argc, char *argv[]) {

	int i = 5;

	printf("[01] TEST INITIATED\n");

	printf("[02] Creating both threads\n");

	id0 = ccreate(func0, (void *)&i, 0);

	printf("[03] MAIN AFTER CREATING THE THREAD\n");

	cjoin(id0);

	printf("[11] MAIN AFTER CYIELD\n");


  printf("[12] TEST COMPLETED\n");

	return 0;
}
