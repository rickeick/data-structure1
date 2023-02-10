#ifndef _GCOLLECTION_H_
#define _GCOLLECTION_H_

typedef struct _gcollection_ GCollection;

GCollection *gcolCreate(int maxItens);

int gcolInsert(GCollection *gc, void *item);

void *gcolRemove(GCollection *gc, void *key, int (*cmp)(void *, void*));

void *gcolQuery(GCollection *gc, void *key, int (*cmp)(void *, void*));

void *gcolGetFirst(GCollection *gc);

void *gcolGetNext(GCollection *gc);

int gcolDestroy(GCollection *gc);

#endif
