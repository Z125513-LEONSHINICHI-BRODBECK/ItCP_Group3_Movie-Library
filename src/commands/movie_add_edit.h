#ifndef MOVIE_ADD_EDIT_H
#define MOVIE_ADD_EDIT_H

#include "./../movie_list.h"

/*
 * Prompts the user for movie data (ID, release year, title, origin,
 * genre, director), creates a Movie, and adds it to the given MovieList.
 */
void add_movie_manually(MovieList *list);

/*
 * Prompts the user based on the id number passed, to edit the data of
 * movie. Updates the movie with the passed
 */
 void edit_movie_manually(MovieList *list, int id);

#endif /* MOVIE_ADD_EDIT_H */
