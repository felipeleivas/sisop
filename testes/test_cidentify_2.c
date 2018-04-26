/*
 *	Test Program - cidentify
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/support.h"
#include "../include/cthread.h"

int main(int argc, char *argv[]) {

	char name[100] = {0}, name2[100] = {0};
	int response = 027;

	printf("Testing cidentify\n");

	response = cidentify(name, 99);
	if (response == 0) {
		printf("First Case - SUCCEEDED\n");
	} else {
		printf("First Case - FAILED\n");
	}

	response = 027;

	response = cidentify(name2, 50);
	if (response == 0) {
		printf("Second Case - SUCCEEDED\n");
	} else {
		printf("Second Case - FAILED\n");
	}

	return 0;
}
