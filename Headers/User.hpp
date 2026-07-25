#pragma once
#include <string>

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

    const std::string& GetSecretSentence() const {
        return secretSentence;
    }
};