#include "./sort_movie.h"
#include "./../movie.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Sorts numerically by ID (Lowest to Highest)
static int compareID(const void *a, const void *b) {
    const Movie *mA = *(const Movie **)a;
    const Movie *mB = *(const Movie **)b;
    return movie_get_id(mA) - movie_get_id(mB);
}

// Sorts numerically by Year (Oldest to Newest)
static int compareYear(const void *a, const void *b) {
    const Movie *mA = *(const Movie **)a;
    const Movie *mB = *(const Movie **)b;
    return movie_get_release_year(mA) - movie_get_release_year(mB);
}

// Sorts alphabetically by Director
static int compareDirector(const void *a, const void *b) {
    const Movie *mA = *(const Movie **)a;
    const Movie *mB = *(const Movie **)b;
    // Handle NULLs safely if necessary, though strict CSVs shouldn't have them
    return strcasecmp(movie_get_director(mA), movie_get_director(mB));
}

// Sorts alphabetically by Genre
static int compareGenre(const void *a, const void *b) {
    const Movie *mA = *(const Movie **)a;
    const Movie *mB = *(const Movie **)b;
    return strcasecmp(movie_get_genre(mA), movie_get_genre(mB));
}

static int compareOrigin(const void *a, const void *b) {
    const Movie *mA = *(const Movie **)a;
    const Movie *mB = *(const Movie **)b;
    return strcasecmp(movie_get_origin(mA), movie_get_origin(mB));
}

void sort_movies(MovieList *list, char flag) {
    if (!list || movie_list_size(list) == 0) {
        printf("List is empty.\n");
        return;
    }

    switch(flag) {
        case 'i':
            printf("Sorting by ID...\n");
            movie_list_sort(list, compareID);
            break;
        case 'y':
            printf("Sorting by Release Year...\n");
            movie_list_sort(list, compareYear);
            break;
        case 'd':
            printf("Sorting by Director...\n");
            movie_list_sort(list, compareDirector);
            break;
        case 'g':
            printf("Sorting by Genre...\n");
            movie_list_sort(list, compareGenre);
            break;
        case 'o':
            printf("Sorting by Origin...\n");
            movie_list_sort(list, compareOrigin);
            break;
        default:
            printf("Invalid flag. Use -y, -d, -g, or -o.\n");
            return;
    }

    // Reprint the table to show result
    movie_list_print_table(list);
}
