#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include "./../movie.h"
#include "./../movie_list.h"

#define BUF_SIZE 256

/* helper: remove trailing newline from fgets */
static void strip_newline(char *s) {
    if (!s) return;
    s[strcspn(s, "\n") ] = '\0';
}

/* trim leading/trailing whitespace and remove surrounding quotes */
static void trim_whitespace(char *s) {
    if (!s) return;
    char *start = s;
    while (*start && isspace((unsigned char)*start)) start++;
    if (start != s) memmove(s, start, strlen(start) + 1);

    size_t len = strlen(s);
    while (len > 0 && isspace((unsigned char)s[len - 1])) s[--len] = '\0';

    /* remove surrounding double quotes if present */
    if (len >= 2 && s[0] == '"' && s[len - 1] == '"') {
        memmove(s, s + 1, len - 2);
        s[len - 2] = '\0';
    }
}

/* Read a line into buf. Returns 0 on success, -1 on EOF/error. */
static int read_line(const char *prompt, char *buf, size_t size) {
    if (!buf || size == 0) return -1;
    if (prompt) printf("%s", prompt);
    if (!fgets(buf, (int)size, stdin)) return -1; /* EOF or error */
    strip_newline(buf);
    return 0;
}

/* Read a non-empty string (after trimming). Returns 0 on success, -1 on EOF. */
static int read_nonempty_string(const char *prompt, char *buf, size_t size) {
    while (1) {
        if (read_line(prompt, buf, size) < 0) return -1;
        trim_whitespace(buf);
        if (buf[0] == '\0') {
            printf("Input cannot be empty. Please try again.\n");
            continue;
        }
        return 0;
    }
}

/* Parse integer with robust error checking and range. Returns 0 on success, -1 on EOF, 1 on invalid. */
static int parse_int_field(const char *prompt, int *out, int min, int max) {
    char buf[BUF_SIZE];
    char *endptr;
    long val;

    while (1) {
        if (read_line(prompt, buf, sizeof buf) < 0) return -1;
        trim_whitespace(buf);
        if (buf[0] == '\0') {
            printf("Input cannot be empty. Please enter a number.\n");
            continue;
        }

        errno = 0;
        val = strtol(buf, &endptr, 10);
        if (errno == ERANGE || val < LONG_MIN || val > LONG_MAX) {
            printf("Number out of range. Please try again.\n");
            continue;
        }
        if (endptr == buf || *endptr != '\0') {
            printf("Invalid numeric input. Please enter digits only.\n");
            continue;
        }
        if (val < min || val > max) {
            printf("Number must be between %d and %d. Please try again.\n", min, max);
            continue;
        }
        *out = (int)val;
        return 0;
    }
}

/* Shared helpers are reused by add/edit */

void add_movie_manually(MovieList *list) {
    if (!list) return;

    char buf[BUF_SIZE];
    int id;
    int year;
    char title[BUF_SIZE];
    char origin[BUF_SIZE];
    char genre[BUF_SIZE];
    char director[BUF_SIZE];

    /* Calculate ID safely */
    size_t list_size = movie_list_size(list);
    if (list_size >= (size_t)INT_MAX) {
        fprintf(stderr, "Movie list too large to assign a new ID.\n");
        return;
    }
    id = (int)list_size + 1;

    /* Determine reasonable year bounds: first known films (~1888) to next year */
    time_t t = time(NULL);
    struct tm tm_now;
    localtime_r(&t, &tm_now);
    int current_year = tm_now.tm_year + 1900;
    int min_year = 1888;
    int max_year = current_year + 1; /* allow one year into future for upcoming films */

    /* Release year (robust validation) */
    if (parse_int_field("Enter release year: ", &year, min_year, max_year) < 0) {
        printf("Input cancelled or EOF received. Aborting.\n");
        return;
    }

    /* Title */
    if (read_nonempty_string("Enter title: ", title, sizeof title) < 0) {
        printf("Input cancelled or EOF received. Aborting.\n");
        return;
    }

    /* Origin */
    if (read_nonempty_string("Enter origin (country): ", origin, sizeof origin) < 0) {
        printf("Input cancelled or EOF received. Aborting.\n");
        return;
    }

    /* Genre */
    if (read_nonempty_string("Enter genre: ", genre, sizeof genre) < 0) {
        printf("Input cancelled or EOF received. Aborting.\n");
        return;
    }

    /* Director */
    if (read_nonempty_string("Enter director: ", director, sizeof director) < 0) {
        printf("Input cancelled or EOF received. Aborting.\n");
        return;
    }

    /* Additional lightweight validation: lengths and characters */
    if (strlen(title) >= sizeof title - 1) {
        printf("Warning: title truncated to %zu characters.\n", sizeof title - 1);
        title[sizeof title - 1] = '\0';
    }
    if (strlen(origin) >= sizeof origin - 1) origin[sizeof origin - 1] = '\0';
    if (strlen(genre) >= sizeof genre - 1) genre[sizeof genre - 1] = '\0';
    if (strlen(director) >= sizeof director - 1) director[sizeof director - 1] = '\0';

    /* Basic sanitization: ensure printable characters (allow common punctuation) */
    for (char *p = title; *p; ++p) if (!isprint((unsigned char)*p)) *p = '?';
    for (char *p = origin; *p; ++p) if (!isprint((unsigned char)*p)) *p = '?';
    for (char *p = genre; *p; ++p) if (!isprint((unsigned char)*p)) *p = '?';
    for (char *p = director; *p; ++p) if (!isprint((unsigned char)*p)) *p = '?';

    /* Confirm with user before creating */
    while (1) {
        printf("\nAbout to add movie:\n");
        printf("  ID: %d\n", id);
        printf("  Year: %d\n", year);
        printf("  Title: %s\n", title);
        printf("  Origin: %s\n", origin);
        printf("  Genre: %s\n", genre);
        printf("  Director: %s\n", director);
        printf("Confirm? (y/n): ");

        if (!fgets(buf, sizeof buf, stdin)) {
            printf("EOF received. Aborting.\n");
            return;
        }
        strip_newline(buf);
        trim_whitespace(buf);
        if (buf[0] == 'y' || buf[0] == 'Y') break;
        if (buf[0] == 'n' || buf[0] == 'N') {
            printf("Aborted by user. No movie was added.\n");
            return;
        }
        printf("Please enter 'y' or 'n'.\n");
    }

    /* create movie */
    Movie *movie = movie_create(
        id,
        year,
        title,
        origin,
        genre,
        director
    );

    if (!movie) {
        fprintf(stderr, "Failed to create movie (movie_create returned NULL)\n");
        return;
    }

    /* add to list */
    movie_list_add(list, movie);

    printf("Movie added successfully!\n");
}
/* ================= EDIT MOVIE ================= */
void edit_movie_manually(MovieList *list, int id) {
    if (!list) return;

    /* IDs are 1-based, list index is 0-based */
    if (id <= 0 || id > movie_list_size(list)) {
        printf("No movie with ID %d found.\n", id);
        return;
    }

    Movie *movie = movie_list_get_mut(list, id - 1);
    if (!movie) {
        printf("No movie with ID %d found.\n", id);
        return;
    }

    char buf[BUF_SIZE];

    /* Calculate reasonable year bounds (same as add_movie) */
    time_t t = time(NULL);
    struct tm tm_now;
    localtime_r(&t, &tm_now);
    int current_year = tm_now.tm_year + 1900;
    int min_year = 1888;
    int max_year = current_year + 1;

    printf("Editing movie ID %d (press ENTER to keep current value)\n", id);

    /* ---- Release year ---- */
    while (1) {
        int current_val = movie_get_release_year(movie);
        printf("Release year [%d]: ", current_val);

        if (read_line(NULL, buf, sizeof buf) < 0) return; /* Handle EOF */
        trim_whitespace(buf);

        /* If empty, keep existing */
        if (buf[0] == '\0') {
            break;
        }

        /* Parse and Validate */
        char *endptr;
        errno = 0;
        long val = strtol(buf, &endptr, 10);

        if (errno == ERANGE || val < LONG_MIN || val > LONG_MAX) {
            printf("Number out of range. Please try again.\n");
            continue;
        }
        if (endptr == buf || *endptr != '\0') {
            printf("Invalid numeric input. Please enter digits only.\n");
            continue;
        }
        if (val < min_year || val > max_year) {
            printf("Year must be between %d and %d. Please try again.\n", min_year, max_year);
            continue;
        }

        movie_set_release_year(movie, (int)val);
        break; /* Success */
    }

    /* ---- Title ---- */
    while (1) {
        const char *current_val = movie_get_title(movie);
        printf("Title [%s]: ", current_val);

        if (read_line(NULL, buf, sizeof buf) < 0) return;
        trim_whitespace(buf);

        if (buf[0] == '\0') break; /* Keep existing */

        /* Sanitize printable characters */
        for (char *p = buf; *p; ++p) if (!isprint((unsigned char)*p)) *p = '?';

        /* Update */
        movie_set_title(movie, buf);
        break;
    }

    /* ---- Origin ---- */
    while (1) {
        const char *current_val = movie_get_origin(movie);
        printf("Origin [%s]: ", current_val);

        if (read_line(NULL, buf, sizeof buf) < 0) return;
        trim_whitespace(buf);

        if (buf[0] == '\0') break;

        for (char *p = buf; *p; ++p) if (!isprint((unsigned char)*p)) *p = '?';

        movie_set_origin(movie, buf);
        break;
    }

    /* ---- Genre ---- */
    while (1) {
        const char *current_val = movie_get_genre(movie);
        printf("Genre [%s]: ", current_val);

        if (read_line(NULL, buf, sizeof buf) < 0) return;
        trim_whitespace(buf);

        if (buf[0] == '\0') break;

        for (char *p = buf; *p; ++p) if (!isprint((unsigned char)*p)) *p = '?';

        movie_set_genre(movie, buf);
        break;
    }

    /* ---- Director ---- */
    while (1) {
        const char *current_val = movie_get_director(movie);
        printf("Director [%s]: ", current_val);

        if (read_line(NULL, buf, sizeof buf) < 0) return;
        trim_whitespace(buf);

        if (buf[0] == '\0') break;

        for (char *p = buf; *p; ++p) if (!isprint((unsigned char)*p)) *p = '?';

        movie_set_director(movie, buf);
        break;
    }

    printf("Movie updated successfully.\n");
}
