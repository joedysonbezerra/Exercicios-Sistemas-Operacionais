#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define NUMBER_THREADS 5


void *visit();


int main(int argc, char **argv) {
   pthread_t class[NUMBER_THREADS];
   pthread_barrier_t barrier;
   pthread_barrier_init(&barrier, NULL, NUMBER_THREADS); // cria a barreira

   int i;
   for(i = 0; i < NUMBER_THREADS; i++) { 
      pthread_create(&class[i], NULL, visit, &barrier);
      sleep(3);
   }

   for(i = 0; i < NUMBER_THREADS; i++) { 
      pthread_join(class[i], NULL);
   }

   pthread_barrier_destroy(&barrier);

   return EXIT_SUCCESS;

}

void *visit(pthread_barrier_t *barrier) {
   long int id = pthread_self(); //id real
   srand(time(0));
   
   printf("\033[37mTurma -\033[32m %ld \033[37m Chegou no:\033[31m PA\n",id);
   pthread_barrier_wait(barrier);//só prossiga quando chegar as 5 threads 
	sleep(rand() % 13);

   printf("\033[37mTurma -\033[32m %ld \033[37m Chegou no:\033[33m PB\n",id);
   pthread_barrier_wait(barrier);
	sleep(rand() % 14);

   printf("\033[37mTurma -\033[32m %ld \033[37m Chegou no:\033[34m PC\n",id);
   pthread_barrier_wait(barrier);
	sleep(rand() % 15);

   printf("\033[37mTurma -\033[32m %ld \033[37m Chegou no:\033[35m PD\n",id);
   pthread_barrier_wait(barrier);
	sleep(rand() % 16);

   printf("\033[37mTurma -\033[32m %ld \033[37m Chegou no:\033[36m PE\n",id);
   pthread_barrier_wait(barrier);
	sleep(rand() % 17);

}