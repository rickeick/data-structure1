#ifndef _SLLIST_H_
#define _SLLIST_H_

typedef struct _sllist_ SLList;

typedef struct _slnode_ SLNode;

SLList *sllCreate();

int sllInsertAsFirst(SLList *l, void *data);

int sllInsertAsLast(SLList *l, void *data);

int sllInsertAfterSpec(SLList *l, void *data, void *key, int (*cmp)(void *, void *));

int sllInsertBeforeSpec(SLList *l, void *data, void *key, int (*cmp)(void *, void *));

void *sllRemoveFirst(SLList *l);

void *sllRemoveLast(SLList *l);

void *sllRemoveAfterSpec(SLList *l, void *key, int (*cmp)(void *, void *));

void *sllRemoveBeforeSpec(SLList *l, void *key, int (*cmp)(void *, void *));

int sllGetNumNodes(SLList *l);

int sllIsEmpty(SLList *t);

int sllDestroy(SLList *l);

#endif
