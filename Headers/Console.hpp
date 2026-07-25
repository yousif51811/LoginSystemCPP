#include <vector>

class Console {
    private:
        static char getch();
    public:
        static void eraseLines(int count);
        static int PrintOptions(std::vector<std::string> options, int Index = 0);
        static void PressEnterToContinue();
};