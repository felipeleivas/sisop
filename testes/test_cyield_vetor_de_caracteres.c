/*
 * test_vetor.c: realiza a criação de 10 threads, cada uma delas escreve uma
 * sequencia de 20 letras iguais e passa a vez para outra thread. Repete até
 * preencher um vetor de 250 caracteres.
 */

#include "../include/support.h"
#include "../include/cthread.h"
#include <stdio.h>

#define		MAX_SIZE	250
#define		MAX_THR		10

int vetor[MAX_SIZE];
int  inc = 0;
int contador = 0;

void *func(void *arg){
   contador++;
   printf("Entrei na thread %d\n", contador);
   while ( inc < MAX_SIZE ) {
       vetor[inc] = (int)arg;
       inc++;
       if ( (inc % 20) == 0 )
           cyield();
       else
           continue;
   }
   printf("Acabei a thread...\n");
   return (NULL);
}


int main(int argc, char *argv[]) {
    int i, pid[MAX_THR];


    for (i = 0; i < MAX_THR; i++) {
        pid[i] = ccreate(func, (void *)('A'+i), 0);
       if ( pid[i] == -1) {
          printf("ERRO: criação de thread!\n");
          return(-1);
       }
     }

    for (i = 0; i < MAX_THR; i++)
         cjoin(pid[i]);

    for (i = 0; i < MAX_SIZE; i++) {
        if ( (i % 20) == 0 )
           printf("\n");
        printf("%c", (char)vetor[i]);
    }

    printf("\nConcluido vetor de letras...\n");
    return(0);
}
