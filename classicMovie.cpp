// CSS343 Movie Project
// Group 2: Jasleen Kaur Saini, Zaina Shaikh, Maryam Maabreh, Vinisha Bala

#include "classicMovie.h"

// Returns the genre tag for Classic movies
// Pre-conditions: None
// Post-conditions: None
// Return: 'C' as the genre tag for Classic movies
char ClassicMovie::getGenreTag() const {
  return 'C';
}

// Overloaded less than operator for Classic movies
// Pre-conditions: Valid ClassicMovie object to compare with
// Post-conditions: None
// Return: True if this ClassicMovie is less than the other ClassicMovie, false otherwise
bool ClassicMovie::operator<(const ClassicMovie &other) const {
  // First compare by genre.
  int genreComparison =
      getGenrePriority(other.getGenreTag()) - getGenrePriority(getGenreTag());

  if (genreComparison > 0) {
    return true;
  } else if (genreComparison < 0) {
    return false;
  }

  // If same genre, then compare by attributes.
  if (year != other.year) {
    return year < other.year;
  } else if (month != other.month) {
    return month < other.month;
  }
  return majorActor < other.majorActor;
}

// Overloaded greater than operator for Classic movies
// Pre-conditions: Valid ClassicMovie object to compare with
// Post-conditions: None
// Return: True if this ClassicMovie is greater than the other ClassicMovie, false otherwise
bool ClassicMovie::operator>(const ClassicMovie &other) const {
  return other < *this;
}

// Overloaded equality operator for Classic movies
// Pre-conditions: Valid ClassicMovie object to compare with
// Post-conditions: None
// Return: True if both ClassicMovies are equal, false otherwise
bool ClassicMovie::operator==(const ClassicMovie &other) const {
  return getGenreTag() == other.getGenreTag() && year == other.year &&
         month == other.month && majorActor == other.majorActor;
}
