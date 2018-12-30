
#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef char byte;

typedef struct
{
    byte  *data;
    byte  *ptr;
    byte  *end;

    size_t typeSize;
    
} stack_t;

stack_t    *stackCreate ( size_t size, size_t typeSize );
void        stackDestroy( stack_t *stack );
bool        stackPush   ( stack_t *stack, void *data  );/*cria uma cópia do dado apontado por data e a guarda na pilha*/
void       *stackPop    ( stack_t *stack );
void       *stackTop    ( stack_t *stack);
bool        stackIsEmpty( stack_t *stack );
bool        stackIsFull ( stack_t *stack );

#define STACK( type, size )  stackCreate( size , sizeof(type) )

#endif