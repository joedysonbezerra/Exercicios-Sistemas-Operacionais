#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <unistd.h>

#define NUMBER_THREADS 5

void *life();
void think();
void eat();

pthread_mutex_t mutexFork[NUMBER_THREADS] = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char **argv) {
   pthread_t philosophers[NUMBER_THREADS];
   int i;
   for(i = 0; i < NUMBER_THREADS; i++) pthread_create(&philosophers[i], NULL, life,(void*)(intptr_t)i);

   for(i = 0; i < NUMBER_THREADS; i++) pthread_join(philosophers[i],NULL);

}

void *life(void *arg) {
   const int id = (int)(intptr_t)arg; 
   while (1) {
      eat(&id);
      think(&id);
   } 
}

void eat(int *id) {

   int left = *id;
   int right = (*id + 1) % NUMBER_THREADS;

      pthread_mutex_lock(&mutexFork[left]);
      pthread_mutex_lock(&mutexFork[right]);
      
      printf("\033[32mFilosófos - %d Comendo ...\n", *id);
      sleep(3);
      
      printf("\033[33mFilosófos - %d Parou de Comer\n", *id);
      pthread_mutex_unlock(&mutexFork[left]);
      pthread_mutex_unlock(&mutexFork[right]);

   
}

void think(int *id) {
   printf("\033[37mFilosófos - %d Pensando ...\n", *id);
   sleep(1);
}