#include "MerkelMain.h"
#include <iostream>

int main()
{
    MerkelMain advisorbot;
    advisorbot.init();

    std::string command;
    while (true)
    {
        std::cout << "advisorbot> Please enter a command, or 'help' for a list of commands" << std::endl;
        std::getline(std::cin, command);

        if (command == "exit")
            break;

        advisorbot.processUserCommand(command);
    }

    return 0;
}
