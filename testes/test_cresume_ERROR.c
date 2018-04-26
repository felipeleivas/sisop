/*
 *	Test Program - cyield not using Semáforo
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/cthread.h"

void * func0(void* arg){

    printf("Entering FIRST thread\n");

    int result = cresume(*(int *)arg);


    if(result < 0){
        printf("RESUMING IN EXECUTION THREAD TEST SUCCEEDED\n");
    } else {
        printf("RESUMING IN EXECUTION THREAD TEST FAILED\n");
    }


    cyield();

    return 0;

}

void * func1(void* arg){

    int result = cresume(*(int*)arg);

    if(result < 0){
        printf("TEST SUCCEEDED\n");
    } else {
        printf("TEST FAILED\n");
    }


    return 0;
}

int main(int argc, char *argv[]){

    int id0;
    int falseTid = 919;

	  printf("TEST INITIATED\n");

	  printf("Creating threads\n");

    id0 = ccreate(func0, (void *)&id0, 0);
    ccreate(func1, (void *)&id0, 0);

    cjoin(id0);


    int result = cresume(falseTid);

    if(result < 0){
      printf("NO THREAD WITH THIS TID TEST SUCCEEDED\n");
    } else {
      printf("NO THREAD WITH THIS TID TEST FAILED\n");
    }


    printf("TEST COMPLETED\n");

    return 0;
}
