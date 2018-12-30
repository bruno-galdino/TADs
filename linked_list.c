
#include "linked_list.h"

struct node_t
{
    void          *data;/*pointer to store user data*/
    node_t *next;
    node_t *prev;

};

struct list_t
{
    node_t *first;
    node_t *last;

    size_t len;

};

node_t *nodeCreate( void )
{
    return malloc( sizeof(node_t) );
}

void nodeDestroy( list_t *list, node_t *node, void (*freeData)( void *data ) )
{

    if( node == list->first )
    {
        if( node == list->last )
        {
            list->first = list->last = NULL;
        }
        else
        {
            node->next->prev  = NULL;
            list->first       = node->next;
        }
        
    }
    else if( node == list->last )
    {
        node->prev->next = NULL;
        list->last       = node->prev;
    }
    else
    {
        node->next->prev = node->prev;
        node->prev->next = node->next;
    }

    if( freeData )
    {
        freeData(node->data);
    }

    free(node);
    list->len--;
}

node_t *nodeGetByIndex( list_t *list, size_t index )
{
    node_t *node;

    if( index == 0 )
    {
        return list->first;
    }
    else if( index >= list->len - 1 )
    {
        return list->last;
    }
    
    node = list->first;
    
    while( index-- )
    {
        node  = node->next;
    }

    return node;
}

list_t *listCreate( void )
{
    return calloc( sizeof(list_t), 1 );
}

void listDestroy( list_t *list, void (*freeData)( void *data )  )
{
    listRemoveAll( list, freeData );
    free(list);
}

node_t *listInsert( list_t *list, size_t index, void *data)
{
    node_t *newNode  = nodeCreate( );
    node_t *curNode  = list->first;

    if( newNode )
    {
        if( list->len == 0 )
        {
            list->first   = list->last = newNode;
            newNode->next = newNode->prev = NULL;
        }
        else if( index == 0 )
        {
            newNode->next  = list->first;
            newNode->prev  = NULL;
            list->first    = list->first ? list->first->prev = newNode: newNode;
        }
        else if( index >= list->len )
        {
            newNode->next = NULL;
            newNode->prev = list->last;
            list->last    = list->last->next = newNode;
        }
        else
        {
            curNode = nodeGetByIndex( list, index );

            newNode->next = curNode;
            newNode->prev = curNode->prev;
            curNode->prev = newNode->prev->next = newNode;
        }
        
        newNode->data = data;
        list->len++;
    }

    return newNode;
}

node_t *listInsertFront( list_t *list, void *data )
{
    return listInsert( list, 0, data );
}

node_t *listInsertBack( list_t *list, void *data )
{
    return listInsert( list, -1, data );
}

void listRemove( list_t *list, size_t index, void (*freeData)( void *data ) )
{
    node_t *node = list->first;

    if( list->len )
    {
        if( index >= list->len )
        {   
            node = list->last;
        }
        else
        {
            node = nodeGetByIndex( list, index );
        }

        nodeDestroy( list, node, freeData );
    }
}

void listRemoveAll( list_t *list, void (*freeData)( void *data ) )
{
    node_t *node  = list->first;
    node_t *aux;

    if( freeData )
    {
        while( node )
        {
            aux  = node;
            node = node->next;

            freeData(aux->data);
            free(aux);
        }
    }
    else
    {
        while( node )
        {
            aux  = node;
            node = node->next;

            free(aux);
        }        
    }

    list->first = list->last = NULL;
    list->len   = 0;
}

void listRemoveFront( list_t *list, void (*freeData)( void *data ) )
{
    nodeDestroy( list, list->first, freeData);
}

void listRemoveBack( list_t *list, void (*freeData)( void *data ) )
{
    nodeDestroy( list, list->last, freeData);
}

void listRemoveKey( list_t *list, void *key, bool (*cmpFunc)( void *test, void *key ), void (*freeData)( void *data ) )
{
    node_t *node = list->first;

    while( node )
    {
        if( cmpFunc( node->data, key ) )
        {
            nodeDestroy( list, node, freeData );
            break;
        }

        node = node->next;
    }
}

void listRemovekeyAll( list_t *list, void *key, bool (*cmpFunc)( void *test, void *key ), void (*freeData)( void *data ) )
{
    node_t *node = list->first;
    node_t *aux;

    while( node )
    {
        aux = node;
        node = node->next;

        if( cmpFunc( aux->data, key ) )
        {
            nodeDestroy( list, aux, freeData );
        }

        
    }
}

size_t listIndex( list_t *list, void *key, bool (*cmpFunc)( void *test, void *key ) )
{
    node_t *node = list->first;
    size_t index = 0;

    while( node )
    {   
        
        if( cmpFunc( node->data, key ) )
        {
            return index;
        }

        node = node->next;
        index++;
    }

    return -1;
}

size_t listCount( list_t *list, void *key, bool (*cmpFunc)( void *test, void *key ) )
{
    node_t *node = list->first;
    size_t count = 0;

    while( node )
    {   
        if( cmpFunc( node->data, key ) )
        {
            count++;
        }

        node = node->next;
    }

    return count;
}

/*
void listSort( list_t *list, int (*cmpFunc)( void *test, void *key ) );
*/

node_t *listGetNode( list_t *list, size_t index )
{
    return nodeGetByIndex( list, index );
}

void *listGetData( list_t *list, size_t index )
{
    return nodeGetByIndex( list, index )->data;
}

void listSetData( list_t *list, size_t index, void *data )
{
    nodeGetByIndex( list, index )->data = data;
}

void listForEach( list_t *list, void (*func)( void *data) )
{
    node_t *node = list->first;

    while( node )
    {
        func( node->data );
        node = node->next;
    }

}