CC=gcc
LIB_DIR=./lib
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src
TEST_DIR=./testes
CFLAGS = -Wall

all: directory clean lib
directory:
	mkdir lib -p

main: cthread.o
	$(CC) -o $(BIN_DIR)/main $(BIN_DIR)/*.o -g -Wall
cthread.o: 
	$(CC) -c $(SRC_DIR)/cthread.c -o $(BIN_DIR)/cthread.o -Wall 

lib: cthread.o
	ar crs $(LIB_DIR)/libcthread.a $(BIN_DIR)/support.o $(BIN_DIR)/cthread.o 

clean:
	find $(BIN_DIR) $(LIB_DIR) $(TEST_DIR) -type f ! -name 'support.o' ! -name '*.c' ! -name 'Makefile' ! -name 'script.sh'  -exec rm -f {} +
	find $(TEST_DIR)/* -type d -exec rm  -r -f {} +

