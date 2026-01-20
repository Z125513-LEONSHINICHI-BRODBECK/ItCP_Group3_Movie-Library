#include "./movie_delete.h"
#include "./../movie.h"
#include <stdio.h>

int delete_movie_interactive(MovieList *list) {
    int id;
    char confirm;

    printf("Enter movie ID to delete: ");
    if (scanf("%d", &id) != 1) {
        // flush buffer
        int c; while ((c = getchar()) != '\n' && c != EOF);
        printf("Invalid input.\n");
        return 0;
    }
    // Clear newline left by scanf
    getchar();

    int size = movie_list_size(list);
    int found_index = -1;

    for (int i = 0; i < size; i++) {
        const Movie *m = movie_list_get(list, i);
        if (movie_get_id(m) == id) {
            found_index = i;
            break;
        }
    }

    if (found_index != -1) {
        const Movie *m = movie_list_get(list, found_index);
        printf("\nMovie found:\n");
        printf("ID: %d\nTitle: %s\nYear: %d\n",
               movie_get_id(m),
               movie_get_title(m),
               movie_get_release_year(m));

        printf("\nConfirm delete (y/n): ");
        scanf("%c", &confirm);
        // consume newline
        int c; while ((c = getchar()) != '\n' && c != EOF);

        if (confirm == 'y' || confirm == 'Y') {
            movie_list_delete_at(list, found_index);
            printf("Movie deleted successfully.\n");
            return 1; // Return 1 indicating a change happened
        } else {
            printf("Deletion cancelled.\n");
            return 0;
        }
    }

    printf("Movie ID %d not found.\n", id);
    return 0;
}
