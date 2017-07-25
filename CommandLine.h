//
// Created by mkondratek on 25.07.17.
//

#ifndef TRIPBANK_COMMANDLINE_H
#define TRIPBANK_COMMANDLINE_H


#include <istream>
#include <vector>

class CommandLine {
    std::vector<std::string> history;
    unsigned long int historyIterator;
    unsigned long charCount;
    std::string command;

    void setCursor(unsigned long int);

public:
    CommandLine();

    std::string getCommand();

    void clear();
};


#endif //TRIPBANK_COMMANDLINE_H
