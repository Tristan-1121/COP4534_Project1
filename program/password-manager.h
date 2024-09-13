#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#include "cipher.h"
#include "hash-table.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class PasswordManager {
public:
    // Parse the names from the file (e.g., names.txt)
    std::vector<std::string> parseNames(const std::string &filename) {
        std::ifstream file(filename);
        std::vector<std::string> names;
        std::string line;

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string name;
            ss >> name;  // Extract only the first column (the surname)
            names.push_back(name);
        }

        return names;
    }

     // Method to load passwords from rawdata.txt
    std::vector<std::string> loadPasswords(const std::string &filename) {
        std::ifstream infile(filename);
        std::vector<std::string> passwords;
        std::string userid, password;

        while (infile >> userid >> password) {
            passwords.push_back(password);  // Store only the password in the vector
        }

        infile.close();
        return passwords;
    }

    // Test combinations of user IDs and passwords
    void testCombinations(const std::vector<std::string> &userIDs, const std::vector<std::string> &passwords, HashTable &hashTable) {
        // Indices of entries to test (1st, 3rd, 5th, 7th, 9th)
        std::vector<int> testIndices = {0, 2, 4, 6, 8};

        std::cout << "Legal Tests:\n";
        for (int index : testIndices) {
            std::string userid = userIDs[index];
            std::string password = passwords[index];
            std::string encryptedPassword = Cipher::encrypt(password, "jones");

            bool match = hashTable.checkPassword(userid, encryptedPassword);
            std::cout << "Userid: " << userid << ", Password(file): " << password
                      << ", Password(table/encrypted): " << encryptedPassword
                      << " - " << (match ? "match" : "no match") << std::endl;
        }

        std::cout << "\nIllegal Tests:\n";
        for (int index : testIndices) {
            std::string userid = userIDs[index];
            std::string password = passwords[index];
            // Modify the first letter to make it an illegal password
            password[0] = (password[0] == 'z') ? 'a' : password[0] + 1;
            std::string encryptedPassword = Cipher::encrypt(password, "jones");

            bool match = hashTable.checkPassword(userid, encryptedPassword);
            std::cout << "Userid: " << userid << ", Password(modified): " << password
                      << ", Password(table/encrypted): " << encryptedPassword
                      << " - " << (match ? "match" : "no match") << std::endl;
        }
    }

    // Generates random passwords (9 characters long, lowercase)
    std::string generateRandomPassword() {
        std::string characters = "abcdefghijklmnopqrstuvwxyz";
        std::string password;

        for (int i = 0; i < 9; ++i) {
            password += characters[rand() % characters.length()];
        }

        return password;
    }

    // Write raw user ID and password to rawdata.txt
    void writeRawData(const std::vector<std::string> &userIDs, const std::string &filename) {
        std::ofstream outfile(filename);

        for (const std::string &userid : userIDs) {
            std::string password = generateRandomPassword();
            outfile << userid << " " << password << std::endl;
        }

        outfile.close();
    }
};

void writeEncryptedData(const std::string& filename, const std::vector<std::string>& data) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    for (const auto& line : data) {
        outfile << line << std::endl;
    }

    outfile.close();
}

#endif
