/* Diego Henrique Dorta
   RA: 10005460
   Date: 03/05/2015
*/
#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <pthread.h>

#define NO_OF_ITERATIONS	1000
#define NO_OF_CHAIRS		5
#define NO_OF_BARBERS		3
#define NO_OF_CUSTOMER		20
#define MICRO_PER_SECOND	1000000

#define SEM_KEY_1		0x1401
#define SEM_KEY_2		0x1411

pthread_t barbers[NO_OF_BARBERS];
pthread_t customers[NO_OF_CUSTOMER];

int g_sem_id_barbers;
int g_sem_id_customers;	

int waiting; 
int indice_customer;  
int indice_barber; 

struct sembuf g_lock_sembuf[1];
struct sembuf g_unlock_sembuf[1];

void *customer(void *customer_no);
void *barber(void *barber_no);
void apreciate_hair();
void cut_hair();

int main(void) {

	int count;
	int i = 0;
	int tb, tc;

	waiting = 0;
	indice_customer = -1;  
	indice_barber = -1;

	g_lock_sembuf[0].sem_num   =  0;
	g_lock_sembuf[0].sem_op    = -1;
	g_lock_sembuf[0].sem_flg   =  0;

	g_unlock_sembuf[0].sem_num =  0;
	g_unlock_sembuf[0].sem_op  =  1;
	g_unlock_sembuf[0].sem_flg =  0;

	if( ( g_sem_id_barbers = semget( SEM_KEY_1, 1, IPC_CREAT | 0666 ) ) == -1 ) {
		fprintf(stderr,"chamada a semget() falhou, impossivel criar o conjunto de semaforos!");
		exit(EXIT_FAILURE);
	}

	if( ( g_sem_id_customers = semget( SEM_KEY_2, 1, IPC_CREAT | 0666 ) ) == -1 ) {
		fprintf(stderr,"chamada a semget() falhou, impossivel criar o conjunto de semaforos!");
		exit(EXIT_FAILURE);
	}

	for (count = 0; count < NO_OF_BARBERS; count++)	{	
		tb = pthread_create(&barbers[i], NULL, barber, (void *)(intptr_t)count+1);
		if (tb) {
			printf("ERRO: impossivel criar um thread barbeiro\n");
			exit(EXIT_FAILURE);
		}
	}

	for (count = 0; count < NO_OF_CUSTOMER; count++) {				
		tc = pthread_create(&customers[i], NULL, customer, (void *)(intptr_t)count+1);
		if (tc) {
			printf("ERRO: impossivel criar um thread cliente\n");
			exit(EXIT_FAILURE);
		}
	}

	for (i = 0; i < NO_OF_BARBERS + NO_OF_CUSTOMER; i++) {		

		if (i >= NO_OF_BARBERS) {
			tb = pthread_join(customers[i-NO_OF_BARBERS], NULL);
			if (tb) {
				printf("ERRO: impossivel terminar um thread cliente\n");
				exit(EXIT_FAILURE);
			}
		}	
		else {
			tb = pthread_join(barbers[i], NULL);
			if (tb) {
				printf("ERRO: impossivel terminar um thread barbeiro\n");
				exit(EXIT_FAILURE);
			}
		}			
	}

	if( semctl( g_sem_id_barbers, 0, IPC_RMID, 0) != 0 ) {
		fprintf(stderr,"Impossivel remover o conjunto de semaforos!\n");
		exit(EXIT_FAILURE);
	}

	if( semctl( g_sem_id_customers, 0, IPC_RMID, 0) != 0 ) {
		fprintf(stderr,"Impossivel remover o conjunto de semaforos!\n");
		exit(EXIT_FAILURE);
	}
}

void *barber(void *barber_no) {  

	int indice = 0;
	int id_barber;

	id_barber = (int)(intptr_t)barber_no;

	printf("Barbeiro #%d iniciado ...\n", id_barber);
	fflush(stdout);

	/*while (true) {
	if(semop(g_sem_id_customers, g_lock_sembuf, 1) == -1) {
		fprintf(stderr,"chamada semop() falhou, impossivel fechar o recurso!");
		exit(EXIT_FAILURE);
	}

	waiting--;

	indice = indice_barber+1;

	printf("O barbeiro #%d esta atendendo o cliente #%d\n\n", id_barber);      
	fflush(stdout);

	indice_barber++;


	cut_hair();

      
	if(semop(g_sem_id_barbers, g_unlock_sembuf, 1) == -1) {      		
		fprintf(stderr,"chamada semop() falhou, impossivel liberar o recurso!");
		exit(EXIT_FAILURE);
	}
	}*/
}

void *customer(void *customer_no) {

	struct timeval tv;
	struct timeval start_time;

	int number1, number2;
	int indice;
	int result, barber_no;  
	int id_customer;

	id_customer = (int)(intptr_t)customer_no; 

	printf("Cliente #%d iniciado ...\n", id_customer);

	if(gettimeofday(&tv, NULL) == -1) {
		fprintf(stderr,"Impossivel conseguir o tempo atual, terminando.\n");
		exit(EXIT_FAILURE);
	}

	if(gettimeofday(&tv, NULL) == -1) {
		fprintf(stderr,"Impossivel conseguir o tempo atual, terminando.\n");
		exit(EXIT_FAILURE);
	}

	/*if (waiting < NO_OF_CHAIRS) {	
	
		gettimeofday(&start_time, NULL); 

		waiting++;
		indice = indice_customer+1; 
		indice_customer++;

		printf("O cliente #%d esta sentado aguardando ser chamado e eh o %do na fila.\n", id_customer, waiting);
		fflush(stdout);

	 
		if(semop(g_sem_id_customers, g_unlock_sembuf, 1) == -1) {
			fprintf(stderr,"chamada semop() falhou, impossivel liberar o recurso!");
			exit(EXIT_FAILURE);
		}

		if(semop(g_sem_id_barbers, g_lock_sembuf, 1) == -1) { 
			fprintf(stderr,"chamada semop() falhou, impossivel fechar o recurso!");
			exit(EXIT_FAILURE);
		}


		apreciate_hair(); 
	}
	else
		printf("O cliente #%d nao foi atendido porque a barbearia estava lotada.\n", id_customer);
	*/
	printf("Cliente #%d terminou!\n\n", id_customer);
	fflush(stdout);
}



void cut_hair() {
	return;    
}

void apreciate_hair() {
	return;
}


