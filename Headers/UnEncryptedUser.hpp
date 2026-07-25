#pragma once

#include <string>

class UnEncryptedUser {
private:
    std::string username;
    std::string password;
    std::string secretSentence;

public:
    UnEncryptedUser(std::string u, std::string p, std::string s)
        : username(u), password(p), secretSentence(s) {}

    const std::string& GetUsername() const {
        return username;
    }

    const std::string& GetPassword() const {
        return password;
    }

    const std::string& GetSecretSentence() const {
        return secretSentence;
    }
};