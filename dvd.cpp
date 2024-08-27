// CSS343 Movie Project
// Group 2: Jasleen Kaur Saini, Zaina Shaikh, Maryam Maabreh, Vinisha Bala

// File Name: dvd.cpp
// Purpose: Implementation of the DVD class methods.

#include "dvd.h"
#include "movie.h"

// Default constructor
// Name: DVD
// Purpose: Initializes a DVD object.
// Pre-conditions: None.
// Post-conditions: A DVD object is created.
// Return: if included
DVD::DVD() {}

// Destructor
// Name: ~DVD
// Purpose: Destroys a DVD object.
// Pre-conditions: None.
// Post-conditions: The DVD object is destructed.
// Return: if included
DVD::~DVD() {}

// Borrow a movie (reduce stock by 1)
// Name: borrow
// Purpose: Borrow a movie from the inventory and reduce its stock by 1.
// Pre-conditions: A valid Movie object must be given.
// Post-conditions: If successful, the stock of the movie is reduced by 1.
// Return: True if the movie is borrowed successfully, false otherwise.
bool DVD::borrow(Movie *movie) { return movie->borrowMovie(movie); }

// Return a movie (increase stock by 1)
// Name: returnMovie
// Purpose: Return a borrowed movie to the inventory and increase its stock by 1.
// Pre-conditions: A valid Movie object must be given.
// Post-conditions: If successful, the stock of the movie is increased by 1.
// Return: True if the movie is returned successfully, false otherwise.
bool DVD::returnMovie(Movie *movie) { return movie->returnMovie(movie); }
