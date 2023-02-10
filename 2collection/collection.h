// Rick Eick Vieira Dos Santos
#ifndef _COLLECTION_H_
#define _COLLECTION_H_

typedef struct _collection_ Collection;

Collection *colCreate(int maxItens);

int colInsert(Collection *c, int item);

int colRemove(Collection *c, int key);

int colQuery(Collection *c, int key);

int colDestroy(Collection *c);

#endif
