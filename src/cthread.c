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
FILA2 suspendBlockQueue;
FILA2 blockedsByAnotherThread;

TCB_t *runningThread = NULL;
ucontext_t *finalizationContext = NULL;
int nextId = 0;
int systemInitialized = false;

int initQueues();
int createMainThread();
int createFinalizationContext();
int initializeSystem();
int initializeContext(ucontext_t *context, void* (*start)(void*), int argSize, void *arg);
int dispatcher();
int generateTID();
void threadFinalizator();
void printQueue(FILA2 fila);
int unblockThread(int blockedThreadTid);
int anyThreadBlockedForThis(int blockerThreadTid);
int changeQueueOfThread(FILA2 originQueue, FILA2 destinyQueue, int threadTid);


int initQueues() {
	if(CreateFila2(&readyQueue) < 0) {
		return -1;
	}

	if(CreateFila2(&blockQueue) < 0) {
		return -1;
	}

	if(CreateFila2(&suspendReadyQueue) < 0) {
		return -1;
	}

	if(CreateFila2(&suspendBlockQueue) < 0) {
		return -1;
	}
	if(CreateFila2(&blockedsByAnotherThread) < 0) {
		return -1;
	}
	return 0;
}

int createMainThread() {
	TCB_t *mainThread = (TCB_t *) malloc(sizeof(TCB_t));
	if(mainThread == NULL) {
		return -1;
	}

	getcontext(&(mainThread->context));
	mainThread->tid = generateTID();
	mainThread->state = PROCST_EXEC;
	mainThread->prio = 0;
	runningThread = mainThread;

	return 0;
}

int createFinalizationContext() {
	finalizationContext = (ucontext_t *) malloc(sizeof(ucontext_t));
	if(finalizationContext == NULL) {
		return -1;
	}
	getcontext(finalizationContext);
	finalizationContext->uc_link = NULL;
  finalizationContext->uc_stack.ss_sp = (char *) malloc(SIGSTKSZ);
  finalizationContext->uc_stack.ss_size = SIGSTKSZ;

	makecontext(finalizationContext, threadFinalizator, 0);
	return 0;
}

int initializeSystem() {
	if(initQueues() < 0) return -1;
	if(createFinalizationContext() < 0) return -1;
	if(createMainThread() < 0) return -1;
	systemInitialized = true;
	return 0;
}

int generateTID() {
	int id = nextId;
	nextId++;
	return id;
}

void threadFinalizator() {
	int blockedThreadTid = anyThreadBlockedForThis(runningThread->tid);
	if(blockedThreadTid != -1) {
		if(unblockThread(blockedThreadTid) != 0) {

		}
	}
	free(runningThread->context.uc_stack.ss_sp);
	free(runningThread);

	dispatcher();
}

int unblockThread(int blockedThreadTid) {
	TCB_t *aux;
	int unblockThread = false;

	FirstFila2(&blockQueue);
	while((aux = GetAtIteratorFila2(&blockQueue))
			&& aux != NULL && unblockThread == false) {
		if(aux->tid == blockedThreadTid) {
			aux->state = PROCST_APTO;
			AppendFila2(&readyQueue, (void *) aux);
			DeleteAtIteratorFila2(&blockQueue);
			unblockThread = true;
		}
		NextFila2(&blockQueue);
	}

	FirstFila2(&suspendBlockQueue);
	while((aux = GetAtIteratorFila2(&suspendBlockQueue))
		  && aux != NULL && unblockThread == false) {
		if(aux->tid == blockedThreadTid) {
			aux->state = PROCST_APTO_SUS;
			AppendFila2(&suspendReadyQueue, (void *) aux);
			DeleteAtIteratorFila2(&suspendBlockQueue);
			unblockThread = true;
		}
		NextFila2(&suspendBlockQueue);
	}

	// if (changeQueueOfThread(blockQueue,readyQueue,blockedThreadTid) != 0){             // I couldn't understand why this isn't working, it appers to change the pointer when passing the parameter to another function
	// 	if(changeQueueOfThread(suspendBlockQueue, suspendReadyQueue, blockedThreadTid) != 0){
	// 		return -1;
	// 	}
	// }
	return !unblockThread	;
}

void printQueue(FILA2 fila) {
	FirstFila2(&fila);
	TCB_t *aux;
	printf("threads on readyQueue: ");

	while((aux = GetAtIteratorFila2(&fila)) && aux != NULL) {
		aux = GetAtIteratorFila2(&fila);
		printf("\t%d",aux->tid);
		NextFila2(&fila);
	}
	printf("\n");
}


int anyThreadBlockedForThis(int blockerThreadTid) {
	BlockedThreadPair *aux;
	FirstFila2(&blockedsByAnotherThread);

	while((aux = GetAtIteratorFila2(&blockedsByAnotherThread)) && aux != NULL) {
		if(aux->blockerThreadTid == blockerThreadTid) {
			return aux->blockedThreadTid;
		}
		NextFila2(&blockedsByAnotherThread);
	}
	return -1;
}

// int changeQueueOfThread(FILA2 originQueue, FILA2 destinyQueue, int threadTid){
// 	TCB_t *aux;

// 	FirstFila2(&originQueue);
// 	while((aux = GetAtIteratorFila2(&originQueue)) && aux!= NULL){
// 		if(aux->tid == threadTid){
// 			printf("VAI POR NA FILA THREAD %d\n", aux->tid);
// 			printQueue(destinyQueue);
// 			FirstFila2(&destinyQueue);
// 			AppendFila2(&destinyQueue, (void *) aux);
// 			printQueue(destinyQueue);
// 			DeleteAtIteratorFila2(&originQueue);
// 			return 0;
// 		}
// 		NextFila2(&originQueue);
// 	}
// 	return -1;
// }

int dispatcher() {
	FirstFila2(&readyQueue);
	TCB_t *nextThread = GetAtIteratorFila2(&readyQueue);

	if(nextThread != NULL) {
		DeleteAtIteratorFila2(&readyQueue);
		TCB_t *oldThread = runningThread;
		runningThread = nextThread;
		runningThread->state = PROCST_EXEC;
		swapcontext(&oldThread->context,&nextThread->context);
		return 0;
	} else {
		return -1;
	}
}

////////////////////////////////// Library Functions ///////////////////////////////
int ccreate (void* (*start)(void*), void *arg, int prio) {
	if(!systemInitialized) {
		initializeSystem();
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
  if(AppendFila2(&readyQueue, (void *) newThread) != 0)
		return -1;
  newThread->state = PROCST_APTO;
  return newThread->tid;
}

int cyield(void) {
	if(!systemInitialized) {
		initializeSystem();
	}
	if(AppendFila2(&readyQueue,(void *) runningThread) != 0) return -1;
	runningThread->state = PROCST_APTO;

	return dispatcher();
}

int cjoin(int tid) {
	if(!systemInitialized) {
		initializeSystem();
	}

	if(anyThreadBlockedForThis(tid) == -1) {
		BlockedThreadPair *newBlockedThread = (BlockedThreadPair *) malloc(sizeof(BlockedThreadPair));
		if(newBlockedThread == NULL)
			return -1;

		newBlockedThread->blockerThreadTid = tid;
		newBlockedThread->blockedThreadTid = runningThread->tid;
		if( AppendFila2(&blockedsByAnotherThread, (void *) newBlockedThread) != 0)
			return -1;

		runningThread->state = PROCST_BLOQ;
		if( AppendFila2(&blockQueue, (void *) runningThread) != 0)
			return -1;

		return dispatcher();
	}	else {
		return -1;
	}
}

int csuspend(int tid) {
	if(!systemInitialized) {
		initializeSystem();
	}

	if(runningThread->tid == tid)
		return -1;
	TCB_t *aux;
	int suspendThread = false;

	FirstFila2(&blockQueue);
	while((aux = GetAtIteratorFila2(&blockQueue)) && aux != NULL && suspendThread == false) {
		if(aux->tid == tid) {
			aux->state = PROCST_APTO_SUS;
			AppendFila2(&suspendBlockQueue, (void *) aux);
			DeleteAtIteratorFila2(&blockQueue);
			suspendThread = true;
		}
		NextFila2(&blockQueue);
	}

	FirstFila2(&readyQueue);
	while((aux = GetAtIteratorFila2(&readyQueue)) && aux != NULL && suspendThread == false) {
		if(aux->tid == tid) {
			aux->state = PROCST_BLOQ_SUS;
			AppendFila2(&suspendReadyQueue, (void *) aux);
			DeleteAtIteratorFila2(&readyQueue);
			suspendThread = true;
		}
		NextFila2(&readyQueue);
	}
	return 0;
}

int cresume(int tid) {
	if(!systemInitialized) {
		initializeSystem();
	}

	TCB_t *aux;
	int resumeThread = false;

	FirstFila2(&suspendBlockQueue);
	while((aux = GetAtIteratorFila2(&suspendBlockQueue)) && aux != NULL && resumeThread == false) {
		if(aux->tid == tid) {
			aux->state = PROCST_BLOQ;
			AppendFila2(&blockQueue, (void *) aux);
			DeleteAtIteratorFila2(&suspendBlockQueue);
			resumeThread = true;
		}
		NextFila2(&suspendBlockQueue);
	}

	FirstFila2(&suspendReadyQueue);
	while((aux = GetAtIteratorFila2(&suspendReadyQueue)) && aux != NULL && resumeThread == false) {
		if(aux->tid == tid) {
			aux->state = PROCST_EXEC;
			AppendFila2(&readyQueue, (void *) aux);
			DeleteAtIteratorFila2(&suspendReadyQueue);
			resumeThread = true;
		}
		NextFila2(&suspendReadyQueue);
	}
	return 0;
}

int csem_init(csem_t *sem, int count) {
	sem->fila = (PFILA2) malloc(sizeof(FILA2));
	if (sem->fila != NULL) {
		sem->count = count;
		CreateFila2(sem->fila);
		return 0;
	}
	else
		return -1;
}

int cwait(csem_t *sem) {
	if (sem != NULL){
		if(sem->count <= 0){    //if sem->count <= 0, thread needs to be blocked
            sem->count--;
            runningThread->state = PROCST_BLOQ;
            if(AppendFila2(sem->fila, (void *) runningThread) != 0)
                return -1;
            dispatcher();
		}
        else         //if sem->count > 0, nothing to do (thread enter critical zone).
            sem->count--;
	}
	else            //if sem == NULL, error
        return -1;
    return 0;
}

int csignal(csem_t *sem){
	if (sem != NULL){
	        if (sem->count < 0){
			FirstFila2(sem->fila);
			sem->count++;
			TCB_t *tcb = (TCB_t*)GetAtIteratorFila2(sem->fila);
			if(tcb != NULL){
				tcb->state = PROCST_APTO;
				if(AppendFila2(&readyQueue, (void*) tcb) != 0)
					return -1;
				DeleteAtIteratorFila2(sem->fila);
			}
	        }
		else
			sem->count++;
	}
	else
		return -1;
	return 0;
}
int cidentify (char *name, int size){
char names[] = "Felipe Leivas Machado - 262528, Botem o nome de voces aqui\n\0";
	if(size < 0){
		return -1;
	}
	int i = 0;
	for(i = 0; i < size -1; i++){
		if(names[i] == '\0'){
			name[i] = '\0';
			return 0;
		}
		else{
			name[i] = names[i];
		}	
	}
	name[i] = '\0';
	return 0;
}
