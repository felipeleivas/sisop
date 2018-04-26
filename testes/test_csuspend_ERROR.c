/*
 *	Test Program - cyield not using Semáforo
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/cthread.h"

void * func0(void* arg){

    printf("Entering FIRST thread\n");

    printf("ENTERED LOOP\n");
    while(1){
	};

}

void * func1(void* arg){

    int result = csuspend(*(int*)arg);

    if(result < 0){
        printf("TEST SUCCEEDED\n");
    } else {
        printf("TEST FAILED\n");
    }


    return 0;
}

int main(int argc, char *argv[]){

    int id0, id1;
    int i = 5;
    int falseTid = 924;

	printf("TEST INITIATED\n");

	printf("Creating threads\n");

    id0 = ccreate(func0, (void *)&i, 0);
    id1 = ccreate(func1, (void *)&id0, 0);

    csuspend(id0);
    printf("FIRST THREAD SUSPENDED\n");

    cjoin(id1);


    int result = csuspend(falseTid);

    if(result < 0){
      printf("NO THREAD WITH THIS TID TEST SUCCEEDED\n");
    } else {
      printf("NO THREAD WITH THIS TID TEST FAILED\n");
    }


    printf("TEST COMPLETED\n");

    return 0;
}
