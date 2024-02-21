#include <stdio.h>

#include "../inc/Queue.h"
#include "../inc/CartLoader.h"
#include "../inc/Logger.h"

SingleQueue singleQueue;
GroupQueue groupQueue;
FrontRowQueue frontRowQueue;
Cart cart;

// Default timers for the thread functions
int singleQueueJoinTimer = 2;
int groupQueueJoinTimer = 2;
int frontQueueJoinTimer = 2;
int cartLeaveTimer = 10;

// Default group size (small)
int smallGroups = 0;

// Thread functions
void *singleThread(void *arg);
void *groupThread(void *arg);
void *frontThread(void *arg);
void *cartThread(void *arg);


int main() {
    // Initializing the queues
    singleQueue_init(&singleQueue);
    groupQueue_init(&groupQueue, smallGroups);
    frontRowQueue_init(&frontRowQueue);

    // Initialize the cart loader
    cart_init(&cart, &singleQueue, &groupQueue, &frontRowQueue);

    // Creating the threads
    pthread_create(&singleQueue.interface.thread, NULL, singleThread, &singleQueue);
    pthread_create(&groupQueue.interface.thread, NULL, groupThread, &groupQueue);
    pthread_create(&frontRowQueue.interface.thread, NULL, frontThread, &frontRowQueue);
    pthread_create(&cart.thread, NULL, cartThread, &cart);

    // Joining the threads
    pthread_join(singleQueue.interface.thread, NULL);
    pthread_join(groupQueue.interface.thread, NULL);
    pthread_join(frontRowQueue.interface.thread, NULL);
    pthread_join(cart.thread, NULL);

    // Destroying the semaphores
    queue_sem_destroy(&singleQueue);
    queue_sem_destroy(&groupQueue);
    queue_sem_destroy(&frontRowQueue);

    return 0;
}


void *singleThread(void *arg) {
    SingleQueue *q = (SingleQueue *)arg;
    while (1) {
        q->interface.add(q);
        sleep(singleQueueJoinTimer);
    }
}

void *groupThread(void *arg) {
    GroupQueue *q = (GroupQueue *)arg;
    while (1) {
        q->interface.add(q);
        sleep(groupQueueJoinTimer);
    }
}

void *frontThread(void *arg){
    FrontRowQueue *q = (FrontRowQueue *)arg;
    while (1){
        q->interface.add(q);
        sleep(frontQueueJoinTimer);
    }
}

void *cartThread(void *arg){
    Cart *cart = (Cart *)arg;
    while (1) {
        printf("<\n");
        print_queue_counters("A", "SingleQueue", QueueGetCount(cart->singleQueue));
        print_queue_counters("A", "GroupQueue", QueueGetCount(cart->groupQueue));
        print_queue_counters("A", "FrontRowQueue", QueueGetCount(cart->frontRowQueue));
        load(cart);
        print_queue_counters("L", "SingleQueue", QueueGetCount(cart->singleQueue));
        print_queue_counters("L", "GroupQueue", QueueGetCount(cart->groupQueue));
        print_queue_counters("L", "FrontRowQueue", QueueGetCount(cart->frontRowQueue));
        printf(">\n\n");
        sleep(cartLeaveTimer);
    }
}