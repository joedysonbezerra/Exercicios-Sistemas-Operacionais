#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <string.h>

#define NUMBER_THREADS 10
#define MAX 9999999999
void *bruteForce();
void *createThreads();

struct data {
   int id;
   char password[10];
   long long int initial;
   long long int end;
   pthread_cond_t semaphore;
   pthread_mutex_t mutex;
};

int main(int argc, char **argv) {
   struct data *args = (struct data *)malloc(sizeof(struct data));
   pthread_cond_init(&args->semaphore, NULL);
   pthread_mutex_init(&args->mutex, NULL);
   pthread_t threads[NUMBER_THREADS];
   
   strcpy(args->password,argv[1]);
   args->initial = 0; 
   args->end = (MAX / NUMBER_THREADS) + 1;
   
   long int aux;
   aux = args->end;


   int i;
   for(i = 0; i < NUMBER_THREADS; i++) { 
      pthread_mutex_lock(&args->mutex);
      
      args->id = i;
      
      pthread_create(&threads[i], NULL, bruteForce,(void *)args);
      
      pthread_cond_wait(&args->semaphore, &args->mutex);
      args->initial = args->end + 1;
      args->end += aux;
      pthread_mutex_unlock(&args->mutex);

   }

   for(i = 0; i < NUMBER_THREADS; i++) {
      pthread_join(threads[i], NULL);
   }
   return EXIT_SUCCESS;
}

void *bruteForce(void *value) {
   pthread_mutex_lock(&((struct data*)value)->mutex);
   
   int id = (int)((struct data*)value)->id;
   long long int initial = (long long int)((struct data*)value)->initial;
   long long int end = (long long int)((struct data*)value)->end;
   
   pthread_cond_signal(&((struct data*)value)->semaphore);
   
   pthread_mutex_unlock(&((struct data*)value)->mutex);
   
   char password [10];
   for(initial; initial < end; initial++) {
      //printf("t_id - %d initial - %lld end - %lld\n",id,initial,end);
      sprintf(password, "%lld", initial );
		if(strcmp(((struct data*)value)->password,password) == 0) {
			printf("\033[37m Thread -\033[31m %d\033[37m Senha -\033[32m %lld\n",id, initial);
			exit(EXIT_SUCCESS);
		}
			
	}
}