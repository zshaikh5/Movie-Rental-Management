// CSS343 Movie Project
// Group 2: Jasleen Kaur Saini, Zaina Shaikh, Maryam Maabreh, Vinisha Bala

#ifndef CLASSICMOVIE_H
#define CLASSICMOVIE_H

#include "movie.h"
#include <string>

class ClassicMovie : public Movie {
public:
  const std::string majorActor; // Major actor in the classic movie
  const int month;              // Release month of the classic movie

  // Constructor for ClassicMovie
  // Parameters:
  // - stock: Initial stock of the movie
  // - director: Director of the movie
  // - title: Title of the movie
  // - month: Release month of the movie
  // - year: Release year of the movie
  // - majorActor: Major actor in the movie
  ClassicMovie(int stock, const std::string &director, const std::string &title,
               int month, int year, const std::string &majorActor)
      : Movie(director, title, year, stock), majorActor(majorActor), month(month) {}

  // Destructor for ClassicMovie
  ~ClassicMovie() {}

  // Overloaded less than operator for ClassicMovie
  bool operator<(const ClassicMovie &other) const;

  // Overloaded greater than operator for ClassicMovie
  bool operator>(const ClassicMovie &other) const;

  // Overloaded equality operator for ClassicMovie
  bool operator==(const ClassicMovie &other) const;

  // Returns the genre tag for Classic movies
  char getGenreTag() const override;
};

#endif 
