//
//  ReadersWriters.c
//  OS_Final Project
//
//  Created by Nguyen Le Khanh Ngoc on 19/12/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/timex.h>
#include <time.h>
#include "ReadersWriters.h"
#define DEFAULT 10000000
#define LIMIT 5
void gap() {
    struct timespec interval;
    interval.tv_sec = rand()%3;
    interval.tv_nsec = (rand()%100)*DEFAULT;
    nanosleep(&interval, NULL);
}

void reader(Semaphore *locks, int ID){
    for (int i = 0; i < LIMIT; ++i){
        sem_wait(locks->reader);
        sem_wait(locks->data);
        fprintf(stderr, "***\tReader <%d> is reading %d\n",ID, i);
        sem_post(locks->data);
    }
    exit(0);
}

void writer(Semaphore *locks, int ID){
    for (int i = 0; i < LIMIT; ++i){
        sem_wait(locks->data);
        fprintf(stderr, "Writer <%d> is writing %d\n",ID, i);
        sem_post(locks->data);
        sem_post(locks->reader);
        gap();                                      //Simulate activity
    }
}
