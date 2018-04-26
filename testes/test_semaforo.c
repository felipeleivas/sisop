/*
*   Test Program - Semáforo
*
*   Creating three threads, we stablish an order for critical section access.
*   Thread 1 asks for the 'SEMAFORO' first, followed by the second thread. While the first thread asks first,
*   it will be the second who has the final say on the critical section value, for we are using a 'FIFO' structure.
*   After the third thread signals the 'SEMAFORO' and ends, the first in the line (thread 1) wakes up and changes the critical
*   variable's value. When this thread signals the 'SEMAFORO' and ends, it will be the second thread's turn to set the variable's value.
*   We return to the main thread to execute the final test.
*/


#include <stdio.h>
#include <stdlib.h>

#include "../include/cthread.h"

csem_t sem;

void * func0(void* arg){


    printf("ENTERED FIRST THREAD\n");

    if(*(int *)arg == 5){
        printf("THREAD CREATION SUCCEEDED\n");
    }else{
        printf("THREAD CREATION FAILED\n");
    }


    printf("FIRST THREAD STARTS TO SLEEP\n");
    cwait(&sem);
    printf("FIRST THREAD WAKES UP\n");

    *(int *) arg = 3;

    printf("FIRST THREAD SIGNALS SECOND THREAD\n");
    csignal(&sem);

    printf("FIRST THREAD ENDS\n");
    return 0;

}

void * func1(void* arg){


    printf("ENTERED SECOND THREAD\n");

    if(*(int *)arg == 5){
        printf("THREAD CREATION SUCCEEDED\n");
    }else{
        printf("THREAD CREATION FAILED\n");
    }


    printf("SECOND THREAD STARTS TO SLEEP\n");
    cwait(&sem);
    printf("SECOND THREAD WAKES UP\n");

    *(int *) arg = 7;

    printf("SECOND THREAD ENDS\n");
    return 0;

}

void * func2(void* arg){

    printf("ENTERED THIRD THREAD\n");

    if(*(int *)arg == 5){
        printf("THREAD CREATION SUCCEEDED\n");
    }else{
        printf("THREAD CREATION FAILED\n");
    }

    *(int *) arg = 70;




    printf("THIRD THREAD SIGNALS FIRST THREAD\n");
    csignal(&sem);
    printf("THIRD THREAD ENDS\n");

    return 0;

}




int main(int argc, char * argv[]){

    int id1;
    int i = 5;


    csem_init(&sem, 0);

    printf("Creating both threads\n");

    ccreate(func0, (void *)&i, 0);
    id1 = ccreate(func1, (void *)&i, 0);
    ccreate(func2, (void *)&i, 0);

    cjoin(id1);

    if(i == 7){
        printf("TEST SUCCEEDED\n");
    }else{
        printf("TEST FAILED\n");
    }

    printf("TEST COMPLETED\n");

    return 0;
}
