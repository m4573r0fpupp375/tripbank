#include <iostream>
#include <string>
#include <vector>
#include "Bank.h"

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

int main() {
    Bank bank;
    std::vector<std::string> command;

    while (true) {
        std::string input="";

#ifdef _WIN32
        std::system("CLS");
#else
        std::system("clear");
#endif

        bank.showData();
        std::cout << ">> ";
        getline(std::cin, input);
        command = splitCommand(input);
        if (!bank.handleInput(command)) break;
    }

    return 0;
}
