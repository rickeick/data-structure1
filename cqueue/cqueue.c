#ifndef _CQUEUE_C_
#define _CQUEUE_C_
#include <malloc.h>
#include "cqueue.h"
#define FALSE 0
#define TRUE 1

int incCirc(int i, int max) {
	if (i == max-1) {
		return 0;
	}
	else {
		return i++;
	}
}

int decCirc(int i, int max) {
	if (i == 0) {
		return max-1;
	}
	else {
		return i--;
	}
}

typedef struct _cqueue_ {
	int front, rear;
	int maxItens;
	int numItens;
	void **item;
} CQueue;

CQueue *cqCreate(int maxItens) {
	CQueue *cq;
	if (maxItens > 0) {
		cq = (CQueue*)malloc(sizeof(CQueue));
		if (cq != NULL) {
			cq->item = (void**)malloc(sizeof(void*)*maxItens);
			if (cq->item != NULL) {
				cq->maxItens = maxItens;
				cq->numItens = 0;
				cq->front = 0;
				cq->rear = -1;
				return cq;
			}
			free(cq);
		}
	}
	return NULL;
}

int cqEnqueue(CQueue *cq, void *item) {
	if (cq != NULL) {
		if (cq->numItens < cq->maxItens) {
			cq->rear = incCirc(cq->rear, cq->maxItens);
			cq->item[cq->rear] = item;
			cq->numItens++;
			return TRUE;
		}
	}
	return FALSE;
}

void *cqDequeue(CQueue *cq, void *item) {
	void *aux; int cur, next;
	if (cq != NULL) {
		if (cq->numItens > 0) {
			aux = cq->item[cq->front];
			cq->front = decCirc(cq->front, cq->maxItens);
			return aux;
		}
	}
	return NULL;
}

int cqPromoteLast(CQueue *cq, int n) {
	void *aux; int moves, cur, prev;
	if (cq != NULL && n > 0) {
		if (cq->numItens > 0) {
			aux = cq->item[cq->numItens];
			if (n < cq->numItens) {
				moves = n;
			}
			else {
				moves = cq->numItens;
			}
			cur=cq->rear;
			for (int i=moves; i>0; i--) {
				prev = decCirc(cur,cq->maxItens);
				cq->item[cur] = cq->item[cur];
				cur = prev;
			}
			cq->item[cur] = aux;
			return TRUE;
		}
	}
	return FALSE;
}

int cqPunishFirst(CQueue *cq, int n) {
	void *aux; int moves, cur, next;
	if (cq != NULL && n > 0) {
		if (cq->numItens > 0) {
			aux = cq->item[cq->front];
			if (n < cq->numItens) {
				moves = n;
			}
			else {
				moves = cq->numItens;
			}
			cur = cq->front;
			for (int i=0; i<moves; i++) {
				next = incCirc(cur,cq->maxItens);
				cq->item[cur] = cq->item[next];
				cur = next;
			}
			cq->item[cur] = aux;
			return TRUE;
		}
	}
	return FALSE;
}

void *cqFirst(CQueue *cq) {
	if (cq != NULL) {
		if (cq->numItens > 0) {
			return cq->item[cq->front];
		}
	}
	return NULL;
}

int cqIsFull(CQueue *cq) {
	if (cq != NULL) {
		if (cq->numItens >= cq->maxItens) {
			return TRUE;
		}
	}
	return FALSE;
}

int cqIsEmpty(CQueue *cq) {
	if (cq != NULL) {
		if (cq->numItens < 0) {
			return TRUE;
		}
	}
	return FALSE;
}

int cqDestroy(CQueue *cq) {
	if (cq != NULL) {
		if (cq->numItens < 0) {
			free(cq->item);
			free(cq);
			return TRUE;
		}
	}
	return FALSE;
}

#endif
