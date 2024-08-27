// CSS343 Movie Project
// Group 2: Jasleen Kaur Saini, Zaina Shaikh, Maryam Maabreh, Vinisha Bala

// File Name: movie.cpp
// Purpose: Implementation of movie-related classes and functions.

#include "movie.h"

#include "classicMovie.h"
#include "comedyMovie.h"
#include "dramaMovie.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

// Comparator struct to compare Movie pointers based on genre and specifics
struct CompareMoviePtrs {
  bool operator()(Movie *lhs, Movie *rhs) const {
    // First compare by genre
    int genreComparison = lhs->getGenrePriority(rhs->getGenreTag()) -
                          lhs->getGenrePriority(lhs->getGenreTag());

    if (genreComparison < 0) {
      return true; // Left movie has higher priority
    } else if (genreComparison > 0) {
      return false; // Right movie has higher priority
    }

    // Handle cases where genres are equal
    if (lhs->getGenreTag() == 'F') {
      ComedyMovie *left = dynamic_cast<ComedyMovie *>(lhs);
      ComedyMovie *right = dynamic_cast<ComedyMovie *>(rhs);
      return (*left < *right); // Compare based on specific criteria for Comedy

    } else if (lhs->getGenreTag() == 'D') {
      DramaMovie *left = dynamic_cast<DramaMovie *>(lhs);
      DramaMovie *right = dynamic_cast<DramaMovie *>(rhs);
      return (*left < *right); // Compare based on specific criteria for Drama

    } else {
      ClassicMovie *left = dynamic_cast<ClassicMovie *>(lhs);
      ClassicMovie *right = dynamic_cast<ClassicMovie *>(rhs);
      return (*left < *right); // Compare based on specific criteria for Classic
    }
  }
};

// Method to build a vector of Movie pointers from a file
// Name: build
// Purpose: Read movie data from a file and create Movie objects.
// Pre-conditions: Valid file path provided.
// Post-conditions: Vector of Movie pointers containing movie objects from the file.
// Return: Vector of Movie pointers.
std::vector<Movie *> Movie::build(const std::string &movieFilename) {
  std::vector<Movie *> movies;
  std::ifstream file(movieFilename);

  if (!file.is_open()) {
    std::cerr << "Error: file cannot be opened " << movieFilename << std::endl;
    return movies; // Return empty vector if file cannot be opened
  }

  std::string line;
  while (std::getline(file, line)) {
    Movie *movie = Movie::createMovie(line); // Create Movie object from file line
    if (movie != nullptr) {
      movies.push_back(movie); // Add valid movies to the vector
    }
  }
  file.close();

  CompareMoviePtrs cmp;
  std::sort(movies.begin(), movies.end(), cmp); // Sort movies based on criteria

  return movies;
}

// Method to create a Movie object from a string line
// Name: createMovie
// Purpose: Parse a string line to create a Movie object.
// Pre-conditions: Valid string line with movie data.
// Post-conditions: Movie object created based on the data in the string line.
// Return: Pointer to the created Movie object.
Movie *Movie::createMovie(const std::string &fileLine) {
  std::istringstream ss(fileLine);
  char genre;
  ss >> genre;
  ss.ignore(1, ',');

  int stock;
  std::string director, title;
  int year;

  if (genre == 'F') { // Comedy tag
    if (ss >> stock) {
      ss.ignore(1, ',');
      std::getline(ss, director, ',');
      std::getline(ss, title, ',');

      if (ss >> year) {
        return new ComedyMovie(stock, director, title, year); // Create ComedyMovie
      }
    }

  } else if (genre == 'D') { // Drama tag
    if (ss >> stock) {
      ss.ignore(1, ',');
      std::getline(ss, director, ',');
      std::getline(ss, title, ',');

      if (ss >> year) {
        return new DramaMovie(stock, director, title, year); // Create DramaMovie
      }
    }

  } else if (genre == 'C') { // Classic tag
    if (ss >> stock) {
      ss.ignore(1, ',');
      std::getline(ss, director, ',');
      std::getline(ss, title, ',');

      std::string actorF;
      std::string actorL;
      int month;
      if (ss >> actorF >> actorL >> month >> year) {
        ClassicMovie *pClassic;
        pClassic = new ClassicMovie(stock, director, title, month, year,
                                    (actorF + " " + actorL));

        return pClassic;
      }
    }

  } else { // Invalid tag
    std::cerr << "Error: Invalid movie genre code '" << genre << "'."
              << std::endl;
  }

  return nullptr;
}

// Method to get the available stock of a Movie
// Name: getStock
// Purpose: Get the current stock of the Movie.
// Pre-conditions: Movie object initialized.
// Post-conditions: None.
// Return: Current available stock of the Movie.
int Movie::getStock() const { return availableStock; }

// Method to borrow a Movie
// Name: borrowMovie
// Purpose: Borrow the Movie if available.
// Pre-conditions: Movie object initialized.
// Post-conditions: Stock of the Movie decreased if borrowed successfully.
// Return: True if the Movie was successfully borrowed, false otherwise.
bool Movie::borrowMovie(Movie *movie) {
  if (availableStock > 0) {
    availableStock--;
    return true; // Movie borrowed successfully
  }
  return false; // Movie not available for borrowing
}

// Method to return a Movie
// Name: returnMovie
// Purpose: Return a borrowed Movie.
// Pre-conditions: Movie object initialized.
// Post-conditions: Stock of the Movie increased after return.
// Return: Always true as a Movie is returned.
bool Movie::returnMovie(Movie *movie) {
  availableStock++;
  return true; // Movie returned successfully
}

// Method to get the genre priority for sorting
// Name: getGenrePriority
// Purpose: Get the priority of a genre for sorting purposes.
// Pre-conditions: Valid genre code ('C', 'D', 'F') provided.
// Post-conditions: None.
// Return: Priority value for sorting.
// Note: Greater priority implies greater weight in sorting.
int Movie::getGenrePriority(char genre) {
  switch (genre) {
  case 'C':
    return 1; // Classic
  case 'D':
    return 2; // Drama
  case 'F':
    return 3; // Comedy
  }

  return 0; // For invalid genre codes
}

// Operator overload for outputting Movie information
// Name: operator<<
// Purpose: Output Movie information to an output stream.
// Pre-conditions: None
std::ostream &operator<<(std::ostream &os, const Movie &movie) {
  os << movie.str(); // Calls the str() function to get the formatted string representation of the movie
  return os;
}

// Name: str
// Purpose: Generate a string representation of the Movie object.
// Pre-conditions: None
// Post-conditions: None
// Return: A string containing the formatted movie information.
std::string Movie::str() const {
  std::string genre(1, getGenreTag()); // Get the genre tag of the movie
  std::string fullStr =
      genre + ", " + title + ", " + director + // Construct the full string with movie details
      ", year: " + std::to_string(year) +
      ".\nAvailable stock: " + std::to_string(availableStock) + ".";

  return fullStr; // Return the formatted string
}

// Name: equal
// Purpose: Compare two Movie objects for equality based on their attributes.
// Pre-conditions: lMovie and rMovie are valid pointers to Movie objects.
// Post-conditions: None
// Return: True if the movies are equal, false otherwise.
bool Movie::equal(Movie *lMovie, Movie *rMovie) {
  CompareMoviePtrs cmp; // Create a CompareMoviePtrs object for comparison

  if (cmp(lMovie, rMovie) || cmp(rMovie, lMovie)) { // Use the comparison operator to check equality
    return false;
  }

  return true; // Return true if the movies are equal
}

