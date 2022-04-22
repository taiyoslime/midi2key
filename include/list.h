#ifndef M2K_LIST_H
#define M2K_LIST_H

#include <stddef.h>


typedef struct list_elem {
    void *data;
    struct list_elem *next;
} ListElem;

typedef struct list {
  ListElem *head;
  size_t size;
} List;


typedef int (*ListCmp)(const void *a, const void *b);
typedef void (*ListPrint)(const void *data);

void listInit(List** list);
void listInsert(List* list, void* data);
ListElem* listFind(List* list, const void* data, ListCmp cmp);
ListElem* listDeleteElem(List* list, const void* data, ListCmp cmp);
void listFree(List* list);
void listPrintAll(List *list, ListPrint prt);

#endif