#include <iostream>
#include <vector>
#include "Console.hpp"

int main(int argc, char* argv[]) 
{
    std::cout << "What would you like to do? (W/S)\n";
    std::vector<std::string> options = {"Register", "Login"};
    Console::PrintOptions(options);
    Console::eraseLines(2);
}
