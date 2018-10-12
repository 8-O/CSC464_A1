/*
  CSC464 Assignment 1
  Dining Philosophers Classical Problem in C

  Thor Reite V00809409
  10/11/2018
*/

#include <stdio.h>
#include <pthread.h>

void* philosopher(void *ptr);

pthread_t tphilosopher[5];
pthread_mutex_t mutex[5];

int main(){
  int i;
  for(i=0; i<5; i++){
    pthread_mutex_init(&mutex[i], NULL);
  }
  for(i=0; i<5; i++){
    pthread_create(&tphilosopher[i], NULL, philosopher, (void*)i);
  }
  for(i=0; i<5; i++){
    pthread_join(tphilosopher[i], NULL);
  }
  for(i=0; i<5; i++){
    pthread_mutex_destroy(&mutex[i]);
  }
  return 0;
}

void* philosopher(void *ptr){
  int i = ((int)ptr);
  printf("Philosopher %d wants to eat.\n", i);
  pthread_mutex_lock(&mutex[i]);
  pthread_mutex_lock(&mutex[(i+1)%5]);
  printf("Philosopher %d is eating with forks %d and %d.\n", i, i, (i+1)%5);
  sleep(1);
  pthread_mutex_unlock(&mutex[i]);
  pthread_mutex_unlock(&mutex[(i+1)%5]);
  printf("Philosopher %d is done eating.\n", i);
  pthread_exit(0);
}
