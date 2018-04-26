/*
 *	Test Program - cyield
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/cthread.h"

void* func0(void *arg) {
	printf("Entering in the first thread\n");
	if (*(int *)arg == 5) {
		printf("First Test SUCCEEDED\n");
	} else {
		printf("First Test FAILED\n");
	}
	return 0;
}

void* func1(void *arg) {
  printf("Entering in the second thread\n");

	printf("Second thread before cyield to modify the number\n");

	cyield();

	printf("Second thread after cyield\n");

	if (*(int *)arg == 2) {
		printf("Second Test SUCCEEDED\n");
	} else {
		printf("Second Test FAILED\n");
	}
	return 0;
}

int main(int argc, char *argv[]) {

	int i = 5;

	printf("TEST INITIATED\n");

	printf("Creating both threads\n");

	ccreate(func0, (void *)&i, 0);

	ccreate(func1, (void *)&i, 0);

	printf("Main before first CYIELD\n");

	cyield();

	printf("Main after first CYIELD\n");

	i = 2;

	printf("Main before second CYIELD\n");

	cyield();

	printf("Main after second CYIELD\n");

  printf("TEST COMPLETED\n");

	return 0;
}
