// program/hash-table.cpp
#include "hash-table.h"
#include <fstream>
#include <sstream>
#include <iostream>

void HashTable::loadEncryptedData(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string userId, encryptedPassword;
    while (infile >> userId >> encryptedPassword) {
        table[userId] = encryptedPassword;
    }

    infile.close();
}

bool HashTable::verifyPassword(const std::string& userId, const std::string& encryptedPassword) {
    auto it = table.find(userId);
    if (it != table.end()) {
        return it->second == encryptedPassword;
    }
    return false;
}

