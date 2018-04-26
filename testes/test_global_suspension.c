/*
 *	Test Program - global suspension
 *
 *	Uma main com 1 thread e uma variavel global i
 *  Essa thread cria 2 threads e as suspende
 *  Resumeia só uma dessas threads e da cjoin, e esta que deverá resumar a outra
 *  Disclaimer do multicore sepa dar merda cjoin
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/cthread.h"


int global_i = 10, global_id;

void* func1(void *arg);
void* func2(void *arg);

void* func0(void *arg) {
	int id1,id2,result1,result2, i = 8;

	printf("Entering in the first thread\n");

	if (*(int *)arg == 5 && global_i == 10) {
		printf("First Thread Test SUCCEEDED\n");
	} else {
		printf("First Thread Test FAILED\n");
	}

	printf("Creating two threads in First Thread\n");

	id1 = ccreate(func1, (void *)&i, 0);
	id2 = ccreate(func2, (void *)&i, 0);

	printf("First Thread after creating two threads\n");
	printf("Suspending both created threads in First Thread\n");

  result1 = csuspend(id1);
	result2 = csuspend(id2);

	if(result1 < 0){
			printf("First Thread first suspend failed\n");
	} else {
			printf("First Thread first suspend passed\n");
	}

	if(result2 < 0){
			printf("First Thread second suspend failed\n");
	} else {
			printf("First Thread second suspend passed\n");
	}

	result2 = cresume(id2);

	if(result2 < 0){
			printf("First Thread first resume failed\n");
	} else {
			printf("First Thread first resume passed\n");
	}


	global_id = id1;
	printf("First Thread will cjoin third thread\n");
	cjoin(id2);
	printf("First Thread will cjoin second thread\n");
	cjoin(id1);
	printf("End First thread\n");
	return 0;
}

void* func1(void *arg) {
  printf("Entering in the second thread\n");

	if (*(int *)arg == 8) {
		printf("Second thread test SUCCEEDED\n");
	} else {
		printf("Second thred test FAILED\n");
	}
	return 0;
}

void* func2(void *arg) {
	int result;
  printf("Entering in the third thread\n");

	if (*(int *)arg == 8) {
		printf("Third Test SUCCEEDED\n");
	} else {
		printf("Third Test FAILED\n");
	}

	result = cresume(global_id);

	if(result < 0){
			printf("Third Thread resume failed\n");
	} else {
			printf("Third Thread resume passed\n");
	}
	return 0;
}

int main(int argc, char *argv[]) {

	int	id0, i = 5;

	printf("TEST INITIATED\n");

	printf("Creating one thread in main\n");

	id0 = ccreate(func0, (void *)&i, 0);

	printf("Main after creating one thread\n");

	cjoin(id0);
	// cyield();
	printf("VOLTEI\n");
	// cyield();
	// cyield();
  printf("TEST COMPLETED\n");

	return 0;
}
