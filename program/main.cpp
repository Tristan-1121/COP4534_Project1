// program/main.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "password-manager.h"
#include "hash-table.h"
#include "cipher.h"

int main() {
    PasswordManager passwordManager;

    // Generate raw data and encrypted data
    passwordManager.generateRawData("rawdata.txt");
    std::string encryptionKey = "jones"; // Replace with your key
    passwordManager.generateEncryptedData("encrypteddata.txt", encryptionKey);

    // Create and populate hash table
    HashTable hashTable;
    hashTable.loadEncryptedData("encrypteddata.txt");

    // Test cases
    std::ifstream infile("rawdata.txt");
    if (!infile.is_open()) {
        std::cerr << "Error opening file for reading: rawdata.txt" << std::endl;
        return 1;
    }

    std::string line;
    int count = 0;
    while (std::getline(infile, line) && count < 9) {
        std::istringstream ss(line);
        std::string userId, password;
        ss >> userId >> password;

        // Test 5 correct attempts (first, third, fifth, seventh, and ninth)
        if (count % 2 == 0) {
            std::string encryptedPassword = Cipher::encrypt(password, encryptionKey);
            bool match = hashTable.verifyPassword(userId, encryptedPassword);
            std::cout << "Legal:" << std::endl;
            std::cout << "Userid: " << userId
                      << " Password(file): " << password
                      << " Password(table/un): " << encryptedPassword
                      << " Result: " << (match ? "match" : "no match") << std::endl;
        }
        // Test 5 incorrect attempts (same user IDs with modified passwords)
        else {
            std::string wrongPassword = password;
            wrongPassword[0] = (wrongPassword[0] == 'a') ? 'b' : 'a'; // Simple modification
            std::string encryptedWrongPassword = Cipher::encrypt(wrongPassword, encryptionKey);
            bool match = !hashTable.verifyPassword(userId, encryptedWrongPassword);
            std::cout << "Illegal:" << std::endl;
            std::cout << "Userid: " << userId
                      << " Password(mod): " << wrongPassword
                      << " Password(table/un): " << encryptedWrongPassword
                      << " Result: " << (match ? "no match" : "match") << std::endl;
        }

        count++;
    }

    infile.close();
    return 0;
}

