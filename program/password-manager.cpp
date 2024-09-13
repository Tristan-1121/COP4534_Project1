// program/password-manager.cpp
#include "password-manager.h"
#include "cipher.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib> // for rand()

void PasswordManager::generateRawData(const std::string& filename) {
    loadNames("names.txt"); // Load names from the provided file

    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    for (size_t i = 0; i < userIds.size(); ++i) {
        outfile << userIds[i] << " " << generateRandomPassword() << std::endl;
    }

    outfile.close();
}

void PasswordManager::generateEncryptedData(const std::string& filename, const std::string& key) {
    std::ifstream infile("rawdata.txt");
    if (!infile.is_open()) {
        std::cerr << "Error opening rawdata.txt for reading" << std::endl;
        return;
    }

    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    std::string userId, password;
    while (infile >> userId >> password) {
        std::string encryptedPassword = Cipher::encrypt(password, key);
        outfile << userId << " " << encryptedPassword << std::endl;
    }

    infile.close();
    outfile.close();
}

std::string PasswordManager::generateRandomPassword() {
    static const char alphanum[] = "abcdefghijklmnopqrstuvwxyz";
    std::string password;
    for (int i = 0; i < 9; ++i) {
        password += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return password;
}

void PasswordManager::loadNames(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string userId;
        ss >> userId; // Read only the first column (userid)

        userIds.push_back(userId);
    }

    infile.close();
}
