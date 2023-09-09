#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

int vector_create_struct(struct vector_t **a, int N) {
    if(a == NULL || N <= 0) return 1;

    int res;

    *a = malloc(sizeof(struct vector_t));

    if(*a == NULL) return 2;
    else {
        res = vector_create(*a, N);
        if(res == 2) {
            vector_destroy_struct(a);
            return 2;
        }
        else return 0;
    }
}

void vector_destroy_struct(struct vector_t **a) {
    if(a == NULL || *a == NULL) return;

    vector_destroy(*a);
    if(*a != NULL) free(*a);
}

int vector_create(struct vector_t *a, int N) {
    if(a == NULL || N <= 0) return 1;

    a->ptr = malloc(N * sizeof(int));
    if(a->ptr == NULL) {
        return 2;
    }
    else {
        a->size = 0;
        a->capacity = N;
        return 0;
    }
}

void vector_destroy(struct vector_t *a) {
    if(a == NULL || a->ptr == NULL) return;

    if(a->ptr != NULL) free(a->ptr);
}

void vector_display(const struct vector_t *a) {
    if(a == NULL || a->ptr == NULL || a->size <= 0 || a->size > a->capacity
       || a->capacity <= 0) return;

    for(int i = 0; i < a->size && i < a->capacity; i++) {
        printf("%d ", *(a->ptr + i));
    }
}

int vector_push_back(struct vector_t *a, int value) {
    if(a == NULL || a->ptr == NULL || a->size < 0 || a->size > a->capacity
       || a->capacity <= 0) return 1;

    if(a->size == a->capacity) {
        int *realloc_ptr;
        realloc_ptr = realloc(a->ptr, a->capacity * 2 * sizeof(int));

        if(realloc_ptr == NULL) return 2;
        else a->ptr = realloc_ptr;

        *(a->ptr + a->size) = value;
        a->size++;
        a->capacity *= 2;
    }
    else {
        *(a->ptr + a->size) = value;
        a->size++;
    }

    return 0;
}

int vector_erase(struct vector_t *a, int value) {
    if(a == NULL || a->ptr == NULL || a->size < 0 || a->size > a->capacity
       || a->capacity <= 0) return -1;

    int index = 0, removed_elements = 0, is_half = 0;

    if(((float)a->size / a->capacity) < 0.25) {
        if(a->capacity > 1 && is_half == 0) {
            int *realloc_ptr;
            realloc_ptr = realloc(a->ptr, a->capacity * 0.5 * sizeof(int));
            a->capacity *= 0.5;
            if(realloc_ptr == NULL) return 2;
            else a->ptr = realloc_ptr;
            is_half = 1;
        }
    }

    while(index < a->size) {
        if(*(a->ptr + index) == value) {
            memcpy(a->ptr + index, a->ptr + index + 1, sizeof(int) * (a->capacity - index));
            a->size--;
            if(((float)a->size / a->capacity) < 0.25) {
                if(a->capacity > 1 && is_half == 0) {
                    int *realloc_ptr;
                    realloc_ptr = realloc(a->ptr, a->capacity * 0.5 * sizeof(int));
                    a->capacity *= 0.5;
                    if(realloc_ptr == NULL) return 2;
                    else a->ptr = realloc_ptr;
                    is_half = 1;
                }
            }
            index = 0;
            removed_elements++;
            continue;
        }
        index++;
    }

    return removed_elements;
}
