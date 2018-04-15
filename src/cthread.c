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
FILA2 blockedsByAnotherThread;

TCB_t *runningThread = NULL;
ucontext_t *finalizationContext = NULL;
int nextId = 0;
int systemInitialized = false;

int initQueues();
int createMainThread();
int createfinalizationContext();
int initializesystem();
int initializeContext(ucontext_t *context, void* (*start)(void*), int argSize, void *arg);
int dispatcher();	
int generateTID();
void threadFinalizator();
void printQueue(FILA2 fila);
void unblockThread(int blockedThreadTid);
int anyThreadBlockedForThis(int blockerThreadTid);


void* func0(void *arg) {
	printf("Eu sou a thread ID0 imprimindo %d\n", *((int *)arg));
	// printf("cyield func0()\n" );
	if( cyield()!= 0) printf("ÉRRRRRRRRRRRRRRRRRRRRRRRor\n");
	printf("%s\n", "Aqui eh a parte tricky" );
	return 0;
}

void* func1(void *arg) {
	printf("Eu sou a thread ID1 imprimindo %d\n", *((int *)arg));
	if(cjoin(1) != 0) printf("ERROR\n");;
	return 0;
}
// int main(int argc, char *argv[]) {

// 	int	id0, id1;
// 	int i;

// 	id0 = ccreate(func0, (void *)&i, 0);
// 	id1 = ccreate(func1, (void *)&i, 0);

// 	printf("%d %d\n",id0, id1 );
// 	printf("Eu sou a main apos a criacao de ID0 e ID1\n");



// 	// FirstFila2(&readyQueue);
// 	// TCB_t *teste = GetAtIteratorFila2(&readyQueue);
// 	// DeleteAtIteratorFila2(&readyQueue);
	
// 	// setcontext(&teste->context);
// 	// ucontext_t *cp = & (runningThread->context);
// 	// setcontext(cp);
// 	// printf("cyield main()\n" );
// 	// if( cyield()!= 0) printf("ÉRRRRRRRRRRRRRRRRRRRRRRRor\n");
// 	// printf("main VOltando mas vai deixar outras coisas acontecerem\n");
// 	// if( cyield()!= 0) printf("ÉRRRRRRRRRRRRRRRRRRRRRRRor\n");

// 	// cjoin(id0);
// 	cjoin(id1);

// 	printf("Eu sou a main voltando para terminar o programa\n");
// 	return 0;
// }


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
	if(CreateFila2(&blockedsByAnotherThread) < 0){
		return -1;
	}
	return 0;
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
	printf("FINALIZADOR DE THREAD DELETANDO %d\n", runningThread->tid );
	int blockedThreadTid = anyThreadBlockedForThis(runningThread->tid);
	if(blockedThreadTid != -1) unblockThread(blockedThreadTid);
	free(runningThread->context.uc_stack.ss_sp);
	free(runningThread);
	
	dispatcher();
}
void unblockThread(int blockedThreadTid){
	TCB_t *aux;
	FirstFila2(&blockQueue);
	while((aux = GetAtIteratorFila2(&blockQueue)) && aux!= NULL){
		if(aux->tid == blockedThreadTid){
			AppendFila2(&readyQueue, (void *) aux);
			DeleteAtIteratorFila2(&blockQueue);
			break;
		}
		NextFila2(&blockQueue);
	}
}
void printQueue(FILA2 fila){
	FirstFila2(&fila);
	TCB_t *aux;
	printf("threads on readyQueue: ");
	while((aux = GetAtIteratorFila2(&fila)) && aux!= NULL){
		aux = GetAtIteratorFila2(&fila);
		printf("\t%d",aux->tid);
		NextFila2(&fila);
	}
	printf("\n");
}

int anyThreadBlockedForThis(int blockerThreadTid){
	BlockedThreadPair *aux;
	FirstFila2(&blockedsByAnotherThread);
	while((aux = GetAtIteratorFila2(&blockedsByAnotherThread)) && aux!= NULL){
		if(aux->blockerThreadTid == blockerThreadTid){
			return aux->blockedThreadTid;
		}
		NextFila2(&blockedsByAnotherThread);
	}
	return -1;
}

int dispatcher(){

	FirstFila2(&readyQueue);
	TCB_t *nextThread = GetAtIteratorFila2(&readyQueue);
	if(nextThread != NULL){
		DeleteAtIteratorFila2(&readyQueue);
		TCB_t *oldThread = runningThread;
		runningThread = nextThread;
		runningThread->state = PROCST_EXEC;
		swapcontext(&oldThread->context,&nextThread->context);
		return 0;
	}
	else return -1;
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
	
	return dispatcher();
}

int cjoin(int tid){
	if(!systemInitialized){
		initializesystem();
	}

	if(anyThreadBlockedForThis(tid) == -1){
		BlockedThreadPair *newBlockedThread = (BlockedThreadPair *) malloc(sizeof(BlockedThreadPair));
		if(newBlockedThread == NULL) return -1;
		newBlockedThread->blockerThreadTid = tid;
		newBlockedThread->blockedThreadTid = runningThread->tid;
		if( AppendFila2(&blockedsByAnotherThread, (void *) newBlockedThread) != 0) return -1;
		
		runningThread->state = PROCST_BLOQ;
		if( AppendFila2(&blockQueue, (void *) runningThread) != 0) return -1;

		return dispatcher();
	}

	else{
		return -1;

	}
}