// CSS343 Movie Project
// Group 2: Jasleen Kaur Saini, Zaina Shaikh, Maryam Maabreh, Vinisha Bala

// File Name: HashTable.h
// Purpose: Definition of the HashTable class for storing customers.

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "customer.h" // Include the Customer class header

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Define a struct for a linked list node in the hash table
struct node {
  Customer *customer; // Pointer to a customer object
  node *next = nullptr; // Pointer to the next node in the linked list

  // Constructor to initialize node with a customer and next node pointer
  node(Customer *customer, node *next = nullptr)
      : customer(customer), next(next) {}

  // Destructor to delete the customer object when node is destroyed
  ~node() { delete customer; }
};

// Define the HashTable class
class HashTable {
public:
  static const int TABLE_SIZE = 100; // Example size for the hash table, can be adjusted

  HashTable(); // Default constructor
  ~HashTable(); // Destructor

  // Method to print the contents of the hash table
  void print();

  // Method to build the hash table from a customer file
  bool build(const std::string &custFilename);

  // Method to add a customer to the hash table
  void add(Customer *customer);

  // Method to remove a customer from the hash table
  bool remove(Customer *customer);

  // Method to remove a customer by their ID from the hash table
  bool removeByKey(int customerID);

  // Method to get a customer from the hash table by their ID
  Customer *getByKey(int customerID);

  // Method to check if the hash table contains a specific customer
  bool contains(Customer *customer);

  // Method to check if the hash table contains a customer with a specific ID
  bool containsKey(int key);

private:
  std::vector<node *> customerList; // Vector to store linked list nodes for customers

  // Hash function to calculate the index in the hash table based on the customer ID
  int hash(int customerID);
};

#endif 
