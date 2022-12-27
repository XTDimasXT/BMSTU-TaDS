#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdlib.h>

#define DEFAULT_CAPACITY 8u

typedef struct
{
    void *data;
    size_t elem_size;
    size_t size;
    size_t capacity;
} vector_t;

vector_t create_vector(size_t elem_size);
int vector_push_back(vector_t *vec, void *elem);
void clear_vector(vector_t *vec);
void *vector_get_at(vector_t *vec, size_t index);
void vector_set_at(vector_t *vec, size_t index, void *elem);
int build_from_pointers(const void *pb, const void *pe, size_t elem_size, vector_t *dst);
int vector_reserve(vector_t *vec, size_t capacity);
int vector_grow(vector_t *vec);
void *vector_pop_back(vector_t *vec);
void vector_print(vector_t *vec, void (*print_elem)(void *elem));
void vector_print_reverse(vector_t *vec, void (*print_elem)(void *elem));

#endif // __VECTOR_H__
