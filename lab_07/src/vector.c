#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

#include "vector.h"

vector_t create_vector(size_t elem_size)
{
    vector_t result = { 0 };
    result.elem_size = elem_size;
    return result;
}

int vector_reserve(vector_t *vec, size_t capacity)
{
    if (vec->capacity >= capacity)
        return EXIT_SUCCESS;

    void *temp = realloc(vec->data, capacity * vec->elem_size);
    if (temp == NULL)
        return EXIT_FAILURE;

    vec->data = temp;
    vec->capacity = capacity;
    return EXIT_SUCCESS;
}

int vector_grow(vector_t *vec)
{
    size_t new_capacity = DEFAULT_CAPACITY;
    if (new_capacity < vec->capacity * 2)
        new_capacity = vec->capacity * 2;

    if (vector_reserve(vec, new_capacity))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int vector_push_back(vector_t *vec, void *elem)
{
    if (vec->size == vec->capacity)
        if (vector_grow(vec))
            return EXIT_FAILURE;

    void *to_write = (char *)(vec->data) + vec->size * vec->elem_size;
    memcpy(to_write, elem, vec->elem_size);

    vec->size++;
    return EXIT_SUCCESS;
}

void clear_vector(vector_t *vec)
{
    free(vec->data);
    vec->data = NULL;
    vec->capacity = 0;
    vec->size = 0;
}

void *vector_get_at(vector_t *vec, size_t index)
{
    return (char *)(vec->data) + index * vec->elem_size;
}

void vector_set_at(vector_t *vec, size_t index, void *elem)
{
    void *to_write = (char *)(vec->data) + index * vec->elem_size;
    memcpy(to_write, elem, vec->elem_size);
}

int build_from_pointers(const void *pb, const void *pe, size_t elem_size, vector_t *dst)
{
    vector_t result = { 0 };
    result.elem_size = elem_size;
    size_t size_in_bytes = (char *)pe - (char *)pb;
    if (vector_reserve(&result, size_in_bytes / elem_size))
        return EXIT_FAILURE;

    memcpy(result.data, pb, size_in_bytes);
    result.size = size_in_bytes / elem_size;
    *dst = result;
    return EXIT_SUCCESS;
}

// Результат должен быть сразу присвоен 
// какой-то переменной
void *vector_pop_back(vector_t *vec)
{
    assert(vec->size != 0);
    --vec->size;
    return vector_get_at(vec, vec->size);
}

void vector_print(vector_t *vec, void (*print_elem)(void *elem))
{
    for (size_t i = 0; i < vec->size; ++i)
        print_elem(vector_get_at(vec, i));
}

void vector_print_reverse(vector_t *vec, void (*print_elem)(void *elem))
{
    for (int32_t i = vec->size - 1; i >= 0; --i)
        print_elem(vector_get_at(vec, i));
}
