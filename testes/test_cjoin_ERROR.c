/*
 *	Test Program - cyield not using Semáforo
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/cthread.h"



void * func1(void* arg){

    *(int *)arg = 3;
    printf("APPLIED THE INTRUSION VALUE\n");

    return 0;
}

void * func0(void* arg){

    int id1;

    printf("ENTERED FIRST THREAD\n");

    printf("CREATING SECOND THREAD\n");


    id1 = ccreate(func1, (void*)arg, 0);

    *(int *)arg = 5;


    printf("APPLIED THE RIGHT VALUE\n");

    cjoin(id1);

     printf("RETURNED TO FIRST THREAD\n");


    if(*(int*)arg == 5){
        printf("TEST FAILED\n");
    } else {
        printf("TEST SUCCEEDED\n");
    }


    return 0;
}

int main(int argc, char *argv[]){

    int id0;
    int i = 0;
    int falseTid = 923;

  	printf("TEST INITIATED\n");

  	printf("Creating threads\n");

    id0 = ccreate(func0, (void *)&i, 0);

    cjoin(id0);

    int result = cjoin(falseTid);

    if(result < 0){
      printf("NO THREAD WITH THIS TID TEST SUCCEEDED\n");
    } else {
      printf("NO THREAD WITH THIS TID TEST FAILED\n");
    }

    printf("TEST COMPLETED\n");

    return 0;
}
