//
//  ReadersWriters.h
//  OS_Final Project
//
//  Created by Nguyen Le Khanh Ngoc on 19/12/2020.
//

#ifndef ReadersWriters_h
#define ReadersWriters_h
#include <stdio.h>
#include <semaphore.h>
void gap(void);
typedef struct {
    sem_t *data;
    sem_t *reader;
} Semaphore;
void reader (Semaphore *locks, int ID);
void writer (Semaphore *locks, int ID);
#endif /* ReadersWriters_h */
