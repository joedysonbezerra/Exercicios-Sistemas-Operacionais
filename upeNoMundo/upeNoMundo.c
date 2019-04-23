#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define NUMBER_PARKS 6


void *visit();


int main(int argc, char **argv) {
   const int number_threads = atoi(argv[1]);
   pthread_t class[number_threads];
   pthread_barrier_t barrier;
   pthread_barrier_init(&barrier, NULL, number_threads); // cria a barreira

   int i;
   for(i = 0; i < number_threads; i++) { 
      pthread_create(&class[i], NULL, visit, &barrier);
      sleep(3);
   }

   for(i = 0; i < number_threads; i++) { 
      pthread_join(class[i], NULL);
   }

   pthread_barrier_destroy(&barrier);

   return EXIT_SUCCESS;

}

void *visit(pthread_barrier_t *barrier) {
   long int id = pthread_self(); 
   srand(time(0));

   for(int i = 1; i <= NUMBER_PARKS; i++) {
      printf("\033[37mTurma -\033[32m %ld \033[37m Chegou no:\033[3%dm P%d\n",id,(i%7),i);
      pthread_barrier_wait(barrier); 
   	sleep(rand() % 13);
   }
}