#include <iostream>
#include <string>
#include <vector>
#include "Bank.h"
#include "CommandLine.h"

#ifdef _WIN32
#include <windows.h>
#elif __linux__
#elif __unix__ // all unices not caught above
#else
#error "Unknown compiler"
#endif

std::vector<std::string> splitCommand(std::string str) {
    std::vector<std::string> temp;
    size_t pos = str.find(" ");
    while (pos != std::string::npos) {
        std::string found = str.substr(0, pos);
        temp.push_back(found);
        str = str.substr(pos + 1);
        pos = str.find(" ");
    }
    temp.push_back(str);
    return temp;
}

void clear() {
#ifdef _WIN32
    std::system("CLS");
#else
    std::system("clear");
#endif
}

int main() {
    Bank bank;
    CommandLine commandLine;
    std::vector<std::string> command;

    do {
        std::string input = "";

        clear();
        bank.showData();
        std::cout << ">> ";

#ifdef _WIN32
        getline(std::cin, input);
#else
        input = commandLine.getCommand();
#endif

        if (input == "") continue;
        command = splitCommand(input);

    } while (bank.handleInput(command));

    clear();

    return 0;
}
