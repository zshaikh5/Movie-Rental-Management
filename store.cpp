// CSS343 Movie Project
// Group 2: Jasleen Kaur Saini, Zaina Shaikh, Maryam Maabreh, Vinisha Bala

// File Name: store.cpp
// Purpose: Implementing the store class methods and processing the commands from file. 

#include "store.h"

#include "classicMovie.h"
#include "comedyMovie.h"
#include "dramaMovie.h"

// Name: Store Destructor 
// Purpose: Cleans dynamically allocated memory for movies in the store
// Pre-conditions: Store object exists
// Post-conditions: All movies in the store are deleted and the vector is cleared. 
Store::~Store() {
  for (Movie *movie : movies) {
    delete movie;
  }
  movies.clear();
}

// Name: buildFromFiles 
// Purpose: Builds the inventory and customer database from input files and processes commands.
// Pre-conditions: Valid filenames for customers, movies, and commands are present.
// Post-conditions: The store includes customers and movies and the commands are executed. 
// Return: True if all the files are processed sucessfully and false if not.
bool Store::buildFromFiles(const std::string &customerFilename,
                           const std::string &movieFilename,
                           const std::string &commandsFilename) {

  customers.build(customerFilename);
  movies = Movie::build(movieFilename);

  // Execute commands

  std::fstream commandsFile;
  commandsFile.open(commandsFilename);

  if (!commandsFile.is_open()) {
    std::cout << "Failed to open the commands file.\n" << std::endl;
    return false;
  }

  std::string currCommand;
  while (std::getline(commandsFile, currCommand)) {
    // std::cout << "Command: " << currCommand << std::endl; // Delete me
    executeCommand(currCommand);
  }

  return true;
}

// Name: executeCommand  
// Purpose: Executes a command to modify the store or display any information.
// Pre-conditions: A valid command string is provided
// Post-conditions: The command is executed, modifying the store/displaying information.
// Return: Return true if the command was executed successfully and false if not. 
// Helper functions for buildFromFiles. Returns false if input is invalid.
bool Store::executeCommand(const std::string &command) {
  std::istringstream iss(command);
  char commandType;

  if (iss >> commandType) {

    if (commandType == 'I') { // Display inventory
      printInventory();
      return true;

    } else {
      int customerID;

      if (iss >> customerID) {
        Customer *customer = customers.getByKey(customerID);

        if (customer == nullptr) {
          std::cout
              << "Cannot display history of non-existent customer. (No UID="
              << customerID << ").\n"
              << std::endl;
          return false;
        }

        if (commandType == 'H') { // Display customer history
          displayCustomerHistory(customer);
          return true;

        } else {
          char mediaType;
          iss >> mediaType;

          std::string movieInfo;
          std::getline(iss >> std::ws, movieInfo);
          Movie *movie = returnEquivelent(movieInfo);

          if (movie == nullptr) {
            // std::cout << "Cannot borrow/return a movie that DNE in the
            // store.\n"        << std::endl;
            return false;
          }

          if (commandType == 'B') { // Borrow
            if (borrowMovie(customer, movie)) {
              // std::cout << "Sucessfully borrowed movie." << std::endl; //
              // DELETE
              return true;
            }
            std::cout << "Failed to borrow movie." << std::endl;

          } else if (commandType == 'R') { // Return
            if (returnMovie(customer, movie)) {
              // std::cout << "Sucessfully returned movie." << std::endl; //
              // DELETE
              return true;
            }

            std::cout << "Failed to return movie." << std::endl;
          }
        }
      }
    }
  }

  return false;
}

// Name: printInventory 
// Purpose: Displays the current inventory of movies in the store.
// Pre-conditions: None
// Post-conditions: The inventory of movies is outputted to the console.
// Return: None
void Store::printInventory() {
  std::cout << "\n=============================\nInventory:\n" << std::endl;

  for (Movie *movie : movies) {
    std::cout << movie->str() << "\n" << std::endl;
  }

  std::cout << "[End of Inventory Display]\n=============================\n"
            << std::endl;
}

// Name: displayCustomerHistory 
// Purpose: Displays the rental history of a specific customer.
// Pre-conditions: A valid customer is present. 
// Post-conditions: The customer's rental history is displayed
// Return: None
void Store::displayCustomerHistory(Customer *customer) {
  customer->displayHistory();
}

// Name: borrowMovie 
// Purpose: Allows a customer to borrow a movie if its in stock.
// Pre-conditions: A valid customer and movie object are present.
// Post-conditions: The movie is marked as borrowed if successful 
// Return: True if the movie was successfully borrowed, false if not.
bool Store::borrowMovie(Customer *customer, Movie *movie) {

  if (movie->borrowMovie(movie)) {
    return customer->borrowMovie(movie);

  } else {
    std::cout << "Cannot borrow movie, as it is out of stock.\n" << std::endl;
  }

  return false;
}

// Name: returnMovie
// Purpose: Allows a customer to return a borrowed movie.
// Pre-conditions: A valid customer and movie object are present.
// Post-conditions: The movie is marked as returned by the customer if successful.
// Return: True if the movie was successfully returned, false if not.
bool Store::returnMovie(Customer *customer, Movie *movie) {
  if (movie->returnMovie(movie)) {
    return customer->returnMovie(movie);
  }

  std::cout << "Failed to return movie.\n" << std::endl;
  return false;
}

// Name: contains (Movie)
// Purpose: Checks if a specific movie exists in the store's inventory.
// Pre-conditions: A valid movie object is present.
// Post-conditions: None.
// Return: true if the movie exists in the inventory, false if it does not.
bool Store::contains(Movie *movie) {
  return (returnEquivelent(movie) != nullptr);
}

// Name: contains (Customer)
// Purpose: Checks if a specific customer exists in the store's database.
// Pre-conditions: A valid customer object.
// Post-conditions: None.
// Return: True if the customer exists in the database, false if it doesn't.
bool Store::contains(Customer *customer) {
  return customers.contains(customer);
}

// Name: returnEquivelent (Movie object)
// Purpose: Finds an equivalent movie in the store's inventory.
// Pre-conditions: A valid movie object.
// Post-conditions: None.
// Return: A pointer to the equivalent movie if found, nullptr if not found.
Movie *Store::returnEquivelent(Movie *movieToFind) {
  for (Movie *movie : movies) {
    if (Movie::equal(movie, movieToFind)) {
      return movie;
    }
  }

  return nullptr;
}

// Name: returnEquivelent (Movie info string)
// Purpose: Finds an equivalent movie in the store's inventory based on a string description.
// Pre-conditions: A valid movie description string is required.
// Post-conditions: None.
// Return: A pointer to the equivalent movie if found, nullptr if it is not found.
Movie *Store::returnEquivelent(std::string movieInfo) {
  // First seperate into movie info
  char genre;
  std::string title = "";
  std::string name = "";
  int year = 0;

  std::istringstream iss(movieInfo);

  iss >> genre;

  switch (genre) {
  case 'C':
    iss >> year >> std::ws;
    std::getline(iss, name);
    break;

  case 'F':
    std::getline(iss, title, ',');
    iss >> year;
    break;

  case 'D':
    std::getline(iss, name, ',');
    std::getline(iss, title);
    break;

  default: // Invalid tag
    return nullptr;
  }

  // Now find if matching movie exists
  for (Movie *movie : movies) {
    if (movie->getGenreTag() == genre) {
      if (movie->title == title) {
        if (genre == 'F') {
          if (dynamic_cast<ComedyMovie *>(movie)->year == year) {
            return movie;
          }

        } else if (genre == 'C') { // Classic
          ClassicMovie *classic = dynamic_cast<ClassicMovie *>(movie);

          if (classic->majorActor == name && classic->year == year) {
            return movie;
          }

        } else if (genre == 'D') {
          if (dynamic_cast<DramaMovie *>(movie)->director == name) {
            return movie;
          }
        }
      }
    }
  }

  return nullptr;
}