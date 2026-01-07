#include "movie_list.h"
#include <stdlib.h>

struct MovieList {
    Movie **data;
    size_t size;
    size_t capacity;
};

#define INITIAL_CAPACITY 32

MovieList *movie_list_create(void) {
    MovieList *list = malloc(sizeof *list);
    if (!list) return NULL;

    list->size = 0;
    list->capacity = INITIAL_CAPACITY;
    list->data = malloc(list->capacity * sizeof *list->data);

    if (!list->data) {
        free(list);
        return NULL;
    }

    return list;
}

void movie_list_destroy(MovieList *list) {
    if (!list) return;

    /* does NOT destroy movies themselves */
    free(list->data);
    free(list);
}

size_t movie_list_size(const MovieList *list) {
    return list->size;
}

void movie_list_add(MovieList *list, Movie *movie) {
    if (list->size == list->capacity) {
        size_t new_capacity = list->capacity * 2;
        Movie **new_data = realloc(
            list->data,
            new_capacity * sizeof *new_data
        );

        if (!new_data) return; /* allocation failed */

        list->data = new_data;
        list->capacity = new_capacity;
    }

    list->data[list->size++] = movie;
}

Movie *movie_list_get(const MovieList *list, size_t index) {
    if (index >= list->size) return NULL;
    return list->data[index];
}
