#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cdata.h"

#define true 1
#define false 0
#define read

FILA2 readyQueue;
FILA2 blockQueue;
FILA2 suspendReadyQueue;
FILA2 suspendeblockQueue;

TCB_t *runningThread = NULL;
ucontext_t *finalizationContext = NULL;
int nextId = 0;
int systemInitialized = false;

int initQueues();
void foo();
int createMainThread();
int createfinalizationContext();
int initializesystem();
int initializeContext(ucontext_t *context, void* (*start)(void*), int argSize, void *arg);
void dispatcher();	
int generateTID();
void threadFinalizator();

void* func0(void *arg) {
	printf("Eu sou a thread ID0 imprimindo %d\n", *((int *)arg));
	return 0;
}

void* func1(void *arg) {
	printf("Eu sou a thread ID1 imprimindo %d\n", *((int *)arg));
	return 0;
}
int main(int argc, char *argv[]) {

	int	id0, id1;
	int i;

	id0 = ccreate(func0, (void *)&i, 0);
	id1 = ccreate(func1, (void *)&i, 0);
	id1 = ccreate(func0, (void *)&i, 0);

	printf("%d %d\n",id0, id1 );
	printf("Eu sou a main após a criação de ID0 e ID1\n");



	// FirstFila2(&readyQueue);
	// TCB_t *teste = GetAtIteratorFila2(&readyQueue);
	// DeleteAtIteratorFila2(&readyQueue);
	
	// setcontext(&teste->context);
	// ucontext_t *cp = & (runningThread->context);
	// setcontext(cp);
	cyield();
	// cjoin(id0);
	// cjoin(id1);

	printf("Eu sou a main voltando para terminar o programa\n");
	return 0;
}


int initQueues(){
	
	if(CreateFila2(&readyQueue) < 0){
		return -1;
	}

	if(CreateFila2(&blockQueue) < 0){
		return -1;
	}

	if(CreateFila2(&suspendReadyQueue) < 0){
		return -1;
	}

	if(CreateFila2(&suspendeblockQueue) < 0){
		return -1;
	}
	return 0;
}

void foo(){
	printf("Vamo danca tudo nu");
}
int createMainThread(){
	TCB_t *mainThread = (TCB_t *) malloc(sizeof(TCB_t));
	if(mainThread == NULL){
		return -1;
	}

	getcontext(&(mainThread->context)); 
	mainThread->tid = generateTID();
	mainThread->state = PROCST_EXEC;
	mainThread->prio = 0;
	runningThread = mainThread;
	
	return 0;
}

int createfinalizationContext(){
	finalizationContext = (ucontext_t *) malloc(sizeof(ucontext_t));
	if(finalizationContext == NULL){
		return -1;
	}
	getcontext(finalizationContext);
	finalizationContext->uc_link = NULL;
    finalizationContext->uc_stack.ss_sp = (char *) malloc(SIGSTKSZ);
    finalizationContext->uc_stack.ss_size = SIGSTKSZ;
	
	makecontext(finalizationContext, threadFinalizator, 0);
	return 0;
}

int initializesystem(){

	if(initQueues() < 0) return -1;
	if(createfinalizationContext() < 0) return -1;
	if(createMainThread() < 0) return -1;
	systemInitialized = true;
	return 0;
}
int generateTID(){
	int id= nextId;
	nextId++;
	return id;
}
void threadFinalizator(){
	free(runningThread->context.uc_stack.ss_sp);
	free(runningThread);

	dispatcher();
}
void dispatcher(){

	FirstFila2(&readyQueue);
	TCB_t *nextThread = GetAtIteratorFila2(&readyQueue);
	if(nextThread != NULL){
		DeleteAtIteratorFila2(&readyQueue);
		runningThread = nextThread;
		runningThread->state = PROCST_EXEC;
		// swapcontext(&runningThread->context,&nextThread->context);
		setcontext(&nextThread->context);
	}
}
////////////////////////////////// Library Functions ///////////////////////////////
int ccreate (void* (*start)(void*), void *arg, int prio){
	if(!systemInitialized){
		initializesystem();
	}
	TCB_t *newThread = (TCB_t *) malloc(sizeof(TCB_t));

    if (newThread == NULL)
        return -1;

    getcontext(&newThread->context);
    newThread->context.uc_link = finalizationContext;
    newThread->context.uc_stack.ss_sp = (char *) malloc(SIGSTKSZ);
    newThread->context.uc_stack.ss_size = SIGSTKSZ;
    newThread->tid = generateTID();
    newThread->state = PROCST_CRIACAO;
    newThread->prio = 0;
    
    makecontext(&newThread->context, (void (*)(void)) start, 1, arg);
    if(AppendFila2(&readyQueue, (void *) newThread) != 0) return -1;
    newThread->state = PROCST_APTO;
    return newThread->tid;
}
int cyield(void){
	if(!systemInitialized){
		initializesystem();
	}

	if(AppendFila2(&readyQueue,(void *) runningThread) != 0) return -1;
	runningThread->state = PROCST_APTO;
	TCB_t *nextThread = GetAtIteratorFila2(&readyQueue);
		printf("%s\n","sdadsa");
	if(nextThread != NULL){
		DeleteAtIteratorFila2(&readyQueue);
		swapcontext(&runningThread->context,&nextThread->context);
		runningThread = nextThread;
		runningThread->state = PROCST_EXEC;
		return 0;
	}
	return -1;
}
