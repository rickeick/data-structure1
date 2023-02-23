#ifndef _DLLIST_C_
#define _DLLIST_C_
#include <malloc.h>
#include "dllist.h"
#define FALSE 0
#define TRUE 1

typedef struct _dlnode_ {
	void *data;
	DLNode *prev;
	DLNode *next;
} DLNode;

typedef struct _dllist_ {
	DLNode *first;
	DLNode *cur;
} DLList;


DLList *dllCreate() {
	DLList *l;
	l = (DLList *)malloc(sizeof(DLList));
	if (l != NULL) {
		l->first = NULL;
		l->cur = NULL;
		return l;
	}
	return NULL;
}

int dllInsertAsFirst(DLList *l, void *data) {
	DLNode *newnode;
	if (l != NULL) {
		newnode = (DLNode *)malloc(sizeof(DLNode));
		if (newnode != NULL) {
			newnode->data = data;
			newnode->prev = NULL;
			newnode->next = l->first;
			if (l->first != NULL) {
				l->first->prev = newnode;
			}
			l->first = newnode;
			return TRUE;
		}
	}
	return FALSE;
}

int dllInsertAsLast(DLList *l, void *data) {
	DLNode *newnode, *last = NULL;
	if (l != NULL) {
		newnode = (DLNode *)malloc(sizeof(DLNode));
		if (newnode != NULL) {
			if (l->first != NULL) {
				last = l->first;
				while (last->next != NULL) {
					last = last->next;
				}
			}
			newnode->data = data;
			newnode->prev = last;
			newnode->next = NULL;
			if (last != NULL) {
				last->next = newnode;
			}
			else {
				l->first = newnode;
			}
			return TRUE;
		}
	}
	return FALSE;
}

void *dllRemoveSpec(DLList *l, void *key, int (*cmp)(void *, void *)) {
	DLNode *prevnode, *spec, *nextnode; void *data; int stat;
	if (l != NULL) {
		if (l->first != NULL) {
			spec = l->first;
			stat = cmp(key, spec->data);
			while (spec->next != NULL && stat != TRUE) {
				spec = spec->next;
				stat = cmp(key, spec->data);
			}
			if (stat == TRUE) {
				data = spec->data;
				prevnode = spec->prev;
				nextnode = spec->next;
				if (prevnode != NULL) {
					prevnode->next = nextnode;
				}
				else {
					l->first = nextnode;
				}
				if (nextnode != NULL) {
					nextnode->prev = prevnode;
				}
				free(spec);
				return data;
			}
		}
	}
}

void *dllQuery(DLList *l, void *key, int (*cmp)(void *, void *)) {
	DLNode *spec; int stat;
	if (l != NULL) {
		if (l->first != NULL) {
			spec = l->first;
			stat = cmp(key, spec->data);
			while (spec->next != NULL && stat != TRUE) {
				spec = spec->next;
				stat = cmp(key, spec->data);
			}
			if (stat == TRUE) {
				return spec->data;
			}
		}
	}
	return NULL;
}

void *dllGetFirst(DLList *l) {
	if (l != NULL) {
		if (l->first != NULL) {
			l->cur = l->first;
			return l->cur->data;
		}
	}
	return NULL;
}

void *dllGetNext(DLList *l) {
	if (l != NULL) {
		if (l->cur != NULL) {
			l->cur = l->cur->next;
			if (l->cur != NULL) {
				return l->cur->data;
			}
		}
	}
	return NULL;
}

int dllClear(DLList *l, int (*myfree)(void *)) {
	DLNode *cur, *prev;
	if (l != NULL) {
		if (l->first != NULL) {
			cur = l->first;
			while (cur != NULL) {
				prev = cur;
				cur = cur->next;
				myfree(prev->data);
				free(prev);
			}
			l->first = NULL;
			return TRUE;
		}
	}
	return FALSE;
}

int dllDestroy(DLList *l) {
	if (l != NULL) {
		if (l->first == NULL) {
			free(l);
			return TRUE;
		}
	}
	return FALSE;
}

#endif
