#ifndef _QUEUE_C_
#define _QUEUE_C_

#include <stdlib.h>
#include "queue.h"

#define FALSE 0
#define TRUE 1

typedef struct _queue_ {
    int rear;
    int maxItens;
    void **item;
} Queue;

Queue *qCreate(int maxItens) {
    Queue *q;
    if (maxItens > 0) {
        q = (Queue*)malloc(sizeof(Queue));
        if (q != NULL) {
            q->item = (void**)malloc(sizeof(void*)*maxItens);
            if (q->item != NULL) {
                q->maxItens = maxItens;
                q->rear = -1;
                return q;
            }
            free(q);
        }
    }
    return NULL;
}

int qEnqueue(Queue *q, void *item) {
    if (q != NULL) {
        if (q->rear < q->maxItens-1) {
            q->rear++;
            q->item[q->rear] = item;
            return TRUE;
        }
    }
    return FALSE;
}

void *qDequeue(Queue *q, void *item) {
    void *aux; int cur, next;
    if (q != NULL) {
        if (q->rear > 0) {
            aux = q->item[0];
            for (int i=0; i<q->rear; i++) {
                cur = i; next = i+1;
                q->item[cur] = q->item[next];
            }
            q->rear--;
            return aux;
        }
    }
    return NULL;
}

int qPromoteLast(Queue *q, int n) {
    void *aux; int moves, cur;
    if (q != NULL && n > 0) {
        if (q->rear > 0) {
            aux = q->item[q->rear];
            if (n < q->rear) {
                moves = n;
            }
            else {
                moves = q->rear;
            }
            cur = q->rear;
            for (int i=moves; i>0; i--) {
                q->item[cur] = q->item[cur-1]; cur--;
            }
            q->item[cur] = aux;
            return TRUE;
        }
    }
    return FALSE;
}

int qPunishFirst(Queue *q, int n) {
    void *aux; int moves, cur, next;
    if (q != NULL && n > 0) {
        if (q->rear > 0) {
            aux = q->item[0];
            if (n < q->rear) {
                moves = n;
            }
            else {
                moves = q->rear;
            }
            for (int i=0; i<moves; i++) {
                cur = i; next = i+1;
                q->item[cur] = q->item[next];
            }
            q->item[moves] = aux;
            return TRUE;
        }
    }
    return FALSE;
}

void *qFirst(Queue *q) {
    if (q != NULL) {
        if (q->rear > 0) {
            return q->item[0];
        }
    }
    return NULL;
}

int qIsFull(Queue *q) {
    if (q != NULL) {
        if (q->rear >= q->maxItens-1) {
            return TRUE;
        }
    }
    return FALSE;
}

int qIsEmpty(Queue *q) {
    if (q != NULL) {
        if (q->rear < 0) {
            return TRUE;
        }
    }
    return FALSE;
}

int qDestroy(Queue *q) {
    if (q != NULL) {
        if (q->rear < 0) {
            free(q->item);
            free(q);
            return TRUE;
        }
    }
    return FALSE;
}

#endif
