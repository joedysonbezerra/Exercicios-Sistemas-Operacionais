#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>

void *identifiesLetter();
void *identifiesNumber();
void split();

struct criticalRegion {
   char string[100];
   pthread_mutex_t mutex;
};


int main(int argc, char **argv) {
   struct criticalRegion data;
   pthread_t threads[2];

   strcpy(data.string,argv[1]);
   pthread_mutex_init(&data.mutex,NULL);

   pthread_create(&threads[0], NULL, identifiesLetter, &data);
   pthread_create(&threads[1], NULL, identifiesNumber, &data);

   for(int i = 0; i < 2; i++) pthread_join(threads[i], NULL);
  // printf("\n%s",data.string);
   return EXIT_SUCCESS;

}

void *identifiesLetter(struct criticalRegion *pData) {
   FILE *letter;
   letter = fopen("string.txt", "w");

   if(letter == NULL) {
      printf("Erro na abertura do arquivo!");
      pthread_exit(0);
   }

   split(isalpha,pData,letter,"\033[34m");

   fclose(letter);
   pthread_exit(0);

};
void *identifiesNumber(struct criticalRegion *pData) {
   FILE *number;
   number = fopen("number.txt", "w");

   if(number == NULL) {
      printf("Erro na abertura do arquivo!");
      pthread_exit(0);
   }

   split(isdigit,pData,number,"\033[32m");

   fclose(number);
   pthread_exit(0);
};


void split (int (*function)(char), struct criticalRegion *pData, FILE *arq, char cor[]){
   int i = 0;
   while(pData->string[i] != '\0') {
      pthread_mutex_lock(&pData->mutex);
      if(function(pData->string[i])) {
         fprintf(arq, "%c", pData->string[i]);
         pData->string[i] = ' ';
      }
      pthread_mutex_unlock(&pData->mutex);
      //usleep(20000);
      ++i;

   }
}
