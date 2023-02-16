#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef struct _queue_ Queue;

Queue *qCreate(int maxItens);

int qEnqueue(Queue *q, void *item);

void *qDequeue(Queue *q, void *item);

int qPromoteLast(Queue *q, int n);

int qPunishFirst(Queue *q, int n);

void *qFirst(Queue *q);

int qIsFull(Queue *q);

int qIsEmpty(Queue *q);

int qDestroy(Queue *q);

#endif
