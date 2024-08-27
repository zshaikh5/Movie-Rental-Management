// CSS343 Movie Project
// Group 2: Jasleen Kaur Saini, Zaina Shaikh, Maryam Maabreh, Vinisha Bala

// File Name: movieType.h
// Purpose: Declaration of the MovieType class, which defines the interface for different movie types.

#ifndef MOVIETYPE_H
#define MOVIETYPE_H

// Forward declaration of the Movie class
class Movie; 

class MovieType {
public:
  // Operation commands

  // Borrow a movie.
  virtual bool borrow(Movie *movie);

  // Return a movie.
  virtual bool returnMovie(Movie *movie);
};

#endif 
