#ifndef _CQUEUE_H_
#define _CQUEUE_H_

int incCirc(int i, int max);

int decCirc(int i, int max);

typedef struct _cqueue_ CQueue;

CQueue *cqCreate(int maxItens);

int cqEnqueue(CQueue *cq, void *item);

void *cqDequeue(CQueue *q, void *item);

int cqPromoteLast(CQueue *cq, int n);

int cqPunishFirst(CQueue *cq, int n);

void *cqFirst(CQueue *cq);

int cqIsFull(CQueue *cq);

int cqIsEmpty(CQueue *cq);

int cqDestroy(CQueue *q);

#endif
