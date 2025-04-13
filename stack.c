#include <stdlib.h>
#include "stack.h"

node* new_node(int number)
{
	node* result = (node*)calloc(1, sizeof(node));

	result->page_num = number;
	result->timer = -1;

	return result;
}

stack* create_stack()
{
	// Выделяем место
	stack* result = (stack*)calloc(1, sizeof(stack));

	return result;
}

void add_node(stack* src, int number)
{
	node* _node = new_node(number);

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

int search_page_index(stack* src, int number)
{
	int result = -1, running = 1;
	node* _node = src->head;
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

int del_node(stack* src, int number)
{
	node* _node = src->head;
	node* node_ = NULL; // предыдущий за _node элемент
	int result = -1;


	while (_node->page_num != number)
	{
		node_ = _node;
		_node = _node->next;
	}

	result = _node->page_num;
	node* tmp = _node->next;
	free(_node);
	if (_node != src->head)
	{
		node_->next = tmp;
		if (!tmp)
			src->tail = node_;
	}
	else
	{
    	src->head = tmp;
	}
	src->count--;

	return result;
}

int pop(stack* src)
{
	if (src->count-1)
	{
		node* head_prev = src->head;
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

int pop_last(stack* src)
{
	node* _node = src->head;
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

void del_stack(stack* src)
{
	while(src->count)
	{
		pop(src);
	}
	free(src);
}