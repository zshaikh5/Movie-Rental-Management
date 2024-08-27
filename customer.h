// CSS343 Movie Project
// Group 2: Jasleen Kaur Saini, Zaina Shaikh, Maryam Maabreh, Vinisha Bala

// File Name: customer.h
// Purpose: Define the Customer class for managing customer information and movie borrowing.

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "movie.h" // Include necessary header file(s)

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Define a struct for representing borrowed movies by customers
typedef struct borrowedMovie {
  borrowedMovie(Movie *movie) : movie(movie){}; // Constructor with initialization list

  Movie *movie = nullptr; // Pointer to the borrowed movie
  bool isBorrowing = true; // Flag indicating if the movie is currently being borrowed
} borrowedMovie;

// Define the Customer class
class Customer {
public:
  static const bool PRINT_ID = true; // Flag for testing purposes

  ~Customer(); // Destructor

  // Member variables
  const int UID; // Unique identifier for the customer
  const std::string firstName; // First name of the customer
  const std::string lastName; // Last name of the customer

  // Constructor
  Customer(int id, std::string fName, std::string lName)
      : UID(id), firstName(fName), lastName(lName){}; // Constructor with initialization list

  // Member functions

  // Check if the customer is currently borrowing a specific movie
  bool isBorrowing(Movie *movie);

  // Borrow a movie
  bool borrowMovie(Movie *movie);

  // Return a borrowed movie
  bool returnMovie(Movie *movie);

  // Factory method to create Customer objects from a file
  static std::vector<Customer *> getCustomers(std::ifstream file);

  // Display the borrowing history of the customer
  void displayHistory();

  // Overload the stream insertion operator to output customer information
  friend std::ostream &operator<<(std::ostream &os, const Customer &customer);

private:
  std::vector<borrowedMovie *> history; // Vector to store all borrowed movies by the customer

  // Helper method to get a borrowedMovie object for a specific movie
  borrowedMovie *getBorrow(Movie *movie); // Returns nullptr if the movie is not found in history
};

#endif
