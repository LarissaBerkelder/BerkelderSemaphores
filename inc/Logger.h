/**
 * @file Logger
 * @brief Description
 * 
 * @author Larissa Berkelder
 * @date 19/02/2024
 */

#ifndef BERKELDERSEMAPHORE_LOGGER_H
#define BERKELDERSEMAPHORE_LOGGER_H

#include <stdio.h>

void print_queue_counters(const char* moment, const char* queueType, int count);
void log_cart_distribution(const char* queueType, int numOfRiders, int row);

#endif //BERKELDERSEMAPHORE_LOGGER_H
