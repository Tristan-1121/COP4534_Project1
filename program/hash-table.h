#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>
#include <vector>
#include <iostream>
#include <list>
#include <fstream>

// HashTable to store user IDs and encrypted passwords
class HashTable {
private:
    static const int TABLE_SIZE = 10;  // Size of the hash table
    std::vector<std::list<std::pair<std::string, std::string>>> table;  // Each bucket stores pairs of <userID, encryptedPassword>

public:
    // Constructor: Initialize the hash table with empty lists
    HashTable() {
        table.resize(TABLE_SIZE);
    }

    // Hash function for generating index from a user ID
    int hashFunction(const std::string &userid) {
        int hashValue = 0;
        for (char c : userid) {
            hashValue += c;
        }
        return hashValue % TABLE_SIZE;
    }

    // Insert a user ID and its encrypted password into the hash table
    void insert(const std::string &userid, const std::string &encryptedPassword) {
        int index = hashFunction(userid);
        table[index].push_back({userid, encryptedPassword});
    }

    // Check if a password matches the stored encrypted password for a given user ID
    bool checkPassword(const std::string &userid, const std::string &encryptedPassword) {
        int index = hashFunction(userid);
        for (const auto &entry : table[index]) {
            if (entry.first == userid && entry.second == encryptedPassword) {
                return true;
            }
        }
        return false;
    }

    // Load the encrypted data from a file and populate the hash table
    void loadEncryptedData(const std::string &filename) {
        std::ifstream file(filename);
        std::string userid, encryptedPassword;

        while (file >> userid >> encryptedPassword) {
            insert(userid, encryptedPassword);
        }

        file.close();
    }
};

#endif
