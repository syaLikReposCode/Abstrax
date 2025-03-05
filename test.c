#include <abstrax/types/string.h>
#include <abstrax/dsa/list.h>
#include <stdio.h>

#define PRINT_LIST do{ \
                        struct list_node *cur = tlist->head;\
                        printf("List Size: %lu\n", tlist->cached_size);\
                        while(cur != NULL) {\
                            printf("%s ", (char*)cur->value);\
                            cur = cur->next;\
                        } \
                        printf("\n----\n");\
                     } while(0);
int main(){
    struct list *tlist = list_init("TEST", 5).value;
    list_append(tlist, "World", 6);
    list_append(tlist, "Hello", 6);
    list_prepend(tlist, "Another", 9);
    list_insert(tlist, 0, "ZaW", 4);
    PRINT_LIST;
    printf("%s\n", (char*)list_get(tlist, 2));
    list_pop(tlist, 2);
    list_update(tlist, 3, "Za!", 4);
    printf("%s\n", (char*)list_get(tlist, 3));
    list_pop_front(tlist);
    list_pop_back(tlist);
    printf("Final List Size: %lu\n", tlist->cached_size);
    list_deinit(tlist);
    return 0;
}