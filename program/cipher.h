#ifndef CIPHER_H
#define CIPHER_H

#include <string>

class Cipher {
public:
    static std::string encrypt(const std::string &text, const std::string &key) {
        std::string result;
        size_t keyLength = key.length();  // Use size_t for keyLength

        for (size_t i = 0; i < text.length(); ++i) {  // Use size_t for loop variable
            char plainChar = text[i];
            char keyChar = key[i % keyLength];
            char encryptedChar = (plainChar - 'a' + keyChar - 'a') % 26 + 'a';
            result += encryptedChar;
        }

        return result;
    }
};

#endif
