
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct node_t node_t;
typedef struct list_t list_t;

node_t      *nodeCreate      ( void );
void         nodeDestroy     ( list_t *list, node_t *node, void (*freeData)( void *data ) );
node_t      *nodeGetByIndex  ( list_t *list, size_t index );
list_t      *listCreate      ( void );
void         listDestroy     ( list_t *list, void (*freeData)( void *data )  );/*freeData: função para aplicar na dealocação dos nós filhos*/
node_t      *listInsert      ( list_t *list, size_t index, void *data);
node_t      *listInsertFront ( list_t *list, void *data );
node_t      *listInsertBack  ( list_t *list, void *data );
void         listRemove      ( list_t *list, size_t index, void (freeData)( void *data ) );
void         listRemoveAll   ( list_t *list, void (*freeData)( void *data ) );
void         listRemoveFront ( list_t *list, void (*freeData)( void *data ) );
void         listRemoveBack  ( list_t *list, void (*freeData)( void *data ) );
void         listRemoveKey   ( list_t *list, void *key, bool (*cmpFunc)( void *test, void *key ), void (*freeData)( void *data ) );
void         listRemovekeyAll( list_t *list, void *key, bool (*cmpFunc)( void *test, void *key ), void (*freeData)( void *data ) );
size_t       listIndex       ( list_t *list, void *key, bool (*cmpFunc)( void *test, void *key ) );
size_t       listCount       ( list_t *list, void *key, bool (*cmpFunc)( void *test, void *key ) );
void         listSort        ( list_t *list, int (*cmpFunc)( void *test, void *key ) );
node_t      *listGetNode     ( list_t *list, size_t index );
void        *listGetData     ( list_t *list, size_t index );
void         listSetData     ( list_t *list, size_t index, void *data );
void         listForEach     ( list_t *list, void (*func)( void *data) );

#endif