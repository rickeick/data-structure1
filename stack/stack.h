#ifndef __STACK_H_
#define __STACK_H_

typedef struct _stack_ Stack;

Stack *stkCreate(int maxItens);

int stkPush(Stack *stk, void *item);

void *stkPop(Stack *stk);

void *stkTop(Stack *stk);

int stkIsFull(Stack *stk);

int stkIsEmpty(Stack *stk);

int stkDestroy(Stack *stk);

#endif
