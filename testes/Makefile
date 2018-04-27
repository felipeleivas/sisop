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

test_cidentify_2:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test_cidentify_2 $(BIN_DIR)/support.o  cthread.o test_cidentify_2.c -Wall

test_ccreate_2:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test-ccreate_2 $(BIN_DIR)/support.o cthread.o test_ccreate_2.c -Wall

test_cjoin_2:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test_cjoin_2 $(BIN_DIR)/support.o cthread.o test_cjoin_2.c -Wall

test_cjoin_critical:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test_cjoin_critical $(BIN_DIR)/support.o cthread.o test_cjoin_critical.c -Wall

test_cjoin_critical2:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test_cjoin_critical2 $(BIN_DIR)/support.o cthread.o test_cjoin_critical2.c -Wall

test_cyield_2:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test_cyield_2 $(BIN_DIR)/support.o cthread.o test_cyield_2.c -Wall

test_csuspend_2:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test_csuspend_2 $(BIN_DIR)/support.o cthread.o test_csuspend_2.c -Wall

test_cresume_2:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test_cresume_2 $(BIN_DIR)/support.o cthread.o test_cresume_2.c -Wall

test_global_suspension:
		rm -rf build
		mkdir $(BUILD_DIR)
		$(CC) -c $(SRC_DIR)/cthread.c
		$(CC) -o $(BUILD_DIR)/test_global_suspension $(BIN_DIR)/support.o cthread.o test_global_suspension.c -Wall

test_cyield_ERROR:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test_cyield_ERROR $(BIN_DIR)/support.o cthread.o test_cyield_ERROR.c -Wall

test_csuspend_ERROR:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test_csuspend_ERROR $(BIN_DIR)/support.o cthread.o test_csuspend_ERROR.c -Wall

test_cresume_ERROR:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test_cresume_ERROR $(BIN_DIR)/support.o cthread.o test_cresume_ERROR.c -Wall

test_cjoin_ERROR:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test_cjoin_ERROR $(BIN_DIR)/support.o cthread.o test_cjoin_ERROR.c -Wall

test_semaforo:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test_semaforo $(BIN_DIR)/support.o cthread.o test_semaforo.c -Wall

test_wait_suspens:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test_wait_suspens $(BIN_DIR)/support.o cthread.o test_wait_suspens.c -Wall

test_wait_suspens_lib:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -o $(BUILD_DIR)/test_wait_suspens test_wait_suspens.c -L../lib -lcthread -Wall

test_min_threads:
	rm -rf build
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/cthread.c
	$(CC) -o $(BUILD_DIR)/test_min_threads $(BIN_DIR)/support.o cthread.o test_min_threads.c -Wall

clean:
	rm -rf *.o *~ build
