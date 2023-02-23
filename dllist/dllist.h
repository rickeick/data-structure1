#ifndef _DLLIST_H_
#define _DLLIST_H_

typedef struct _dlnode_ DLNode;

typedef struct _dllist_ DLList;

DLList *dllCreate();

int dllInsertAsFirst(DLList *l, void *data);

int dllInsertAsLast(DLList *l, void *data);

void *dllRemoveSpec(DLList *l, void *key, int (*cmp)(void *, void *));

void *dllQuery(DLList *l, void *key, int (*cmp)(void *, void *));

void *dllGetFirst(DLList *l);

void *dllGetNext(DLList *l);

int dllClear(DLList *l, int (*myfree)(void *));

int dllDestroy(DLList *l);

#endif
