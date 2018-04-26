/*
 *	Test Program - cyield not using Semáforo
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/cthread.h"

void * func0(void* arg){


    printf("ENTERED FIRST THREAD\n");

    *(int *)arg = 5;

    printf("APPLIED THE RIGHT VALUE\n");

    cyield();

    if(*(int *)arg == 5){
        printf("NO SEMAFORO TEST FAILED\n");
    } else {
        printf("NO SEMAFORO TEST SUCCEEDED\n");
    }

    return 0;
}

void * func1(void* arg){

    *(int *)arg = 3;
    printf("APPLIED THE INTRUSION VALUE\n");

    return 0;
}

int main(int argc, char *argv[]){

    int id0;
    int i = 0;

	printf("TEST INITIATED\n");

	printf("Creating threads\n");

    id0 = ccreate(func0, (void *)&i, 0);
    ccreate(func1, (void *)&i, 0);

    cjoin(id0);


    printf("TEST COMPLETED\n");

    return 0;
}
