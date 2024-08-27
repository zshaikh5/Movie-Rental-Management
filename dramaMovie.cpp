// CSS343 Movie Project
// Group 2: Jasleen Kaur Saini, Zaina Shaikh, Maryam Maabreh, Vinisha Bala

// File Name: dramaMovie.cpp
// Purpose: Implementation of the DramaMovie class methods.

#include "dramaMovie.h"

// Name: getGenreTag
// Purpose: Get the genre tag for drama movies.
// Pre-conditions: None
// Post-conditions: Returns the genre tag 'D' for drama movies.
// Return: 'D' (char)
char DramaMovie::getGenreTag() const { return 'D'; }

// Name: operator<
// Purpose: Compare two drama movies to determine if one is less than the other.
// Pre-conditions: Both movies must be valid DramaMovie objects.
// Post-conditions: None
// Return: True if this movie is less than the other, false otherwise.
bool DramaMovie::operator<(const DramaMovie &other) const {
  // First compare by genre.
  int genreComparison = getGenrePriority(other.getGenreTag()) - getGenrePriority(getGenreTag());

  if (genreComparison > 0) {
    return true;
  } else if (genreComparison < 0) {
    return false;
  }

  // If same genre, compare by director and title.
  if (director != other.director) {
    return director < other.director;
  }
  return title < other.title;
}

// Name: operator>
// Purpose: Compare two drama movies to determine if one is greater than the other.
// Pre-conditions: Both movies must be valid DramaMovie objects.
// Post-conditions: None
// Return: True if this movie is greater than the other, false otherwise.
bool DramaMovie::operator>(const DramaMovie &other) const {
  return other < *this;
}

// Name: operator==
// Purpose: Compare two drama movies to determine if they are equal.
// Pre-conditions: Both movies must be valid DramaMovie objects.
// Post-conditions: None
// Return: True if both movies are equal, false otherwise.
bool DramaMovie::operator==(const DramaMovie &other) const {
  return getGenreTag() == other.getGenreTag() && director == other.director &&
         title == other.title && year == other.year;
}
