#ifndef _ABSTRAX_LINKED_LIST
#define _ABSTRAX_LINKED_LIST 1
#include <abstrax/baseobject.h>
#include <abstrax/traits/iterable.h>

struct list_node{
    void *value;
    size_t value_size;
    struct list_node *next, *prev;
};

// I used doubly linked-list here.
struct list{
    struct list_node *head;
    struct list_node *tail;
    size_t cached_size; // this variable is affected when calling: list_init, insert or delete operations.
};

struct ReturnValue list_init(void *head_value, size_t head_size);
void list_deinit(struct list *instance);

void list_insert(struct list *instance, size_t at, void *value, size_t value_size);
void list_append(struct list *instance, void *value, size_t value_size);
void list_prepend(struct list *instance, void *value, size_t value_size);

void list_pop(struct list *instance, size_t at);
void list_pop_back(struct list *instance);
void list_pop_front(struct list *instance);

size_t list_size(struct list *instance);
enum ErrorCode list_update(struct list *instance, size_t at, void *value, size_t value_size);
void *list_get(struct list *instance, size_t at);
#endif