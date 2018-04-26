#
# Makefile para programas teste
#

CC=gcc
LIB_DIR=../lib
BIN_DIR=../bin
SRC_DIR=../src
BUILD_DIR=build
all: test-ccreate


test_ccreate:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test_ccreate $(BIN_DIR)/support.o cthread.o test_ccreate.c -Wall

test_ccreate_e_cjoin_par_ou_impar:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test_ccreate_e_cjoin_par_ou_impar $(BIN_DIR)/support.o cthread.o test_ccreate_e_cjoin_par_ou_impar.c -Wall

test_cjoin:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test_cjoin $(BIN_DIR)/support.o cthread.o test_cjoin.c -Wall

test_cyield:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test_cyield $(BIN_DIR)/support.o cthread.o test_cyield.c -Wall

test_cyield_vetor_de_caracteres:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test_cyield_vetor_de_caracteres $(BIN_DIR)/support.o cthread.o test_cyield_vetor_de_caracteres.c -Wall

test_csuspend_apto:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test_csuspend_apto $(BIN_DIR)/support.o cthread.o test_csuspend_apto.c -Wall

test_csuspend_bloqueado:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test_csuspend_bloqueado $(BIN_DIR)/support.o cthread.o test_csuspend_bloqueado.c -Wall

test_cresume_apto:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test_cresume_apto $(BIN_DIR)/support.o cthread.o test_cresume_apto.c -Wall

test_cresume_bloqueado:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test_cresume_bloqueado $(BIN_DIR)/support.o cthread.o test_cresume_bloqueado.c -Wall

test_cidentify:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test_cidentify $(BIN_DIR)/support.o cthread.o test_cidentify.c -Wall

test_csem_init:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test_csem_init $(BIN_DIR)/support.o cthread.o test_csem_init.c -Wall

test_cwait:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test_cwait $(BIN_DIR)/support.o cthread.o test_cwait.c -Wall

test_csignal:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test_csignal $(BIN_DIR)/support.o cthread.o test_csignal.c -Wall

test_cwait_csignal:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test_cwait_csignal $(BIN_DIR)/support.o cthread.o test_cwait_csignal.c -Wall
