// CSS343 Movie Project
// Group 2: Jasleen Kaur Saini, Zaina Shaikh, Maryam Maabreh, Vinisha Bala

#include "customer.h"

#include <iostream>
#include <set>
#include <sstream>
#include <vector>

// Destructor for Customer class
// Pre-conditions: None
// Post-conditions: Frees memory allocated for borrowedMovie objects
// Return: if included
Customer::~Customer() {
  for (borrowedMovie *CustMovie : history) {
    delete CustMovie;
  }
  history.clear();
}

// Checks if the customer is currently borrowing a specific movie
// Pre-conditions: Valid Movie object
// Post-conditions: None
// Return: True if the customer is currently borrowing the movie, false otherwise
bool Customer::isBorrowing(Movie *movie) {
  for (borrowedMovie *bMovie : history) {
    if (Movie::equal(movie, bMovie->movie)) {
      return true;
    }
  }
  return false;
}

// Attempts to borrow a movie for the customer
// Pre-conditions: Valid Movie object
// Post-conditions: Adds a borrowedMovie object to the customer's history if successful
// Return: True if the movie was successfully borrowed, false otherwise
bool Customer::borrowMovie(Movie *movie) {
  borrowedMovie *bMovie = getBorrow(movie);
  if (bMovie != nullptr) {
    if (bMovie->isBorrowing == true) {
      std::cout << "Customer is already borrowing the Movie." << std::endl;
      return false;
    } else {
      bMovie->isBorrowing = true;
      return true;
    }
  }

  borrowedMovie *newBorrow = new borrowedMovie(movie);
  history.push_back(newBorrow);

  return true;
}

// Attempts to return a borrowed movie for the customer
// Pre-conditions: Valid Movie object
// Post-conditions: Updates the borrowedMovie object's status if successful
// Return: True if the movie was successfully returned, false otherwise
bool Customer::returnMovie(Movie *movie) {
  borrowedMovie *bMovie = getBorrow(movie);

  if (bMovie != nullptr) {
    if (bMovie->isBorrowing == true) {
      bMovie->isBorrowing = false;
      return true;
    } else {
      std::cout << "Customer already returned Movie.\n" << std::endl;
      return false;
    }
  }

  std::cout << "Customer cannot return a never-borrowed movie.\n" << std::endl;
  return false;
}

// Displays the borrowing history of the customer
// Pre-conditions: None
// Post-conditions: None
// Return: if included
void Customer::displayHistory() {
  std::cout << "Borrowing History of " << lastName << ", " << firstName << ": ";
  std::cout << "(" << history.size() << " total)\n" << std::endl;

  for (borrowedMovie *bMovie : history) {
    std::string oStr = "(Prev. Borrowed) ";

    if (bMovie->isBorrowing) {
      oStr = "(Cur. Borrowing) ";
    }

    oStr += bMovie->movie->title;
    std::cout << oStr << "\n" << std::endl;
  }

  std::cout << "---------------\n" << std::endl;
}

// Overloaded stream insertion operator for Customer class
std::ostream &operator<<(std::ostream &os, const Customer &customer) {
  if (customer.PRINT_ID) {
    os << std::string("[ID: ") << std::to_string(customer.UID)
       << std::string("] ");
  }

  os << customer.firstName << std::string(" ") << customer.lastName;
  return os;
}

// Helper method to get a borrowedMovie object for a specific movie
// Pre-conditions: Valid Movie object
// Post-conditions: None
// Return: Pointer to the borrowedMovie object if found, nullptr otherwise
borrowedMovie *Customer::getBorrow(Movie *movie) {
  for (borrowedMovie *bMovie : history) {
    if (Movie::equal(movie, bMovie->movie)) {
      return bMovie;
    }
  }

  return nullptr;
}

// Factory method to create Customer objects from a file stream
// Pre-conditions: Valid input file stream
// Post-conditions: Creates Customer objects based on file contents
// Return: Vector of Customer pointers
std::vector<Customer *> Customer::getCustomers(std::ifstream infile) {
  std::vector<Customer *> customers;
  std::set<int> addedIDs;

  int UID;
  std::string firstName;
  std::string lastName;

  std::string currLine;
  while (std::getline(infile, currLine)) {
    std::istringstream iss(currLine);

    if (iss >> UID >> lastName >> firstName) {
      if (addedIDs.count(UID) == 0) { // Don't add duplicates
        addedIDs.insert(UID);

        Customer *newCustomer = new Customer(UID, firstName, lastName);
        customers.push_back(newCustomer);
      }
    } else { // Skip line on fail
      std::cout << "Failed to add customer:\n" << currLine << "\n" << std::endl;
      continue;
    }
  }

  return customers;
}
