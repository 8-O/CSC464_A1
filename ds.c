/*
  CSC464 Assignment 1
  Dining Savages Classical Problem in C

  Thor Reite V00809409
  10/11/2018
*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

void* savage(void *ptr);
void* cook(void *ptr);

pthread_cond_t restock_food, consume_food;
pthread_t tsavage[10];
pthread_t tcook;
sem_t eating;
pthread_mutex_t mutex, print_mutex;

int servings = 5;

int main(){
  sem_init(&eating, 0, 1);
  pthread_mutex_init(&mutex, NULL);
  pthread_mutex_init(&print_mutex, NULL);
  pthread_cond_init(&restock_food, NULL);
  pthread_cond_init(&consume_food, NULL);

  int i;
  for(i=0; i<10; i++){
    pthread_create(&tsavage[i], NULL, savage, (void*)i);
  }
  pthread_create(&tcook, NULL, cook, (void*)i);
  for(i=0; i<10; i++){
    pthread_join(tsavage[i], NULL);
  }
  pthread_join(tcook, NULL);
  sem_destroy(&eating);
  pthread_mutex_destroy(&mutex);
  pthread_mutex_destroy(&print_mutex);
  pthread_cond_destroy(&restock_food);
  pthread_cond_destroy(&consume_food);
  return 0;
}

void* savage(void *ptr){
  int hungry = 1;
  int i = ((int)ptr);
  pthread_mutex_lock(&print_mutex);
  printf("Savage %d wants to eat.\n", i);
  pthread_mutex_unlock(&print_mutex);
  while(hungry){
    sem_wait(&eating);
    if(servings == 0){
      pthread_cond_signal(&restock_food);
      pthread_cond_wait(&consume_food, &mutex);
    }
    servings--;
    pthread_mutex_lock(&print_mutex);
    printf("Savage %d just ate and %d portions remain.\n", i, servings);
    pthread_mutex_unlock(&print_mutex);
    sem_post(&eating);
    sleep(1);
  }
  pthread_exit(0);
}

void* cook(void *ptr){
  int check_pot = 1;
  int i = ((int)ptr);
  while(check_pot){
    pthread_cond_wait(&restock_food, &mutex);
    servings = 10;
    printf("Cook filled the pot with %d portions.\n", servings);
    pthread_cond_signal(&consume_food);
  }
  pthread_exit(0);
}
