#include <abstrax/dsa/list.h>
#include <string.h>

struct list_node *allocate_node(void *head_value, size_t head_size){
    struct list_node *node = malloc(sizeof(struct list_node));
    if(node != NULL){
        node->value = malloc(head_size);
        if(node->value == NULL){
            free(node);
            return NULL;
        }
        memcpy(node->value, head_value, head_size);
        node->value_size = head_size;
        node->prev = NULL;
        node->next = NULL;
        return node;
    }
    return node;
}

struct ReturnValue list_init(void *head_value, size_t head_size){
    struct ReturnValue retval;
    SET_RETURN_OK(retval);
    retval.err = Ok;
    retval.value = malloc(sizeof(struct list));
    struct list *ref_list = (struct list*)retval.value;

    if(ref_list == NULL){
        SET_RETURN_NULL(retval);
        retval.err = OutOfMemory;
        retval.value = NULL;
        return retval;
    }
    ref_list->cached_size = 1;
    ref_list->head = allocate_node(head_value, head_size);
    
    if(ref_list->head == NULL){
        free(ref_list);
        SET_RETURN_NULL(retval);
        retval.err = OutOfMemory;
        retval.value = NULL;
        return retval;
    }

    ref_list->tail = ref_list->head;
    return retval;
}

void list_deinit(struct list *instance){
    struct list_node *current = instance->head;
    while(current != NULL){
        struct list_node *temporary = current->next;
        free(current->value);
        free(current);
        current = temporary;
    }
    free(instance);
    instance = NULL;
}

void list_append(struct list *instance, void *value, size_t value_size) {
    if (instance == NULL) {
        return;
    }
    list_insert(instance, list_size(instance), value, value_size);
}

void list_prepend(struct list *instance, void *value, size_t value_size) {
    if (instance == NULL) {
        return;
    }
    list_insert(instance, 0, value, value_size);
}

void list_insert(struct list *instance, size_t at, void *value, size_t value_size){
    if (instance == NULL || at > list_size(instance)) {
        return;
    }

    struct list_node *new_node = allocate_node(value, value_size);
    if (new_node == NULL)
        return;

    if (instance->head == NULL) {
        instance->head = new_node;
        instance->tail = new_node;
    } else if (at == list_size(instance)) {
        new_node->prev = instance->tail;
        instance->tail->next = new_node;
        instance->tail = new_node;
    } else {
        struct list_node *current = NULL;
        // TODO: Check to start altering from head or tail based on middle point.
        if (at <= list_size(instance) / 2) {
            current = instance->head;
            for (size_t i = 0; i < at; i++)
                current = current->next;
        } else {
            current = instance->tail;
            for (size_t i = list_size(instance) - 1; i > at; i--) {
                current = current->prev;
            }
        }

        // Is it head?
        if(current->prev == NULL){
            new_node->next = current;
            current->prev = new_node;
            instance->head = new_node;
        } else {
            new_node->next = current;
            new_node->prev = current->prev;
            current->prev->next = new_node;
            current->prev = new_node;
        }
    }
    instance->cached_size++;
}

size_t list_size(struct list *instance){
    if(instance == NULL)
        return 0;
    return instance->cached_size;
}

void list_pop_back(struct list *instance){
    if (instance == NULL || list_size(instance) == 0)
        return;
    list_pop(instance, list_size(instance) - 1);
}
void list_pop_front(struct list *instance){
    if(instance == NULL || list_size(instance) == 0)
        return;
    list_pop(instance, 0);
}

void list_pop(struct list *instance, size_t at){
    if (instance == NULL || instance->head == NULL || at >= list_size(instance)) {
        return; // Handle invalid cases: null list, empty list, or invalid position
    }

    struct list_node *current_node;
    size_t middle = list_size(instance) / 2;
    // TODO: Check to start altering from head or tail based on middle point.
    if (at <= middle) {
        current_node = instance->head;
        for (size_t i = 0; i < at; i++) 
            current_node = current_node->next;
    } else {
        current_node = instance->tail;
        for (size_t i = list_size(instance) - 1; i > at; i--)
            current_node = current_node->prev;
    }

    if (current_node->prev == NULL) { // Deleting head
        if(instance->head->next == NULL){
            free(instance->head->value);
            free(instance->head);
            instance->head = NULL;
            return;
        }
        instance->head = current_node->next;
    } else {
        current_node->prev->next = current_node->next;
    }

    if (current_node->next == NULL) { // Deleting tail
        if(instance->tail->prev == NULL){
            free(instance->tail->value);
            free(instance->tail);
            instance->tail = NULL;
            return;
        }
        instance->tail = current_node->prev;
    } else {
        current_node->next->prev = current_node->prev;
    }

    // Free resources
    free(current_node->value);
    free(current_node);

    instance->cached_size--;
}

void *list_get(struct list *instance, size_t at) {
    if (instance == NULL || at >= list_size(instance))
        return NULL;

    struct list_node *current;
    size_t middle = list_size(instance) / 2;

    if (at <= middle) {
        current = instance->head;
        for (size_t i = 0; i < at; i++)
            current = current->next;
    } else {
        current = instance->tail;
        for (size_t i = list_size(instance) - 1; i > at; i--) {
            current = current->prev;
        }
    }

    return current->value;
}

enum ErrorCode list_update(struct list *instance, size_t at, void *value, size_t value_size) {
    if (instance == NULL || at >= list_size(instance)) {
        return InvalidParameter;
    }

    struct list_node *current;
    size_t middle = list_size(instance) / 2;

    if (at <= middle) {
        current = instance->head;
        for (size_t i = 0; i < at; i++) 
            current = current->next;
    } else {
        current = instance->tail;
        for (size_t i = list_size(instance) - 1; i > at; i--)
            current = current->prev;
    }

    current->value = realloc(current->value, value_size);
    if (current->value == NULL)
        return OutOfMemory;
    memcpy(current->value, value, value_size);
    current->value_size = value_size;
    return Ok;
}