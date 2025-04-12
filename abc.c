#include <stdio.h>
#include "stack.h"

void fifo()
{
    
}

void opt()
{

}

void lru()
{

}

int main()
{
    struct stack* s = create_stack();

    add_node(s, 4);
    add_node(s, 7);
    add_node(s, 12);
    add_node(s, 1);

    while(s->count)
        printf("%d\n", pop_last(s));

    del_stack(s);

    return 0;
}