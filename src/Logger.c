/**
 * @file Logger
 * @brief Description
 * 
 * @author Larissa Berkelder
 * @date 19/02/2024
 */

#include "../inc/Logger.h"

void print_queue_counters(const char* moment, const char* queueType, int count){
    printf("%s|%s|%d\n", moment, queueType, count);
}

void log_cart_distribution(const char* queueType, int numOfRiders, int row){
    printf("%s,%d,%d\n", queueType, numOfRiders, row + 1);
}


// stdbuf -oL ./BerkelderSemaphore > /mnt/c/Users/laris/OneDrive/Bureaublad/OperatingSystems2/Assignments/VisualizeData/test1.txt