/**
 * @file CartLoader
 * @brief Description
 * 
 * @author Larissa Berkelder
 * @date 19/02/2024
 */

#ifndef BERKELDERSEMAPHORE_CARTLOADER_H
#define BERKELDERSEMAPHORE_CARTLOADER_H

#include "Queue.h"
#include "../inc/Logger.h"

#define CART_CAPACITY 6
#define CART_ROWS 3

typedef struct {
    int capacity;
    int seatsFilled[CART_ROWS];
    int singlesSeated[CART_ROWS];
    pthread_t thread;
    SingleQueue *singleQueue;
    GroupQueue  *groupQueue;
    FrontRowQueue *frontRowQueue;
} Cart;

void cart_init(Cart *cart, SingleQueue *singleQueue, GroupQueue  *groupQueue, FrontRowQueue *frontRowQueue);
void load(Cart *cart);
void wait(Cart *cart);
void loadSingle(Cart *cart, int availableSeats, int row);
void loadGroup(Cart *cart, int row);

#endif //BERKELDERSEMAPHORE_CARTLOADER_H
