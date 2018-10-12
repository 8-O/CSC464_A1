/*
  CSC464 Assignment 1
  Readers Writers Classical Problem in C

  Thor Reite V00809409
  10/11/2018
*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sema_r, sema_w;

void* reader(void *ptr);
void* writer(void *ptr);

int content = 0; //content to read and write
int num_readers = 0;

int main(){
  pthread_t treader[10];
  pthread_t twriter[10];
  sem_init(&sema_r, 0, 5);
  sem_init(&sema_w, 0, 1);

  int i;
  for(i=0; i<10; i++){
    pthread_create(&treader[i], NULL, reader, (void*)i);
    pthread_create(&twriter[i], NULL, writer, (void*)i);
  }
  for(i=0; i<10; i++){
    pthread_join(treader[i], NULL);
    pthread_join(twriter[i], NULL);
  }

  sem_destroy(&sema_r);
  sem_destroy(&sema_w);
}

void* reader(void *ptr){
  int i = ((int)ptr);
  sem_wait(&sema_r);
  num_readers++;
  if(num_readers == 1) sem_wait(&sema_w); //only first reader needs
                                          //  to claim write lock
  printf("Reader %d read content value %d.\n", i, content);
  num_readers--;
  if(num_readers == 0) sem_post(&sema_w); //can write if 0 readers
  sem_post(&sema_r);
  pthread_exit(0);
}

void* writer(void *ptr){
  int i = ((int)ptr);
  sem_wait(&sema_w);
  sem_wait(&sema_r);
  content++;
  printf("Writer %d wrote content value %d.\n", i, content);
  sem_post(&sema_w);
  sem_post(&sema_r);
  pthread_exit(0);
}
