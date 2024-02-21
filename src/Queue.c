/**
 * @file Queue
 * @brief Description
 * 
 * @author Larissa Berkelder
 * @date 19/02/2024
 */

#include "../inc/Queue.h"

void QueueAdd(void *queue) {
    QueueInterface *qi = (QueueInterface *)queue;
    sem_wait(&qi->mutex);
    if(qi->group){
        if(addGroup(queue)) qi->count++;
    }else qi->count++;
    sem_post(&qi->mutex);
}

void QueueRemove(void *queue) {
    QueueInterface *qi = (QueueInterface *)queue;
    sem_wait(&qi->mutex);
    if(qi->count > 0) {
        if(qi->group) removeGroup(queue);
        qi->count--;
    }
    sem_post(&qi->mutex);
}

int QueueGetCount(void *queue) {
    QueueInterface *qi = (QueueInterface *)queue;
    sem_wait(&qi->mutex);
    int count = qi->count;
    sem_post(&qi->mutex);
    return count;
}

void singleQueue_init(SingleQueue *singleQueue){
    singleQueue->interface.count = 0;
    singleQueue->interface.group = false;
    singleQueue->interface.add = QueueAdd;
    singleQueue->interface.remove = QueueRemove;
    singleQueue->interface.getCount = QueueGetCount;
    singleQueue->turnsWaiting = 0;
    queue_sem_create(singleQueue);
}

void groupQueue_init(GroupQueue *groupQueue, bool smallGroups){
    groupQueue->interface.count = 0;
    groupQueue->interface.group = true;
    groupQueue->interface.add = QueueAdd;
    groupQueue->interface.remove = QueueRemove;
    groupQueue->interface.getCount = QueueGetCount;
    groupQueue->smallGroups = smallGroups;
    queue_sem_create(groupQueue);
}

void frontRowQueue_init(FrontRowQueue *frontRowQueue){
    frontRowQueue->interface.count = 0;
    frontRowQueue->interface.group = false;
    frontRowQueue->interface.add = QueueAdd;
    frontRowQueue->interface.remove = QueueRemove;
    frontRowQueue->interface.getCount = QueueGetCount;
    queue_sem_create(frontRowQueue);
}

void queue_sem_create(void *queue){
    QueueInterface *qi = (QueueInterface *)queue;
    sem_init(&qi->mutex, 0, 1);
}

void queue_sem_destroy(void *queue){
    QueueInterface *qi = (QueueInterface *)queue;
    sem_destroy(&qi->mutex);
}

bool addGroup(GroupQueue *groupQueue){
    int groupSize;
    if(groupQueue->smallGroups){
        groupSize = (rand() % 2) + 2;
    } else {
        groupSize = (rand() % 4) + 2;
    }
    if(groupQueue->interface.count < MAX_GROUPS){
        groupQueue->groupSize[groupQueue->interface.count] = groupSize;
    }else {
        printf("Group queue is full. Cannot add more groups.\n");
        return false;
    }
    return true;
}

void removeGroup(GroupQueue *groupQueue){
    for (int i = 0; i < groupQueue->interface.count - 1; i++) {
        groupQueue->groupSize[i] = groupQueue->groupSize[i + 1];
    }
}
