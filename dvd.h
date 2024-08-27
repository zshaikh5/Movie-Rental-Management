// CSS343 Movie Project
// Group 2: Jasleen Kaur Saini, Zaina Shaikh, Maryam Maabreh, Vinisha Bala

// File Name: dvd.h
// Purpose: Definition of the DVD class, a derived class of MovieType.

#ifndef DVD_H
#define DVD_H

#include "movieType.h"

class DVD : public MovieType {
public:
  DVD(); // Default constructor
  ~DVD(); // Destructor

  // Borrow a movie (reduce stock by 1)
  bool borrow(Movie *movie) override;

  // Return a movie (increase stock by 1)
  bool returnMovie(Movie *movie) override;
};

#endif
