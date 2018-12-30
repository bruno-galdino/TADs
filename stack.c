
#include "stack.h"

static bool stackRealloc( stack_t *stack, size_t size );

stack_t *stackCreate( size_t size, size_t typeSize )
{
    stack_t *stack = malloc( sizeof( stack_t ) );
    
    if( stack )
    {
        stack->typeSize = typeSize;
        stack->data     = malloc( size * typeSize );
		stack->ptr      = stack->data;
        stack->end      = stack->data + size * typeSize;

        if( !stack->data )
        {
            free( stack );
            stack  = NULL;
        }
    }

    return stack;
}

void stackDestroy( stack_t *stack )
{
    free( stack->data );
    free( stack );
}

bool stackPush( stack_t *stack, void *data  )
{
    if( stack->ptr == stack->end )
    {
	    if( !stackRealloc( stack, 20)  )/*tenta adicionar espaço a pilha*/
        {
            return false;
        }
    }

	memcpy( stack->ptr, data, stack->typeSize );
	stack->ptr += stack->typeSize;
}

void *stackPop( stack_t *stack )
{
	if( stack->ptr == stack->data )
	{
		return NULL;
	}

	stack->ptr -= stack->typeSize;
    return stack->ptr;	
}

void *stackTop( stack_t *stack)
{
    return stack->ptr - stack->typeSize;
}
/*add size blocks to new elements*/
static bool stackRealloc( stack_t *stack, size_t size )
{
    byte  *ptr;
    size_t stackSize = stack->end - stack->data;
    size_t newSize   = stackSize + stack->typeSize * size;
    
    ptr = realloc( stack->data, newSize );

    if( ptr )
    {
        stack->data = ptr;
        stack->ptr  = ptr + stackSize;
        stack->end  = ptr + newSize;
    }

    return ptr != NULL;
}

bool stackIsEmpty( stack_t *stack )
{
    return stack->ptr == stack->data;
}

bool stackIsFull ( stack_t *stack )
{
    return stack->ptr == stack->end;
}