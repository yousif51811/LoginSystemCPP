#include "json.hpp"
#include <unistd.h>
#include "UserManager.hpp"
#include <fstream>
#include <filesystem>
#include "User.hpp"
#include <string>
#include "UnEncryptedUser.hpp"

using json = nlohmann::json;
nlohmann::json UserManager::data;

namespace {
std::filesystem::path DataFile()
{
    std::error_code error;
    const auto executable = std::filesystem::read_symlink("/proc/self/exe", error);
    if (!error)
        return executable.parent_path() / "users.json";

    return "users.json";
}
}

void UserManager::SaveData() {
    std::ofstream file(DataFile());
    file << data.dump(4);
}

void UserManager::EnsureData() {
    const auto dataFile = DataFile();
    if (std::filesystem::exists(dataFile)) // users.json exists already load it
    {
        std::ifstream file(dataFile);
        file >> data;
    } 
    else // Doesn't exist let's create it
    {
        data["users"] = json::array();

        std::ofstream file(dataFile);
        file << data.dump(4);
    }
}

bool UserManager::UserAlreadyExists(const std::string& search ) 
{
    EnsureData();
    for (auto& user : data["users"])
    {
        std::string username = user["username"];
        if (username == search) {
            return true;
        }
    }
    return false;
}
User UserManager::GetUser(const std::string& search) 
{
    EnsureData();
    for (auto& user : data["users"])
    {
        std::string username = user["username"];
        if (username == search) 
            return User(username, user["password_hash"], user["secret_sentence"]);
        
    }
    return User("","","");
}
bool UserManager::AddUser(const UnEncryptedUser& user) {
    EnsureData();
    if (UserAlreadyExists(user.GetUsername())) return false;
    data["users"].push_back({
        {"username", user.GetUsername()},
        {"password_hash", bcrypt::generateHash(user.GetPassword())},
        // Encrypt secret sentence with original password
        {"secret_sentence", EncryptStringWithKey(user.GetSecretSentence(), user.GetPassword())}
    });
    SaveData();
    return true;
}


std::string UserManager::UnlockSecretSentence(const std::string& key, const std::string& encryptedSecretSentence) {
        EnsureData();
        return EncryptStringWithKey(encryptedSecretSentence, key);
}

std::string UserManager::EncryptStringWithKey(const std::string& text, const std::string& key)
{
    // XOR Encryption IS NOT secure, just for learning purposes.
    std::string result = text;

    for (size_t i = 0; i < text.size(); i++)
    {
        result[i] = text[i] ^ key[i % key.size()];
    }

    return result;
}
