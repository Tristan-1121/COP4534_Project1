#include "password-manager.h"
#include "hash-table.h"
#include <iostream>

int main() {
    PasswordManager pm;
    HashTable ht;

    // Step 1: Parse names from file
    std::vector<std::string> userIDs = pm.parseNames("names.txt");

    // Step 2: Write raw data with random passwords
    pm.writeRawData(userIDs, "rawdata.txt");

    // Step 3: Load encrypted data into hash table
    ht.loadEncryptedData("encrypteddata.txt");

    // Step 4: Load passwords from rawdata.txt
    std::vector<std::string> passwords = pm.loadPasswords("rawdata.txt");

    // Step 5: Test legal and illegal password combinations
    pm.testCombinations(userIDs, passwords, ht);

    return 0;
}
