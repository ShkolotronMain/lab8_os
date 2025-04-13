#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int max(const int* seq, const int len)
{
    int res = 0;
    for (int i=0; i<len; i++)
        if (seq[i]>seq[res])
            res = i;
    return res;    
}

void fifo(const int* req, const int cnt, const int size, int* rewrites)
{
    // Создаём стек-нестек
    stack* s = create_stack();

    // Обрабатываем запросы к памяти
    for (int i=0; i<cnt; i++)
    {
        // Ищем страницу
        int k = search_page_index(s, req[i]);

        // Если страницы в памяти нет
        if (k == -1)
        {
            // Если есть свободное место
            if (s->count < size)
            {
                add_node(s, req[i]);
                printf("[%d] В пустую ячейку памяти добавлена страница %d\n", i, req[i]);
            }
            // Если места нет
            else
            {
                printf("[%d] Из памяти удалена страница %d\n", i, pop_last(s));
                add_node(s, req[i]);
                printf("[%d] В пустую ячейку памяти добавлена страница %d\n", i, req[i]);
                *rewrites += 1;
            }
        }
        // Если страница есть
        else
        {
            printf("[%d] Страница %d найдена в ячейке %d\n", i, req[i], k);
        }
    }

    // Заканчиваем работу алгоритма
    del_stack(s);
}

void opt(const int* req, const int cnt, const int size, int* rewrites)
{
    // Создаём стек-нестек
    stack* s = create_stack();

    // Обрабатываем запросы к памяти
    for (int i=0; i<cnt; i++)
    {
        // Ищем страницу
        const int k = search_page_index(s, req[i]);

        // Если страницы в памяти нет
        if (k == -1)
        {
            // Если есть свободное место
            if (s->count < size)
            {
                add_node(s, req[i]);
                printf("[%d] В пустую ячейку памяти добавлена страница %d\n", i, req[i]);
            }
            // Если места нет
            else
            {
                int* pages = (int*)calloc(size, sizeof(int));
                int* indexes = (int*)calloc(size, sizeof(int));
                int p = 0;
                node* _node_ = s->head;

                // Заносим искомые номера в массив номеров страниц
                do
                {
                    pages[p] = _node_->page_num;
                    _node_ = _node_->next;
                    p++;
                } while(_node_);

                // Ищем самую "забытую"
                for (int g=i+1; g<cnt; g++)
                {
                    for (int l=0; l<size; l++)
                    {
                        // Если в существующих страницах есть та, которая будет в будущем
                        if (req[i] == pages[l] && !indexes[l])
                        {
                            indexes[l] = i;
                        }
                    }
                }

                p = max(indexes, size);
                p = pages[p];
                
                del_node(s, p);
                printf("[%d] Из памяти удалена страница %d\n", i, p);
                add_node(s, req[i]);
                printf("[%d] В пустую ячейку памяти добавлена страница %d\n", i, req[i]);

                free(pages);
                free(indexes);

                *rewrites += 1;
            }
        }
        // Если страница есть
        else
        {
            printf("[%d] Страница %d найдена в ячейке %d\n", i, req[i], k);
        }
    }

    // Заканчиваем работу алгоритма
    del_stack(s);
}

void lru(const int* req, const int cnt, const int size, int* rewrites)
{
    // Создаём стек-нестек
    stack* s = create_stack();

    // Обрабатываем запросы к памяти
    for (int i=0; i<cnt; i++)
    {
        // Ищем страницу
        const int k = search_page_index(s, req[i]);

        // Если страницы в памяти нет
        if (k == -1)
        {
            // Если есть свободное место
            if (s->count < size)
            {
                add_node(s, req[i]);
                printf("[%d] В пустую ячейку памяти добавлена страница %d\n", i, req[i]);
            }
            // Если места нет
            else
            {
                int* pages = (int*)calloc(size, sizeof(int)); // номера страниц в памяти
                int* timers = (int*)calloc(size, sizeof(int)); // таймеры с теми же индексами
                int p = 0;
                node* _node_ = s->head;

                // Заносим искомые номера в массив номеров страниц
                do
                {
                    pages[p] = _node_->page_num;
                    timers[p] = _node_->timer;
                    _node_ = _node_->next;
                    p++;
                } while(_node_);

                // Ищем самую неиспользуемую
                p = max(timers, size);

                p = pages[p];
                
                del_node(s, p);
                printf("[%d] Из памяти удалена страница %d\n", i, p);
                add_node(s, req[i]);
                printf("[%d] В пустую ячейку памяти добавлена страница %d\n", i, req[i]);

                free(pages);
                free(timers);

                *rewrites += 1;
            }
        }
        // Если страница есть
        else
        {
            printf("[%d] Страница %d найдена в ячейке %d\n", i, req[i], k);
            node* node_ = s->head;
            while(node_->page_num != req[i])
            {
                node_ = node_->next;
            } 
            node_->timer = -1;
        }

        // Добавляем всему списку время на таймер
        // FIXME: пофиксить циклический список на 7 итерации
        node* _node_ = s->head;
        do
        {
            _node_->timer++;
            _node_ = _node_->next;
        } while(_node_);
    }

    // Заканчиваем работу алгоритма
    del_stack(s);
}

int main()
{
    // Макс будет рад xD
    const int requests[] = {9, 5, 5, 7, 5, 6, 5, 4, 9, 5, 6, 2, 7, 7, 3, 5, 1, 2, 5, 1};
    const int count = 20;
    const int buffer_size = 4;

    // Количество перезаписей (ошибок отсутствия страницы)
    int rewrites = 0;

    fifo(requests, count, buffer_size, &rewrites);
    printf("Алгоритм FIFO для %d блоков страниц даёт %d перезаписей\n", buffer_size, rewrites);
    rewrites = 0;

    printf("\n");

    opt(requests, count, buffer_size, &rewrites);
    printf("Алгоритм OPT для %d блоков страниц даёт %d перезаписей\n", buffer_size, rewrites);
    rewrites = 0;

    printf("\n");

    lru(requests, count, buffer_size, &rewrites);
    printf("Алгоритм LRU для %d блоков страниц даёт %d перезаписей\n", buffer_size, rewrites);

    return 0;
}