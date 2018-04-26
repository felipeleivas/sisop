/*
 *	Test Program - ccreate
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/cthread.h"

void* func0(void *arg) {
	printf("[03] Entering in the thread\n");
	if (*(int *)arg == 5) {
		printf("[04] First Test SUCCEEDED\n");
	} else {
		printf("[??] First Test FAILED\n");
	}
	return 0;
}

int main(int argc, char *argv[]) {

	int	id0;
	int i = 5;

	printf("[01] TEST INITIATED\n");

	id0 = ccreate(func0, (void *)&i, 0);

	printf("[02] Main after creating thread\n");

	cjoin(id0);

	printf("[05] TEST COMPLETED\n");

	return 0;
}
