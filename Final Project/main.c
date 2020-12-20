//
//  main.c
//  OS_Final Project
//
//  Created by Nguyen Le Khanh Ngoc on 19/12/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "ReadersWriters.h"
/*sem_t mutex;
sem_t *m;
#define mutex *m
sem_t db;
sem_t *d;
#define db *d
int readercount=0;
pthread_t reader1,reader2,writer1,writer2;
void *Reader(void *p);
void *Writer(void *p);
*/
int main(int argc, const char * argv[]) {
    
    /*m = sem_open("Mutex", O_CREAT, 0644, 1);
    d = sem_open("DB",O_CREAT, 0644, 1);
    while(1)
    {
        pthread_create(&reader1,NULL,Reader,"1");
        pthread_create(&reader2,NULL,Reader,"2");
        pthread_create(&writer1,NULL,Writer,"1");
        pthread_create(&writer2,NULL,Writer,"2");
    }*/
    Semaphore s;
    sem_unlink("Test 1");
    sem_unlink("Test 2");
    //O_CREATE: create if not existant, must also give the rwx bits (mode) for the file
    //S_IRUSR: read permission: owner
    //S_IWUSR: write permission: owner
    s.data = sem_open("Test 1", O_CREAT, S_IRUSR | S_IWUSR, 0);
    s.reader = sem_open("Test 2", O_CREAT, S_IRUSR | S_IWUSR, 0);
    
    //Initial opening: unlock a semaphore
    sem_post(s.data);
    
    srand(time(NULL));
    
    pid_t pid = fork();
    if (pid == 0){
        reader(&s, 1);
    } else {
        pid = fork();
        if (pid == 0){
            writer(&s, 1);
        } else {
            pid = fork();
            if (pid == 0){
                reader(&s, 2);
            } else {
                writer(&s, 2);
            }
            sleep (5);
            sem_close(s.reader);
            sem_close(s.data);
        }
    }
    return 0;
}
/*
void *Reader(void *p)
{
    //printf("previous value %dn",mutex);
    sem_wait(&mutex);
    printf("Mutex acquired by reader %d\n",mutex);
    readercount++;
    if(readercount==1) sem_wait(&db);
    sem_post(&mutex);
    printf("Mutex returned by reader %d\n",mutex);
    printf("Reader %s is Reading\n",p);
    sleep(3);
    sem_wait(&mutex);
    printf("Reader %s Completed Reading\n",p);
    readercount--;
    if(readercount==0) sem_post(&db);
    sem_post(&mutex);
    return NULL;
}

void *Writer(void *p)
{
    printf("Writer is Waiting\n");
    sem_wait(&db);
    printf("Writer %s is writing\n ",p);
    sem_post(&db);
    sleep(2);
    return NULL;
}*/
