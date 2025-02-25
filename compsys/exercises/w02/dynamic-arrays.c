#include <stdio.h>
#include <stdint.h>

#define CHUNK_SIZE 128

typedef int ElementType;

typedef struct {
    size_t allocated;
    size_t size;
    ElementType* content;
} DynamicArray;

DynamicArray* construct_new_array(DynamicArray* v) {
    ElementType* ptr = calloc(CHUNK_SIZE, sizeof(ElementType));
    if (ptr != NULL) {

        DynamicArray* arr = malloc(sizeof(DynamicArray));
        arr->size = 0;
        arr->allocated = CHUNK_SIZE;
        arr->content = ptr;

        *v = *arr;

        return v;

    } else return NULL;
};

DynamicArray* vector_enlarge(DynamicArray* v) {

    if (v != NULL && SIZE_MAX/sizeof(ElementType) < v->allocated) {
        DynamicArray res = *v;
        res.allocated += CHUNK_SIZE;
        res.content = realloc(res.content, res.allocated * sizeof(ElementType));
        if (res.content != NULL) {
            *v = res;
            return v;
        }
    }

    return NULL;

}

size_t append_new_element(DynamicArray* arr, ElementType el) {

    DynamicArray res;

    while (res.size >= res.allocated) {
        ElementType* newPtr = vector_enlarge(&res);
        if (newPtr != NULL) {
            res.allocated = res.allocated + CHUNK_SIZE;
            res.content;
        } else return 0;
    }

    res.content[res.size-1] = el;
    res.size += 1;

    *arr = res; 

    return res.size;
};

void delete_vector (DynamicArray* arr) {
    free(arr->content);
    arr->size = 0;
    arr->allocated = 0;
}

int main () {


    return 0;
};
