//
// Created by mkondratek on 22.07.17.
//

#ifndef TRIPBANK_BANK_H
#define TRIPBANK_BANK_H

#include <vector>
#include "Client.h"
#include "Colorizer.h"

class Bank {
    Colorizer colorizer;
    std::vector<Client> members;
    std::vector<std::string> commands;
    std::string msg;
    bool saved;
    bool needHelp;

public:

    Bank();

    void updateData();

    void showCommands();

    void addMember(std::string);

    bool memberExists(std::string);

    bool memberExists(std::string, std::vector<std::string> &);

    void removeMember(std::string);

    void showData();

    void pay(std::string, std::string, std::vector<std::string> &);

    void pay(std::string, std::string, std::string);

    void pay(std::string, std::string);

    void setAllToZero();

    void removeAll();

    bool handleInput(std::vector<std::string>);
};


#endif //TRIPBANK_BANK_H
