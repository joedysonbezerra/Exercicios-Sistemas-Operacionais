#include <stdio.h>
#include <pthread.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>

void *identifiesLetter();
void *identifiesNumber();
void binaryLock();

struct criticalRegion {
   char string[100];
   int lock;
};


int main(int argc, char **argv) {
   struct criticalRegion data = {"",0};
   pthread_t threads[2];

   strcpy(data.string,argv[1]);

   pthread_create(&threads[0], NULL, identifiesLetter, &data);
   pthread_create(&threads[1], NULL, identifiesNumber, &data);
   
   for(int i = 0; i < 2; i++) pthread_join(threads[i], NULL);
  // printf("\n%s",data.string);
   return 0;
   
}

void *identifiesLetter(struct criticalRegion *pData) {
   FILE *letter;
   letter = fopen("string.txt", "w");
  
   if(letter == NULL) {
      printf("Erro na abertura do arquivo!");
      pthread_exit(0);
   }

   binaryLock(isalpha,pData,letter,"\033[34m");

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

   binaryLock(isdigit,pData,number,"\033[32m");
 
   fclose(number);
   pthread_exit(0);
};


void binaryLock (int (*function)(char), struct criticalRegion *pData, FILE *arq, char cor[]){
   int i = 0;
   while(pData->string[i] != '\0') {
      if(pData->lock == 0) {
         pData->lock = 1;
         if(function(pData->string[i])) {
            fprintf(arq, "%c", pData->string[i]);
            pData->string[i] = ' ';
         }
         pData->lock = 0;
         usleep(20000);
         ++i;
      } else {
         printf("\033[31m Esperando %s %p\033[31m  desbloquear a variavel\n",cor,arq);
      }
   }
}