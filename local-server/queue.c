#include <err.h>
#include <stdlib.h>
#include "queue.h"

queue* queue_push(queue* start, int val)
{
    queue* q = malloc(sizeof(queue));
    if (!q)
        errx(1,"Couldn't allocate new queue");
    q->val = val;
    q->next = q;
    if (start)
        q->next = start->next;
    return q;
}

queue* queue_pop(queue* start, int *pval)
{
    queue* q = start;
    while (q->next){
        if (q->next == q)
            break;
        q = q->next;
    }
    if (pval)
        *pval = q->val;
    if (q != q->next)
        start->next = q->next;
    else
        start = NULL;
    free(q);
    return start;
}

void queue_empty(queue** pstart)
{
    queue* cur = *pstart;
    while (cur){
        cur = queue_pop(cur,NULL);
    }
    *pstart = cur;
}