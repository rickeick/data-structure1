#ifndef _GCOLLECTION_C_
#define _GCOLLECTION_C_
#include <malloc.h>
#include "gcollection.h"
#define FALSE 0
#define TRUE 1

typedef struct _gcollection_ {
	int cur;
	int numItens;
	int maxItens;
	void **item;
} GCollection;

GCollection *gcolCreate(int maxItens) {
	GCollection *gc;
	if (maxItens > 0) {
		gc = (GCollection*)malloc(sizeof(GCollection));
		if (gc != NULL) {
			gc->item = (void **) malloc (sizeof(void *)*maxItens);
			if (gc->item != NULL) {
				gc->maxItens = maxItens;
				gc->numItens = 0;
				gc-> cur = -1;
				return gc;
			}
			free(gc);
		}
	}
	return NULL;
}

int gcolInsert(GCollection *gc, void *item) {
	if (gc != NULL) {
		if (gc->numItens < gc->maxItens) {
			gc->item[gc->numItens] = item;
			gc->numItens++;
			return TRUE;
		}
	}
	return FALSE;
}

void *gcolRemove(GCollection *gc, void *key, int (*cmp)(void*, void*)) {
	void *aux; int stat, i;
	if (gc != NULL) {
		if (gc->numItens > 0) {
			for (i=0; i<gc->numItens; i++) {
				stat = cmp(key, gc->item[i]);
				if (stat == TRUE) {break;}
			}
			if (stat == TRUE) {
				aux = gc->item[i];
				for (int j=i; j < gc->numItens; j++) {
					gc->item[j] = gc->item[j+1];
				}
				gc->numItens--;
				return aux;
			}
		}
	}
	return NULL;
}

void *gcolQuery(GCollection *gc, void *key, int (*cmp)(void *, void*)) {
	int stat, i;
	if (gc != NULL) {
		if (gc->numItens > 0) {
			for (i=0; i<gc->numItens; i++) {
				stat = cmp(key, gc->item[i]);
				if (stat == TRUE) {break;}
			}
			if (stat == TRUE) {
				return gc->item[i];
			}
		}
	}
	return NULL;
}

void *gcolGetFirst(GCollection *gc) {
	void *elm;
	if (gc != NULL) {
		if (gc->numItens > 0) {
			elm = gc->item[0];
			gc->cur = 0;
			return elm;
		}
	}
	return NULL;
}

void *gcolGetNext(GCollection *gc) {
	void *elm;
	if (gc != NULL) {
		if (gc->numItens > 0 && gc->cur < gc->numItens-1) {
			gc->cur++;
			elm = gc->item[gc->cur];
			return elm;
		}
	}
	return NULL;
}

int gcolDestroy(GCollection *gc) {
	if (gc != NULL) {
		if (gc->numItens == 0) {
			free(gc->item);
			free(gc);
			return TRUE;
		}
	}
	return FALSE;
}

#endif
