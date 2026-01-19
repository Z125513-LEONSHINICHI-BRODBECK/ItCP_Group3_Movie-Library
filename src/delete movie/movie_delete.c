#include <stdio.h>
#include "movie_delete.h"

int deleteMovie(Movie movies[], int *count) {
    int id;
    char confirm;

    printf("Enter movie ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < *count; i++) {
        if (movies[i].id == id) {
            printf("\nMovie found:\n");
            printf("ID: %d\nTitle: %s\nYear: %d\n",
                   movies[i].id,
                   movies[i].title,
                   movies[i].year);

            printf("\nConfirm delete (y/n): ");
            scanf(" %c", &confirm);

            if (confirm != 'y' && confirm != 'Y') {
                printf("Deletion cancelled.\n");
                return 0;
            }

            /* Shift remaining movies left */
            for (int j = i; j < *count - 1; j++) {
                movies[j] = movies[j + 1];
            }

            (*count)--;

            printf("Movie deleted successfully.\n");
            return 1;
        }
    }

    printf("Movie ID not found.\n");
    return 0;
}
