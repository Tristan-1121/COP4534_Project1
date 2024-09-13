// program/cipher.h
#ifndef CIPHER_H
#define CIPHER_H

#include <string>

class Cipher {
public:
    static std::string encrypt(const std::string& text, const std::string& key);
};

#endif // CIPHER_H

