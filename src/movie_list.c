#include "movie_list.h"
#include <stdlib.h>
#include <stdio.h>

struct MovieList {
    Movie **data;
    int size;
    int capacity;
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

int movie_list_size(const MovieList *list) {
    return (int)list->size;
}

const Movie *movie_list_get(const MovieList *list, int index) {
    if (index >= list->size) return NULL;
    return list->data[index];
}

Movie *movie_list_get_mut(MovieList *list, int index) {
    if (index >= list->size) return NULL;
    return list->data[index];
}

void movie_list_add(MovieList *list, Movie *movie) {
    if (list->size == list->capacity) {
        int new_capacity = list->capacity * 2;
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

/* Sorts the list. Note: The comparator receives Movie** (pointers to pointers) */
void movie_list_sort(MovieList *list, int (*compar)(const void *, const void *)) {
    if (!list || list->size < 2) return;
    qsort(list->data, list->size, sizeof(Movie *), compar);
}

/* Removes element at index, shifts remaining elements, and destroys the movie object */
void movie_list_delete_at(MovieList *list, int index) {
    if (!list || index < 0 || index >= list->size) return;

    // 1. Destroy the actual movie object
    movie_destroy(list->data[index]);

    // 2. Shift everything after index to the left
    for (int i = index; i < list->size - 1; i++) {
        list->data[i] = list->data[i + 1];
    }

    // 3. Nullify last slot and decrease size
    list->data[list->size - 1] = NULL;
    list->size--;
}

void movie_list_print_table(const MovieList *list) {
    if (!list) return;
    printf("\e[1;1H\e[2J");

    printf(
        "| %-4s | %-12s | %-33s | %-13s | %-18s | %-20s |\n",
        "ID", "Year", "Title", "Origin", "Genre", "Director"
    );

    printf(
        "|------|--------------|-----------------------------------|---------------|--------------------|----------------------|\n"
    );

    for (int i = 0; i < movie_list_size(list); ++i) {
        const Movie *m = movie_list_get(list, i);
        if (!m) continue;

        printf(
            "| %4d | %12d | %-33s | %-13s | %-18s | %-20s |\n",
            movie_get_id(m),
            movie_get_release_year(m),
            movie_get_title(m),
            movie_get_origin(m),
            movie_get_genre(m),
            movie_get_director(m)
        );
    }
    printf("\e[%d;1H> ", 999);
    fflush(stdout);
}
