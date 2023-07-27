#ifndef _STACK_C_
#define _STACK_C_

#include <stdlib.h>
#include "stack.h"

#define FALSE 0
#define TRUE 1

typedef struct _stack_ {
    int top;
    int maxItens;
    void **item;
} Stack;

Stack *stkCreate(int maxItens) {
    Stack *stk;
    if (maxItens > 0) {
        stk = (Stack*)malloc(sizeof(Stack));
        if (stk != NULL) {
            stk->item = (void**)malloc(sizeof(void*)*maxItens);
            if (stk->item != NULL) {
                stk->maxItens = maxItens;
                stk->top = -1;
                return stk;
            }
            free(stk);
        }
    }
    return NULL;
}

int stkPush(Stack *stk, void *item) {
    if (stk != NULL) {
        if (stk->top < stk->maxItens-1) {
            stk->top++;
            stk->item[stk->top] = item;
            return TRUE;
        }
    }
    return FALSE;
}

void *stkPop(Stack *stk) {
    void *aux;
    if (stk != NULL) {
        if (stk->top >= 0) {
            aux = stk->item[stk->top];
            stk->top--;
            return aux;
        }
    }
    return NULL;
}

void *stkTop(Stack *stk) {
    if (stk != NULL) {
        if (stk->top >= 0) {
            return stk->item[stk->top];
        }
    }
    return NULL;
}

int stkIsFull(Stack *stk) {
    if (stk != NULL) {
        if (stk->top >= stk->maxItens-1) {
            return TRUE;
        }
    }
    return FALSE;
}

int stkIsEmpty(Stack *stk) {
    if (stk != NULL) {
        if (stk->top < 0) {
            return TRUE;
        }
    }
    return FALSE;
}

int stkDestroy(Stack *stk) {
    if (stk != NULL) {
        if (stk->top < 0) {
            free(stk->item);
            free(stk);
            return TRUE;
        }
    }
    return FALSE;
}

#endif
