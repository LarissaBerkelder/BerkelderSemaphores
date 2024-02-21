/**
 * @file CartLoader
 * @brief Description
 * 
 * @author Larissa Berkelder
 * @date 19/02/2024
 */

#include "../inc/CartLoader.h"

void cart_init(Cart *cart, SingleQueue *singleQueue, GroupQueue  *groupQueue, FrontRowQueue *frontRowQueue){
    cart->capacity = CART_CAPACITY;
    cart->singleQueue = singleQueue;
    cart->groupQueue = groupQueue;
    cart->frontRowQueue = frontRowQueue;
}

void load(Cart *cart){
    // Check if there are people in the queue otherwise wait for people to join the queue
    wait(cart);

    // Bool to check if it is the single priority turn
    bool singlePriorityTurn = false;

    // Emtpy arrays
    for (int i = 0; i < CART_ROWS; ++i) {
        cart->seatsFilled[i] = 0;
        cart->singlesSeated[i] = 0;
    }

    // Check the front row queue first
    int waitingFrontQueue = QueueGetCount(cart->frontRowQueue);
    int countFrontRowAdded = 0;
    if(waitingFrontQueue > 0){
        while (cart->seatsFilled[0] < CART_CAPACITY  && QueueGetCount(cart->frontRowQueue) > 0){
            cart->seatsFilled[0]++;
            countFrontRowAdded++;
            QueueRemove(cart->frontRowQueue);
        }
    }
    if(countFrontRowAdded > 0) log_cart_distribution("FrontRowQueue", countFrontRowAdded, 0);

    // Check if people in the single queue have been waiting for two or more turns
    if(cart->singleQueue->turnsWaiting >= 2){
        for (int i = 0; i < CART_ROWS; ++i) {
            int availableSeats = cart->capacity - cart->seatsFilled[i];
            if(availableSeats > 0){
                loadSingle(cart, availableSeats, i);
            }
        }

        cart->singleQueue->turnsWaiting=0;
        singlePriorityTurn = true;
    }

    // Fill seats with groups
    for (int i = 0; i < CART_ROWS; ++i) {
        loadGroup(cart, i);
    }

    // Fill seats with single riders
    for (int i = 0; i < CART_ROWS; ++i) {
        int availableSeats = cart->capacity - cart->seatsFilled[i];
        if(availableSeats > 0){
            loadSingle(cart, availableSeats, i);
            // People from the single queue entered the cart so decrement the waiting turns (only if the waiting turns are not zero)
            if (cart->singleQueue->turnsWaiting > 0) cart->singleQueue->turnsWaiting--;
        }
        else if(availableSeats == 0 && !singlePriorityTurn)  {
            cart->singleQueue->turnsWaiting++;
        }
    }

    for (int i = 0; i < CART_ROWS; ++i){
        if(cart->singlesSeated[i] > 0) log_cart_distribution("SingleQueue", cart->singlesSeated[i], i);
    }
}

void wait(Cart *cart){
    // If there is no one in the queues wait
    while (QueueGetCount(cart->singleQueue) == 0 && QueueGetCount(cart->groupQueue) == 0) {
        usleep(100000);
    }
}


void loadSingle(Cart *cart, int availableSeats, int row){
    while (QueueGetCount(cart->singleQueue) > 0 && availableSeats > 0){
        //printf("Added someone from the single queue in row %d\n", row + 1);
        QueueRemove(cart->singleQueue);
        availableSeats--;
        cart->seatsFilled[row]++;
        cart->singlesSeated[row]++;
    }
}

void loadGroup(Cart *cart, int row){
    // Check the first three groups
    int groupsToProcess = QueueGetCount(cart->groupQueue) < 3 ? QueueGetCount(cart->groupQueue) : 3;
    int seated = 0;
    for (int i = 0; i < groupsToProcess; ++i) {
        if((cart->groupQueue->groupSize[i] + cart->seatsFilled[row]) <= cart->capacity){
            cart->seatsFilled[row] += cart->groupQueue->groupSize[i];
            seated += cart->groupQueue->groupSize[i];
            //log_cart_distribution("GroupQueue", cart->groupQueue->groupSize[i], row);
            QueueRemove(cart->groupQueue);
        }
    }
    if(seated > 0) log_cart_distribution("GroupQueue", seated, row);
}