#include <stdio.h>
#include <stdlib.h>

#include "../include/cthread.h"

int id1,id2,id3;
csem_t sem;


int foo1(){
	printf("2 foo1 its going inside the critical zone\n");
	if(cwait(&sem) != 0){
		printf("error, when doing cwait\n");
	}
	printf("3 foo1 entered critical zone will yield\n");
	cyield();
	printf("9 foo1 will do csignal\n");
	if(csignal(&sem) != 0)
		printf("error, when doing csignal\n");
	printf("10 foo1 will yield\n");
	cyield();
	printf("12 foo1 will finish\n");
	return 0;
}

int foo2(){
	printf("4 foo2 will try access critical zone\n");
	if(cwait(&sem) != 0){
		printf("error, when doing cwait\n");
	}
	printf("13 foo2 will csignal, and yield\n");
	if(csignal(&sem) != 0)
		printf("error, when foo2 tries to csignal\n");
	cyield();
	printf("15 it foo2 time, and i will finish, bye\n");
	return 666;
}

int foo3(){
	printf("5 foo3 assuming the cpu, cause foo2 its blocked, and will suspend foo2\n");
	if(csuspend(id2) != 0)
		printf("error, when suspending foo2\n");
	printf("6 will try to suspeend inexistent threads\n");
	if(csuspend(-5655) == 0)
		printf("error, shouldn't suspeend this thread\n");
	printf("7 will wait until foo2 finishes to terminate this thread\n");
	cjoin(id2);
	printf("17 its fun time with foo3, i'm super fast, good bye(foo3 will finish)\n");
	return 42;
}

int main(){
	 csem_init(&sem, 1);

	 id1 = ccreate((void *) foo1, NULL, 0);
	 id2 = ccreate((void *) foo2, NULL, 0);
	 id3 = ccreate((void *) foo3, NULL, 0);
	 printf("1 Main create 3 threads and will yield\n");
	 cyield();
	 printf("8 now its main turn, will do nothing yield\n");
	 cyield();
 	 printf("11 now its main turn, will resume foo2 and will yield\n");
 	 if(cresume(id2) != 0)
 	 	printf("error, when doing cresume\n");
 	 cyield();
 	 printf("14 its main time again, and i will just yield\n");
 	 cyield();
 	 printf("16 its me(main) one more time, sorry. This will end quickly, yield\n");
 	 cyield();
 	 printf("18 everything is done, thanks for watching\n");
 	 char names[100];
 	 cidentify(names,100);
 	 printf("19 special thanks to %s\n", names);
 	 return 0;


}