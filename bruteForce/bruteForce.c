#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define NUMBER_THREADS 10
#define MAX 9999999999

void *bruteForce();

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
   int i = 0;
   
   strcpy(args->password,argv[1]); 
   args->end = 0;
   
   const long int aux = (MAX / NUMBER_THREADS) + 1;

   while(i < NUMBER_THREADS) {
      pthread_mutex_lock(&args->mutex);
      
      args->id = i;
      args->initial = args->end;
      args->end += aux;
      pthread_create(&threads[i], NULL, bruteForce,(void *)args);
      
      pthread_cond_wait(&args->semaphore, &args->mutex);//espera 
      i++;
      pthread_mutex_unlock(&args->mutex);
   }

   for(i = 0; i < NUMBER_THREADS; i++) {
      pthread_join(threads[i], NULL);
   }
   return EXIT_SUCCESS;
}

void *bruteForce(void *pArgs) {
   pthread_mutex_lock(&((struct data*)pArgs)->mutex);
   
   int id = (int)((struct data*)pArgs)->id;
   long long int initial = (long long int)((struct data*)pArgs)->initial;
   long long int end = (long long int)((struct data*)pArgs)->end;
   
   pthread_cond_signal(&((struct data*)pArgs)->semaphore);//produz
   
   pthread_mutex_unlock(&((struct data*)pArgs)->mutex);
   
   char password [10];
   for(initial; initial < end; initial++) {
      // printf("t_id - %d Alvo - %lld\n",id,initial);
      sprintf(password, "%lld", initial );
		if(strcmp(((struct data*)pArgs)->password,password) == 0) {
			printf("\033[37m Thread -\033[31m %d\033[37m Senha -\033[32m %lld\n",id, initial);
			exit(EXIT_SUCCESS);
		}
			
	}
}