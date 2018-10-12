/*
  CSC464 Assignment 1
  Producer Consumer Classical Problem in C

  Thor Reite V00809409
  10/11/2018
*/

#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t consumer_cond, producer_cond;

void* producer(void *ptr);
void* consumer(void *ptr);

int item_buffer = 0; //tracks items in buffer

int main(){
  pthread_t tproducer;
  pthread_t tconsumer;
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&producer_cond, NULL);
  pthread_cond_init(&consumer_cond, NULL);

  pthread_create(&tproducer, NULL, producer, NULL);
  pthread_create(&tconsumer, NULL, consumer, NULL);

  pthread_join(tproducer, NULL);
  pthread_join(tconsumer, NULL);

  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&producer_cond);
  pthread_cond_destroy(&consumer_cond);
}

void* producer(void *ptr){
  int i;
  for(i=1; i<=1000; i++){
    pthread_mutex_lock(&mutex); //lock item buffer
    while(item_buffer) pthread_cond_wait(&producer_cond, &mutex); //wait while items in buffer
    item_buffer = i;
    pthread_cond_signal(&consumer_cond);
    pthread_mutex_unlock(&mutex);
  }
  pthread_exit(0);
}

void* consumer(void *ptr){
  int i;
  for(i=1; i<=1000; i++){
    pthread_mutex_lock(&mutex); //lock item buffer
    while(!item_buffer) pthread_cond_wait(&consumer_cond, &mutex); //wait while buffer is empty
    item_buffer = 0;
    pthread_cond_signal(&producer_cond);
    pthread_mutex_unlock(&mutex);
  }
  pthread_exit(0);
}
