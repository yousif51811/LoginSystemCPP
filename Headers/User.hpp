#pragma once
#include <string>
#include "bcrypt.h"

class User {
private:
    std::string username;
    std::string passwordHash;
    std::string secretSentence;

public:
    User(std::string u, std::string p, std::string s)
        : username(u), passwordHash(p), secretSentence(s) {}

    const std::string& GetUsername() const {
        return username;
    }
    const std::string& GetPasswordHash() const {
        return passwordHash;
    }

    const std::string& GetSecretSentenceEncrypted() const {
        return secretSentence;
    }
    const bool ValidatePassword(std::string password) {
        return bcrypt::validatePassword(password, GetPasswordHash()); 
    }

    
};