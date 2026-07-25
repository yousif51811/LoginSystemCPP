#include <iostream>
#include <vector>
#include "Console.hpp"
#include "UserManager.hpp"
#include "main.hpp"
int main(int argc, char* argv[]) 
{
    while (true) {
        std::cout << "What would you like to do?\n";
        std::vector<std::string> options = {"Register", "Login"};
        int selectedindex = Console::PrintOptions(options);
        Console::eraseLines(2);
        if (selectedindex == 1)
            printLogin();
        else 
            printRegister();
    }
}

void printLogin() {
    while (true)
    {
        std::string username;
        std::string password;
        std::cout << "Enter Username: ";
        std::cin  >> username;
        if (!(UserManager::UserAlreadyExists(username))) {
            std::cout << "Username doesn't exist!\n";
            continue;
        }
        std::cout << "Enter Password: ";
        std::cin >> password;
        User user = UserManager::GetUser(username);
        if (user.ValidatePassword(password)) {
            Console::eraseLines(2);
            std::cout << "Welcome " << username << "!\n";
            std::cout << "Your secret sentence: " << UserManager::UnlockSecretSentence(password, user.GetSecretSentenceEncrypted()) << '\n';
            std::exit(0);
        }
        else {
            std::cout << "Invalid password!\n";
            Console::eraseLines(5);
            continue;
        }
        return;
    }
};

void printRegister() {
    std::string username;
    std::string password;
    std::string secretSentence;
    std::cout << "Choose Username: ";
    std::cin >> username;
    std::cout << "Choose Password: ";
    std::cin >> password;
    std::cout << "Choose Secret sentence: ";
    std::getline(std::cin >> std::ws, secretSentence);
    UnEncryptedUser user(username, password, secretSentence);
    UserManager::AddUser(user);
    Console::eraseLines(10);
}
