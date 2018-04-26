/*
 *	Test Program - cresume
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include "../include/cthread.h"

csem_t sem;
int id1,id2;

void* func0(void *arg) {
  printf("[1] func0\n");
  cwait(&sem);
  printf("[2] cyield func0\n");
  cyield();


  printf("[6] func0 with locking SC and suspending func1\n");
  csuspend(id2);
  cyield();


  printf("[7] func0 unloking SC\n");
  csignal(&sem);
  cyield();


  printf("[9] func0 resuming func1\n");
  cresume(id2);
  cyield();


	return 0;
}

void* func1(void *arg) {
  printf("[3]func1\n");
  printf("[4]cwait func1 WITH LOCKED SC SO WILL SLEEP\n");
  cwait(&sem);


  printf("[10] func1 running with unlocked SC\n");


	return 0;
}

void* func2(void *arg) {
  printf("[5] func2  after func0 lock SC and func1 sleeps for being locked SC\n");
  cyield();


  printf("[6] func2 after func0 suspend blocked func1 while still locking SC\n");
  cyield();


  printf("[8] func2 after SC unlocked but func1 now has to be on suspended apt\n");
	return 0;
}


int main(int argc, char *argv[]) {
	printf("TEST INITIATED\n");
  csem_init(&sem,1);

	id1 = ccreate(func0,NULL , 0);
  id2 = ccreate(func1, NULL, 0);
  ccreate(func2,NULL, 0);

  printf("Main cjoin func1\n");
  cjoin(id1);
  printf("COMPLETED TEST\n");


	return 0;
}
