// program/password-manager.h
#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#include <string>
#include <vector>

class PasswordManager {
public:
    void generateRawData(const std::string& filename);
    void generateEncryptedData(const std::string& filename, const std::string& key);

private:
    std::vector<std::string> userIds;
    std::vector<std::string> passwords;

    std::string generateRandomPassword();
    void loadNames(const std::string& filename);
};

#endif // PASSWORD_MANAGER_H

