#include <string>
#include "json.hpp"
#include "User.hpp"
#include "UnEncryptedUser.hpp"
class UserManager {
private:
    static void EnsureData();
    static void SaveData();
    static std::string EncryptStringWithKey(const std::string& text, const std::string& key);
    static std::string ToHex(const std::string& input);
    static nlohmann::json data;
public:
    static bool UserAlreadyExists(const std::string& search);
    static bool ValidateCredentials(const std::string& username, const std::string& password);
    static std::string UnlockSecretSentence(const std::string& key, const std::string& encryptedSecretSentence);
    static bool AddUser(const UnEncryptedUser& user);
    static User GetUser(const std::string& search);
};