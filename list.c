#include "list.h"
#include <stdlib.h>

void listInit(List** list) {
    *list = (List*)malloc(sizeof(List));
    if (!list) {
        perror("malloc");
        exit(1);
    }
    (*list)->size = 0;
    (*list)->head = NULL;
}

void listInsert(List* list, void* data) {
    if (!data || !list) return;

    ListElem* elem = (ListElem*) malloc(sizeof(ListElem));
    if (!elem) {
        perror("malloc");
        exit(1);
    }
    elem->data = data;
    elem->next = list->head;
    list->head = elem;
    list->size++;
}

ListElem* listFind(List* list, const void* data, ListCmp cmp) {
    if (!list) return NULL;
    
    ListElem* it = list->head;
    while(it != NULL) {
        if (cmp(data, it->data) == 0) {
            return it;
        }
        it = it->next;
    }
    return NULL;
}

ListElem* listDeleteElem(List* list, const void* data, ListCmp cmp) {
    if (!list) return NULL;
    ;
    // TODO
}

void listFree(List* list) {
    if (!list) return;
    ListElem* it = list->head;
    ListElem* tmp;
    while(it != NULL) {
        tmp = it->next;
        free(it->data);
        free(it);
        it = tmp;
    }
    free(list);
}

void listPrintAll(List *list, ListPrint prt) {
    if (!list) return;
    ListElem* it = list->head;
    while(it != NULL) {
        prt(it->data);
        it = it->next;
    }
} 