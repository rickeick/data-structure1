#ifndef _SLLIST_C_
#define _SLLIST_C_

#include <stdlib.h>
#include "sllist.h"

#define FALSE 0
#define TRUE 1

typedef struct _sllist_ {
    SLNode *first;
} SLList;

typedef struct _slnode_ {
    void *data;
    SLNode *next;
} SLNode;

SLList *sllCreate() {
    SLList *l;
    l = (SLList *)malloc(sizeof(SLList));
    if (l != NULL) {
        l->first = NULL;
        return l;
    }
    return NULL;
}

int sllInsertAsFirst(SLList *l, void *data) {
    SLNode *newnode;
    if (l != NULL) {
        newnode = (SLNode *)malloc(sizeof(SLNode));
        if (newnode != NULL) {
            newnode->data = data;
            newnode->next = l->first;
            l->first = newnode;
            return TRUE;
        }
    }
    return FALSE;
}

int sllInsertAsLast(SLList *l, void *data) {
    SLNode *last, *newnode;
    if (l != NULL) {
        newnode = (SLNode *)malloc(sizeof(SLNode));
        if (newnode != NULL) {
            if (l->first != NULL) {
                last = l->first;
                while (last->next != NULL) {
                    last = last->next;
                }
                last->next = newnode;
            }
            else {
                l->first = newnode;
            }
            newnode->data = data;
            newnode->next = NULL;
            return TRUE;
        }
    }
    return FALSE;
}

int sllInsertAfterSpec(SLList *l, void *data, void *key, int (*cmp)(void *, void *)) {
    SLNode *spec, *newnode; int stat;
    if (l != NULL) {
        if (l->first != NULL) {
            spec = l->first;
            stat = cmp(key, spec->data);
            while (stat != TRUE && spec->next != NULL) {
                spec = spec->next;
                stat = cmp(key, spec->data);
            }
            if (stat == TRUE) {
                newnode = (SLNode *)malloc(sizeof(SLNode));
                if (newnode != NULL) {
                    newnode->data = data;
                    newnode->next = spec->next;
                    spec->next = newnode;
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

int sllInsertBeforeSpec(SLList *l, void *data, void *key, int (*cmp)(void *, void *)) {
    SLNode *prev, *spec, *newnode; int stat;
    if (l != NULL) {
        if (l->first != NULL) {
            prev = NULL;
            spec = l->first;
            stat = cmp(key, spec->data);
            while (stat != TRUE && spec->next != NULL) {
                prev = spec;
                spec = spec->next;
                stat = cmp(key, spec->data);
            }
            if (stat == TRUE) {
                newnode = (SLNode *)malloc(sizeof(SLNode));
                if (newnode != NULL) {
                    newnode->data = data;
                    newnode->next = spec;
                    if (prev != NULL) {
                        prev->next = newnode;
                    }
                    else {
                        l->first = newnode;
                    }
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

void *sllRemoveFirst(SLList *l) {
    SLNode *first; void *data;
    if (l != NULL) {
        if (l->first != NULL) {
            first = l->first;
            data = first->data;
            l->first = first->next;
            free(first);
            return data;
        }
    }
    return NULL;
}

void *sllRemoveLast(SLList *l) {
    SLNode *prim, *prev, *last; void* data;
    if (l != NULL) {
        if (l->first != NULL) {
            prev = NULL;
            last = l->first;
            while (last->next != NULL) {
                prev = last;
                last = last->next;
            }
            data = last->data;
            if (prev != NULL) {
                prev->next = NULL;
            }
            else {
                l->first = NULL;
            }
            free(last);
            return data;
        }
    }
    return NULL;
}

void *sllRemoveAfterSpec(SLList *l, void *key, int (*cmp)(void *, void *)) {
    SLNode *next, *spec; void *data; int stat;
    if (l != NULL) {
        if (l->first != NULL) {
            spec = l->first;
            stat = cmp(key, spec->data);
            while (stat != TRUE && spec->next != NULL) {
                spec = spec->next;
                stat = cmp(key, spec->data);
            }
            if (stat == TRUE) {
                next = spec->next;
                if (next != NULL) {
                    data = next->data;
                    spec->next = next->next;
                    free(next);
                    return data;
                }
            }
        }
    }
    return NULL;
}

void *sllRemoveBeforeSpec(SLList *l, void *key, int (*cmp)(void *, void *)) {
    SLNode *prev2, *prev1, *spec; void *data; int stat;
    if (l != NULL) {
        if (l->first != NULL) {
            prev2 = NULL;
            prev1 = NULL;
            spec = l->first;
            stat = cmp(key, spec->data);
            while (stat != TRUE && spec->next != NULL) {
                prev2 = prev1;
                prev1 = spec;
                spec = spec->next;
                stat = cmp(key, spec->data);
            }
            if (stat == TRUE) {
                data = prev1->data;
                if (prev1 != NULL) {
                    if (prev2 != NULL) {
                        prev2->next = prev1->next;
                    }
                    else {
                        l->first = prev1->next;
                    }
                    free(prev1);
                    return data;
                }
            }
        }
    }
    return NULL;
}

int sllGetNumNodes(SLList *l) {
    SLNode *last; int i=0;
    if (l != NULL) {
        if (l->first != NULL) {
            last = l->first;
            while (last->next != NULL) {
                last = last->next; i++;
            }
        }
        return i;
    }
    return -1;
}

int sllIsEmpty(SLList *l) {
    if (l != NULL) {
        if (l->first == NULL) {
            return TRUE;
        }
    }
    return FALSE;
}

int sllDestroy(SLList *l) {
    if (l != NULL) {
        if (l->first == NULL) {
            free(l);
            return TRUE;
        }
    }
    return FALSE;
}

#endif
