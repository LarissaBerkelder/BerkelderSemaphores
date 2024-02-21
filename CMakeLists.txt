cmake_minimum_required(VERSION 3.22)
project(BerkelderSemaphore C)

set(CMAKE_C_STANDARD 17)

include_directories(inc)

add_executable(BerkelderSemaphore src/main.c
        src/Queue.c
        inc/Queue.h
        src/CartLoader.c
        inc/CartLoader.h
        src/Logger.c
        inc/Logger.h
)

target_link_libraries(BerkelderSemaphore pthread)