#ifndef _ABSTRAX_TRAITS_ITERABLE
#define _ABSTRAX_TRAITS_ITERABLE 0
#include <abstrax/baseobject.h>

#define TRAIT_ITERABLE // Iterable attribute
struct iterator{
    const void *base_pointer; // the base value that will be used by the implementor to modify `::pointer`.
    void *pointer;
    size_t position;
    void (*next)(struct iterator*);
    int (*has_next)(struct iterator);
    void (*advance)(struct iterator*, size_t to); // moves `::pointer` by `to`.
};

#define EMBED_ITER(OBJECT) struct iterator(*iterate)(OBJECT)
#endif