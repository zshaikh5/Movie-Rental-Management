// CSS343 Movie Project
// Group 2: Jasleen Kaur Saini, Zaina Shaikh, Maryam Maabreh, Vinisha Bala

#ifndef COMEDYMOVIE_H
#define COMEDYMOVIE_H

#include "movie.h"
#include <string>

class ComedyMovie : public Movie {
public:
  // Constructor for ComedyMovie
  // Parameters:
  // - stock: Initial stock of the movie
  // - director: Director of the movie
  // - title: Title of the movie
  // - year: Release year of the movie
  ComedyMovie(int stock, const std::string &director, const std::string &title, int year)
      : Movie(director, title, year, stock) {}

  // Destructor for ComedyMovie
  ~ComedyMovie() {}

  // Overloaded less than operator for ComedyMovie
  bool operator<(const ComedyMovie &other) const;

  // Overloaded greater than operator for ComedyMovie
  bool operator>(const ComedyMovie &other) const;

  // Overloaded equality operator for ComedyMovie
  bool operator==(const ComedyMovie &other) const;

  // Returns the genre tag for Comedy movies
  char getGenreTag() const override;
};

#endif 
