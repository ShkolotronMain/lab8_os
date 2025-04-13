#pragma once

typedef struct node
{
    int page_num;
    struct node* next;
    int timer;
} node;

typedef struct stack
{
    node* head;
    int count;
    node* tail;
} stack;

// Создаёт пустой стек
stack* create_stack();

// Ищет и возвращает индекс нужной страницы относительно головы
int search_page_index( stack* src, int number);

// Добавляет элемент в стек
void add_node( stack* src, int number);

// Удаляет элемент из стека и возвращает его значение
int del_node( stack* src, int number);

// Удаляет верхний элемент стека и возвращает его значение
int pop( stack* src);

// Удаляет стек
void del_stack( stack* src);

// Удаляет нижний элемент стека и возвращает его значение 
int pop_last( stack* src);

// Создаёт элемент и загружает в него номер страницы
 node* new_node(int number);
