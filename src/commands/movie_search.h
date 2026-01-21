#ifndef MOVIE_SEARCH_H
#define MOVIE_SEARCH_H

#include "./../movie_list.h"

void movie_list_search_by_title(const MovieList *list, const char *title);
void movie_list_search_by_id(const MovieList *list, int id);
void movie_list_search_by_year(const MovieList *list, int year);
void movie_list_search_by_origin(const MovieList *list, const char *origin);
void movie_list_search_by_genre(const MovieList *list, const char *genre);
void movie_list_search_by_director(const MovieList *list, const char *director);

#endif 
