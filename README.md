# ItCP_Group3_Movie-Library

A simple terminal-based Movie Library Management System written in C. The project demonstrates clean modular design using header/implementation files, opaque structs, dynamic arrays, and safe memory management.

## Features

- Create and manage movies (ID, release year, title, origin, genre, director)
- Show Statistics of the Movie Library
- Dynamic list of movies (ArrayList-style growth)
- Encapsulation via opaque structs (Movie, MovieList, Command)
- Pretty-printed table output to the terminal
- Clear ownership rules and explicit cleanup

---

compile and run from the repository root folder

## How to compile this program

```zsh
gcc src/main.c src/movie.c src/movie_list.c src/command.c src/commands/movie_search.c src/file_io.c src/commands/movie_add_edit.c src/help.c src/statistics.c src/group_movie.c src/movie_delete.c -o MovieLibrary
```

## How to run this file
```zsh
./MovieLibrary
```
