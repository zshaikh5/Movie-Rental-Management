// CSS343 Movie Project
// Group 2: Jasleen Kaur Saini, Zaina Shaikh, Maryam Maabreh, Vinisha Bala

#include "comedyMovie.h"

// Returns the genre tag for Comedy movies
// Pre-conditions: None
// Post-conditions: None
// Return: 'F' as the genre tag for Comedy movies
char ComedyMovie::getGenreTag() const {
  return 'F';
}

// Overloaded less than operator for Comedy movies
// Pre-conditions: Valid ComedyMovie object to compare with
// Post-conditions: None
// Return: True if this ComedyMovie is less than the other ComedyMovie, false otherwise
bool ComedyMovie::operator<(const ComedyMovie &other) const {
  // First compare by genre.
  int genreComparison =
      getGenrePriority(other.getGenreTag()) - getGenrePriority(getGenreTag());

  if (genreComparison > 0) {
    return true;
  } else if (genreComparison < 0) {
    return false;
  }

  // If same genre, then compare by attributes.
  if (title != other.title) {
    return title < other.title;
  }
  return year < other.year;
}

// Overloaded greater than operator for Comedy movies
// Pre-conditions: Valid ComedyMovie object to compare with
// Post-conditions: None
// Return: True if this ComedyMovie is greater than the other ComedyMovie, false otherwise
bool ComedyMovie::operator>(const ComedyMovie &other) const {
  return other < *this;
}

// Overloaded equality operator for Comedy movies
// Pre-conditions: Valid ComedyMovie object to compare with
// Post-conditions: None
// Return: True if both ComedyMovies are equal, false otherwise
bool ComedyMovie::operator==(const ComedyMovie &rhs) const {
  if (getGenreTag() != rhs.getGenreTag()) {
    return false;
  }

  const ComedyMovie &other = static_cast<const ComedyMovie &>(rhs);
  return title == other.title && year == other.year;
}
