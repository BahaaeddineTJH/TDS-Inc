#include <err.h>
#include <stdlib.h>
#include "shared_queue.h"

shared_queue* shared_queue_new()
{
    shared_queue* sq = malloc(sizeof(shared_queue));
    if (!sq)
        errx(1,"Couldn't allocate shared queue");
    if (sem_init(&sq->lock,0,1) == -1)
        errx(1,"Couldn't initialise semaphore");
    if (sem_init(&sq->size,0,0) == -1)
        errx(1,"Couldn't initialise semaphore");
    sq->queue = NULL;
    return sq;
}

void shared_queue_push(shared_queue* sq, int val)
{
    if (sem_wait(&sq->lock) == -1)
        errx(1,"Couldn't wait semaphore");
    sq->queue = queue_push(sq->queue,val);
    if (sem_post(&sq->lock) == -1)
        errx(1,"Couldn't post semaphore");
    if (sem_post(&sq->size) == -1)
        errx(1,"Couldn't post semaphore");
}

int shared_queue_pop(shared_queue* sq)
{
    if (sem_wait(&sq->size) == -1)
        errx(1,"Couldn't wait semaphore");

    int val;
    if (sem_wait(&sq->lock) == -1)
        errx(1,"Couldn't wait semaphore");
    sq->queue = queue_pop(sq->queue,&val);
    if (sem_post(&sq->lock) == -1)
        errx(1,"Couldn't post semaphore");
    return val;
}

void shared_queue_destroy(shared_queue* sq)
{
    queue_empty(&sq->queue);
    if (sem_destroy(&sq->size) == -1)
        errx(1,"Couldn't destroy semaphore");
    if (sem_destroy(&sq->lock) == -1)
        errx(1,"Couldn't destroy semaphore");
    free(sq);
}