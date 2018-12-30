
#include <stdio.h>
#include <math.h>

#include "linked_list.h"

void func( void *n )
{
    *(int*)n *= 2;
}

void show( void *n )
{
    printf("%2d ",*(int*)n);
}

int main(int argc, char const *argv[])
{
    list_t *list = listCreate( );
    int *ptr;

    for( int i = 0 ; i < 10; i++ )
    {
        ptr = malloc( sizeof(int) );
        if(ptr) *ptr = i;
        listInsert( list, 0, ptr );
    }

    listForEach( list, show );
    listForEach( list, func );
    putchar('\n');
    listForEach( list, show );

    return 0;
}