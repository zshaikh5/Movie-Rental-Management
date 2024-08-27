// CSS343 Movie Project
// Group 2: Jasleen Kaur Saini, Zaina Shaikh, Maryam Maabreh, Vinisha Bala

// File Name: HashTable.cpp
// Purpose: Implementation of the HashTable class for storing customers.

#include "hashTable.h"
#include "customer.h"

#include <iostream>
#include <sstream>
#include <vector>

// Default constructor for HashTable
HashTable::HashTable() : customerList(TABLE_SIZE, nullptr) {}

// Destructor for HashTable
HashTable::~HashTable() {
    // Iterate through each index in the customerList vector
    for (auto &head : customerList) {
        // Delete the linked list starting from the head node
        while (head) {
            node *temp = head; // Store the current head node
            head = head->next; // Move to the next node
            delete temp;       // Delete the current node
        }
    }
}

// Method to build the hash table from a customer file
bool HashTable::build(const std::string &custFilename) {
    std::fstream infile;
    infile.open(custFilename);

    if (!infile.is_open()) {
        return false; // File opening failed
    }

    int uid;
    std::string fName;
    std::string lName;

    std::string currLine;
    while (std::getline(infile, currLine)) {
        std::istringstream iss(currLine);

        if (!(iss >> uid >> lName >> fName)) {
            // Failed to read customer data, skip this line
            std::cout << "Failed to add customer:\n" << currLine << "\n" << std::endl;
            continue;
        } else {
            // Create a new Customer object and add it to the hash table
            Customer *newCustomer = new Customer(uid, fName, lName);
            add(newCustomer);
        }
    }

    return true; // File reading and processing successful
}

// Method to print the contents of the hash table
void HashTable::print() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        node *current = customerList[i];
        while (current) {
            // Print the customer ID stored in the current node
            std::cout << "Customer ID: " << current->customer->UID << std::endl;
            current = current->next; // Move to the next node
        }
    }
}

// Method to add a customer to the hash table
void HashTable::add(Customer *customer) {
    int index = hash(customer->UID); // Calculate the index for the customer ID
    // Create a new node with the customer and insert it at the beginning of the list
    customerList[index] = new node(customer, customerList[index]);
}

// Method to check if the hash table contains a specific customer
bool HashTable::contains(Customer *customer) {
    return containsKey(customer->UID); // Check if the hash table contains the customer by ID
}

// Method to check if the hash table contains a customer with a specific key
bool HashTable::containsKey(int key) {
    return (getByKey(key) != nullptr); // Check if a customer with the given key exists in the hash table
}

// Method to remove a customer from the hash table
bool HashTable::remove(Customer *customer) {
    return removeByKey(customer->UID); // Remove the customer using its ID
}

// Method to remove a customer with a specific key from the hash table
bool HashTable::removeByKey(int customerID) {
    int index = hash(customerID);
    node *current = customerList[index];
    node *prev = nullptr;

    while (current && current->customer->UID != customerID) {
        prev = current;
        current = current->next;
    }

    if (!current) {
        return false; // Customer not found
    }

    if (prev) {
        prev->next = current->next; // Remove the current node from the linked list
    } else {
        customerList[index] = current->next;
    }

    delete current; // Delete the removed node
    return true;    // Removal successful
}

// Method to get a customer by their ID from the hash table
Customer *HashTable::getByKey(int customerID) {
    int index = hash(customerID);
    node *current = customerList[index];

    while (current) {
        if (current->customer->UID == customerID) {
            return current->customer; // Return the customer if found
        }
        current = current->next;
    }

    return nullptr; // Customer not found
}

// Method to calculate the hash index for a given customer ID
int HashTable::hash(int customerID) {
    return customerID % TABLE_SIZE; // Use modulo operation to calculate the index
}
