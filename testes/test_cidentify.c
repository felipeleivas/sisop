#include "../include/support.h"
#include "../include/cthread.h"
#include <stdio.h>



int main(int argc, char **argv) {
  int size = 100;
  char name[size];
  cidentify(name, size);
  printf("%s\n",name );
  cidentify(name, 10);
  printf("%s\n",name );
    return 0; 
  }