/**
 * @file Queue
 * @brief Description
 * 
 * @author Larissa Berkelder
 * @date 19/02/2024
 */

#ifndef BERKELDERSEMAPHORE_QUEUE_H
#define BERKELDERSEMAPHORE_QUEUE_H

#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_GROUPS 50

typedef struct {
    pthread_t thread;
    sem_t mutex;
    int count;
    bool group;
    void (*add)(void *queue);
    void (*remove)(void *queue);
    int (*getCount)(void *queue);
} QueueInterface;

typedef struct {
    QueueInterface interface;
    int turnsWaiting;
} SingleQueue;

typedef struct {
    QueueInterface interface;
    int groupSize[MAX_GROUPS];
    bool smallGroups;
} GroupQueue;

typedef struct {
    QueueInterface interface;
} FrontRowQueue;

// Interface functions
void QueueAdd(void *queue);
void QueueRemove(void *queue);
int QueueGetCount(void *queue);

// Initialize functions
void singleQueue_init(SingleQueue *singleQueue);
void groupQueue_init(GroupQueue *groupQueue, bool smallGroups);
void frontRowQueue_init(FrontRowQueue *frontRowQueue);

// Semaphore functions
void queue_sem_create(void *queue);
void queue_sem_destroy(void *queue);

// Group queue function
bool addGroup(GroupQueue *groupQueue);
void removeGroup(GroupQueue *groupQueue);

#endif //BERKELDERSEMAPHORE_QUEUE_H
