struct node
{
    int page_num;
    struct node* next;
};

struct stack
{
    struct node* head;
    int count;
    struct node* tail;
};

// Создаёт пустой стек
struct stack* create_stack();

// Ищет и возвращает индекс нужной страницы относительно головы
int search_page_index(struct stack* src, int number);

// Добавляет элемент в стек
void add_node(struct stack* src, int number);

// Удаляет элемент из стека и возвращает его значение
int del_node(struct stack* src, int number);

// Удаляет верхний элемент стека и возвращает его значение
int pop(struct stack* src);

// Удаляет стек
void del_stack(struct stack* src);

// Удаляет нижний элемент стека и возвращает его значение 
int pop_last(struct stack* src);

// Создаёт элемент и загружает в него номер страницы
struct node* new_node(int number);
