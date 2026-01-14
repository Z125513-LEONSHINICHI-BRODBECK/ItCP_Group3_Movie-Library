#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "./../movie.h"
#include "./../movie_list.h"

static int contains_case_insensitive(const char *str, const char *substr) {
    if (str == NULL || substr == NULL) {
        return 0;
    }
    size_t len = strlen(substr);
    if (len == 0) {
        return 1;
    }

    for (size_t i = 0; str[i] != '\0'; i++) {
        size_t j;
        for (j = 0; j < len; j++) {
            if (str[i + j] == '\0') {
                return 0;
            }
            if (tolower((unsigned char)str[i + j]) != tolower((unsigned char)substr[j])) {
                break;
            }
        }
        if (j == len) {
            return 1;
        }
    }
    return 0;
}

void movie_list_search_by_title(MovieList *list, const char *substring) {
    MovieList *results = movie_list_create();
    if (!results) {
        fprintf(stderr, "Error: Failed to create search results list.\n");
        return;
    }

    size_t size = movie_list_size(list);
    for (size_t i = 0; i < size; i++) {
        Movie *m = movie_list_get_mut(list, i);
        if (contains_case_insensitive(movie_get_title(m), substring)) {
            movie_list_add(results, m);
        }
    }

    movie_list_print_table(results);
    movie_list_destroy(results);
}

void movie_list_search_by_id(MovieList *list, int id) {
    MovieList *results = movie_list_create();
    if (!results) {
        fprintf(stderr, "Error: Failed to create search results list.\n");
        return;
    }

    size_t size = movie_list_size(list);
    for (size_t i = 0; i < size; i++) {
        Movie *m = movie_list_get_mut(list, i);
        if (movie_get_id(m) == id) {
            movie_list_add(results, m);
        }
    }

    movie_list_print_table(results);
    movie_list_destroy(results);
}

void movie_list_search_by_year(MovieList *list, int year) {
    MovieList *results = movie_list_create();
    if (!results) {
        fprintf(stderr, "Error: Failed to create search results list.\n");
        return;
    }

    size_t size = movie_list_size(list);
    for (size_t i = 0; i < size; i++) {
        Movie *m = movie_list_get_mut(list, i);
        if (movie_get_release_year(m) == year) {
            movie_list_add(results, m);
        }
    }

    movie_list_print_table(results);
    movie_list_destroy(results);
}

void movie_list_search_by_origin(MovieList *list, const char *origin) {
    MovieList *results = movie_list_create();
    if (!results) {
        fprintf(stderr, "Error: Failed to create search results list.\n");
        return;
    }

    size_t size = movie_list_size(list);
    for (size_t i = 0; i < size; i++) {
        Movie *m = movie_list_get_mut(list, i);
        if (contains_case_insensitive(movie_get_origin(m), origin)) {
            movie_list_add(results, m);
        }
    }

    movie_list_print_table(results);
    movie_list_destroy(results);
}

void movie_list_search_by_genre(MovieList *list, const char *genre) {
    MovieList *results = movie_list_create();
    if (!results) {
        fprintf(stderr, "Error: Failed to create search results list.\n");
        return;
    }

    size_t size = movie_list_size(list);
    for (size_t i = 0; i < size; i++) {
        Movie *m = movie_list_get_mut(list, i);
        if (contains_case_insensitive(movie_get_genre(m), genre)) {
            movie_list_add(results, m);
        }
    }

    movie_list_print_table(results);
    movie_list_destroy(results);
}

void movie_list_search_by_director(MovieList *list, const char *director) {
    MovieList *results = movie_list_create();
    if (!results) {
        fprintf(stderr, "Error: Failed to create search results list.\n");
        return;
    }

    size_t size = movie_list_size(list);
    for (size_t i = 0; i < size; i++) {
        Movie *m = movie_list_get_mut(list, i);
        if (contains_case_insensitive(movie_get_director(m), director)) {
            movie_list_add(results, m);
        }
    }

    movie_list_print_table(results);
    movie_list_destroy(results);
}
