#include <stdlib.h>
#include "stack.h"

struct node* new_node(int number)
{
    struct node* result = (struct node*)calloc(1, sizeof(struct node));

    result->page_num = number;

    return result;
}

struct stack* create_stack()
{
    // Выделяем место
    struct stack* result = (struct stack*)calloc(1, sizeof(struct stack));

    return result;
}

void add_node(struct stack* src, int number)
{
    struct node* _node = new_node(number);

    if (!src->count)
    {
        src->head = _node;
        src->count++;
        src->tail = _node;
    }
    else
    {
        _node->next = src->head;
        src->head = _node;
        src->count++;
    }
}

int search_page_index(struct stack* src, int number)
{
    int result = -1, running = 1;
    struct node* _node = src->head;
    for (int i=0; i<src->count && running; i++)
    {
        if (_node->page_num == number)
        {
            result = i;
            running = 0;
        }
        else
        {
            _node = _node->next;
        }
    }

    return result;
}

int del_node(struct stack* src, int number)
{
    struct node* _node = src->head;
    struct node* node_ = NULL;
    int running = 1;
    int result = 0;
    for (int i=0; i<src->count && running; i++)
    {
        if (_node->page_num == number-1)
        {
            node_ = _node->next;
            _node->next = node_->next;
            result = node_->page_num;
            free(node_);
            src->count -= 1;
            running = 0;
        }
        else
        {
            _node = _node->next;
        }
    }
    return result;
}

int pop(struct stack* src)
{
    if (src->count-1)
    {
        struct node* head_prev = src->head;
        src->head = src->head->next;
        int res = head_prev->page_num;
        free(head_prev);
        src->count -= 1;
        return res;
    }
    else
    {
        int res = src->head->page_num;
        src->count = 0;
        free(src->head);
        src->head = NULL;
        src->tail = NULL;
        return res;
    }
}

int pop_last(struct stack* src)
{
    struct node* _node = src->head;
    int result = src->tail->page_num;
    if (src->count-1)
    {
        while (_node->next != src->tail)
            _node = _node->next;
        _node->next = NULL;
        free(src->tail);
        src->tail = _node;
        src->count--;
    }
    else
        result = pop(src);
    return result;
}

void del_stack(struct stack* src)
{
    while(src->count)
    {
        pop(src);
    }
    free(src);
}