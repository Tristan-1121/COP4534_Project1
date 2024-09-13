// program/cipher.cpp
#include "cipher.h"

std::string Cipher::encrypt(const std::string& text, const std::string& key) {
    std::string result;
    int keyLength = key.length();
    for (size_t i = 0; i < text.length(); ++i) {
        char textChar = text[i];
        char keyChar = key[i % keyLength];
        char encryptedChar = (textChar - 'a' + (keyChar - 'a')) % 26 + 'a';
        result += encryptedChar;
    }
    return result;
}
