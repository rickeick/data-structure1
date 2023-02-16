#ifndef _COLLECTION_C_
#define _COLLECTION_C_
#include <malloc.h>
#include "collection.h"
#define FALSE 0
#define TRUE 1

typedef struct _collection_ {
	int numItens;
	int maxItens;
	int *item;
} Collection;

Collection *colCreate(int maxItens) {
	Collection *c;
	if (maxItens > 0) {
		c = (Collection*)malloc(sizeof(Collection));
		if (c != NULL) {
			c->item = (int*)malloc(sizeof(int)*maxItens);
			if (c->item != NULL) {
				c->maxItens = maxItens;
				c->numItens = 0;
				return c;
			}
			free(c);
		}
	}
	return NULL;
}

int colInsert(Collection *c, int item) {
	if (c != NULL) {
		if (c->numItens < c->maxItens) {
			c->item[c->numItens] = item;
			c->numItens++;
			return TRUE;
		}
	}
	return FALSE;
}

int colRemove(Collection *c, int key) {
	int i, j, status, aux;
	if (c != NULL) {
		if (c->numItens > 0) {
			i=0, status=FALSE;
			while (i < c->maxItens && status != TRUE) {
				if (c->item[i] == key) {
					status = TRUE;
				}
				else {
					i++;
				}
			}
			if (status == TRUE) {
				c->numItens--;
				aux = c->item[i];
				for (j=i; j<c->numItens; j++) {
					c->item[j] = c->item[j+1];
				}
				return aux;
			}
		}
	}
	return -32767;
}

int colQuery(Collection *c, int key) {
	int i, status;
	if (c != NULL) {
		if (c->numItens > 0) {
			i=0, status=FALSE;
			while (i < c->maxItens && status != TRUE) {
				if (c->item[i] == key) {
					status = TRUE;
				}
				else {
					i++;
				}
			}
			if (status == TRUE) {
				return TRUE;
			}
		}
	}
	return FALSE;
}

int colDestroy(Collection *c) {
	if (c != NULL) {
		if (c->numItens == 0) {
			free(c->item);
			free(c);
			return TRUE;
		}
	}
	return FALSE;
}

#endif
