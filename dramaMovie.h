// CSS343 Movie Project
// Group 2: Jasleen Kaur Saini, Zaina Shaikh, Maryam Maabreh, Vinisha Bala

// File Name: dramaMovie.h
// Purpose: Declaration of the DramaMovie class, derived from the Movie class.

#ifndef DRAMAMOVIE_H
#define DRAMAMOVIE_H

#include "movie.h"
#include <string>

class DramaMovie : public Movie {
public:
  // Constructor for DramaMovie
  // Parameters:
  // - stock: Initial stock of the movie
  // - director: Director of the movie
  // - title: Title of the movie
  // - year: Release year of the movie
  // - Movie class constructor
  DramaMovie(int stock, const std::string &director, const std::string &title, int year)
      : Movie(director, title, year, stock) {}

  // Destructor
  ~DramaMovie() {}

  // Operator methods for comparisons
  bool operator<(const DramaMovie &other) const;
  bool operator>(const DramaMovie &other) const;
  bool operator==(const DramaMovie &other) const;

  // Get the genre tag for drama movies
  char getGenreTag() const override;
};

#endif
