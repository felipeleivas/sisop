/*
 *	Test Program - cresume
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include "../include/cthread.h"

void* func0(void *arg) {
  printf("Entering in thread\n");

	if (*(int *)arg == 5) {
		printf("Thread Creation Test SUCCEEDED\n");
	} else {
		printf("Thread Creation Test FAILED\n");
    }

	printf("Finished Thread\n");

	return 0;
}

int main(int argc, char *argv[]) {

	int	id0;
    int i = 5;
    int result;

	printf("TEST INITIATED\n");

	printf("Creating threads\n");

	id0 = ccreate(func0, (void *)&i, 0);

	printf("Main after creating threads\n");

    csuspend(id0);
    printf("Thread Suspended\n");
    result = cresume(id0);
    cjoin(id0);

    if(result < 0){
        printf("TEST FAILED\n");
    } else {
        printf("TEST COMPLETED\n");
    }
	return 0;
}
