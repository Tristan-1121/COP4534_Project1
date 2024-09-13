// program/hash-table.h
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>
#include <unordered_map>
#include <list>

class HashTable {
public:
    void loadEncryptedData(const std::string& filename);
    bool verifyPassword(const std::string& userId, const std::string& encryptedPassword);

private:
    std::unordered_map<std::string, std::string> table; // Maps user IDs to encrypted passwords
};

#endif // HASH_TABLE_H

