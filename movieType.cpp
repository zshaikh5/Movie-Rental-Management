// CSS343 Movie Project
// Group 2: Jasleen Kaur Saini, Zaina Shaikh, Maryam Maabreh, Vinisha Bala

// File Name: movieType.cpp
// Purpose: Implementation of movieType class member functions.

#include "movieType.h"
#include "movie.h"

// Method to borrow a movie
// Name: borrow
// Purpose: Borrow the movie (reduce stock by 1).
// Pre-conditions: Movie object initialized and in stock.
// Post-conditions: Stock of the movie reduced by 1 if borrowed successfully.
// Return: True if the movie was successfully borrowed, false otherwise.
bool MovieType::borrow(Movie *movie) { return movie->borrowMovie(movie); }

// Method to return a movie
// Name: returnMovie
// Purpose: Return the movie (increase stock by 1).
// Pre-conditions: Movie object initialized.
// Post-conditions: Stock of the movie increased by 1 after return.
// Return: Always true as a movie is returned.
bool MovieType::returnMovie(Movie *movie) { return movie->returnMovie(movie); }
