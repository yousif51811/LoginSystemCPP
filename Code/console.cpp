#include <iostream>
#include <vector>
#include <termios.h>
#include <unistd.h>
#include "console.hpp"
#include <cstdlib>

// Copied off stackoverflow
char Console::getch()
{
    char c;

    termios oldt{};
    tcgetattr(STDIN_FILENO, &oldt);

    termios newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    std::cin.get(c);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return c;
}

// Thanks to (https://stackoverflow.com/questions/61919292/c-how-do-i-erase-a-line-from-the-console) :
// Erases `count` lines, including the current line
void Console::eraseLines(int count) {
    if (count > 0) {
        std::cout << "\x1b[2K"; // Delete current line
        // i=1 because we included the first line
        for (int i = 1; i < count; i++) {
            std::cout
            << "\x1b[1A" // Move cursor up one
            << "\x1b[2K"; // Delete the entire line
        }
        std::cout << "\r"; // Resume the cursor at beginning of line
    }
}

int Console::PrintOptions(std::vector<std::string> options, int Index) 
{
    auto select = [&]() -> int {
        eraseLines(options.size() + 1);
        return Index;
    };

    while (true) 
    {
        for (int i = 0; i < options.size(); i++) {
            if (Index == i)  {
                std::cout << "> \x1B[96m";
                
            }
                
            std::cout << options.at(i) << "\033[0m\t\t\n";
        }
        char c = getch();
        if (c == '\033') // Escape (Which is the start of an arrow key)
        {
            char c2 = getch();

            if (c2 == '[')
            {
                char c3 = getch();

                if (c3 == 'A' && Index > 0) // Up
                    Index--;
                else if (c3 == 'B' && Index < options.size() - 1) // Down
                    Index++;
                else if (c3 == 'C')
                    return select();
                
            }
        }
        else if (c == '\r' || c == '\n') 
            return select();
            
        eraseLines(options.size() + 1);
    }
}


