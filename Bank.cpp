//
// Created by mkondratek on 22.07.17.
//

#include <fstream>
#include <iostream>
#include <regex>
#include "Bank.h"

Bank::Bank() : colorizer(std::cout) {
    std::fstream file;
    file.open("../data.txt", std::ios::in);
    while (!file.eof()) {
        saved = true;
        std::string name;
        file >> name;
        double balance;
        file >> balance;
        Client client(name, balance);
        members.push_back(client);
        msg = "";
    }
    file.close();
    file.open("../commands.txt", std::ios::in);
    while (!file.eof()) {
        std::string temp;
        getline(file, temp);
        commands.push_back(temp);
    }
    file.close();
    needHelp = false;
}

void Bank::updateData() {
    std::fstream file;
    file.open("../data.txt", std::ios::out);
    for (int i = 0; i < members.size() - 1; ++i) {
        file << members[i].getName() << " " << members[i].getBalance() << std::endl;
    }
    file << members[members.size() - 1].getName() << " " << members[members.size() - 1].getBalance();
    file.close();
    saved = true;
}

void Bank::showCommands() {
    for (int i = 0; i < commands.size(); ++i) {
        if (i % 2 == 0) colorizer.setColor("WHITE");
        else colorizer.setColor("RESET");

        std::cout << commands[i];
        if (i % 2 == 1) std::cout << std::endl;
        else std::cout << " - ";
    }
    std::cout << std::endl;
}

void Bank::addMember(std::string name) {
    if (memberExists(name)) {
        msg = ">> ERROR: MEMBER ALREADY EXISTS!\n";
        return;
    }

    std::smatch tmp;
    if (std::regex_search(name, tmp, std::regex("[a-zA-Z]*"))) {
        if (tmp[0] != name) {
            msg = ">> ERROR: MEMBER NAME CAN CONTAINS ONLY LETTERS\n";
            return;
        }
    } else {
        msg = ">> ERROR: INVALID MEMBER NAME\n";
        return;
    }

    //check if name is a command
    for (int i = 0; i < commands.size(); i += 2) {
        std::size_t pos = commands[i].find(" ");
        std::string cmd = commands[i];
        if (pos != std::string::npos) {
            cmd = name.substr(0, pos);
        }

        if (cmd == name) {
            msg = ">> ERROR: MEMBER NAME CANNOT BE A COMMAND!\n";
            return;
        }
    }

    Client temp(name);
    members.push_back(temp);
    saved = false;
}

bool Bank::memberExists(std::string name) {
    for (int i = 0; i < members.size(); ++i) if (members[i].getName() == name) return true;
    return false;
}

bool Bank::memberExists(std::string name, std::vector<std::string> &names) {
    for (int i = 0; i < names.size(); ++i) if (names[i] == name) return true;
    msg = ">> ERROR: NO SUCH NAME\n";
    return false;
}

void Bank::removeMember(std::string name) {
    if (memberExists(name)) {
        std::cout << members.size();
        for (int i = 0; i < members.size(); ++i) {
            if (members[i].getName() == name) {
                members.erase(members.begin() + i);
                break;
            }
        }
        saved = false;
    } else msg = ">> ERROR: NO SUCH NAME\n";
}

void Bank::showData() {
    colorizer.setColor("BOLDWHITE");
    std::cout << " ID / NAME         / BALANCE \n";
    colorizer.setColor("RESET");
    for (int i = 0; i < members.size(); ++i) {
        if (i % 2 == 0) colorizer.setColor("WHITE");
        else colorizer.setColor("RESET");
        std::string dist = "", m = " ";
        unsigned int j = (unsigned int) (13 - members[i].getName().length());
        for (; j > 0; --j) dist += " ";
        if (members[i].getBalance() > 0) m += " ";
        if (i < 10)
            std::cout << " " << i << "  | " << members[i].getName() << dist << "|" << m << members[i].getBalance()
                      << std::endl;
        else
            std::cout << " " << i << " | " << members[i].getName() << dist << "|" << m << members[i].getBalance()
                      << std::endl;
    }
    std::cout << "-----------------------------\n";
    colorizer.setColor("WHITE");
    if (needHelp) {
        showCommands();
        needHelp = false;
    }
    colorizer.setColor("RED");
    std::cout << msg;
    colorizer.setColor("RESET");
    msg = "";
}

void Bank::pay(std::string from, std::string bal, std::vector<std::string> &without) {
    if (memberExists(from)) {
        int i;
        for (i = 0; i < members.size(); ++i) if (from == members[i].getName()) break;
        double rest, balance = atof(bal.c_str());
        std::cout << without.size();
        std::cout << "A";
        int x;
        std::cin >> x;
        rest = balance / (members.size() - without.size());
        members[i].addToBalance(balance);
        for (int j = 0; j < members.size(); ++j)
            if (!memberExists(members[j].getName(), without))
                members[j].addToBalance(-rest);
        saved = false;
    } else msg = ">> ERROR: NO SUCH NAME\n";
}

void Bank::pay(std::string from, std::string to, std::string _balance) {
    if (memberExists(from) && memberExists(to)) {
        int i;
        for (i = 0; i < members.size(); ++i) if (from == members[i].getName()) break;
        members[i].addToBalance(atof(_balance.c_str()));
        for (i = 0; i < members.size(); ++i) if (to == members[i].getName()) break;
        members[i].addToBalance(-atof(_balance.c_str()));
        saved = false;
    } else msg = ">> ERROR: NO SUCH NAME\n";
}

void Bank::pay(std::string from, std::string _balance) {
    if (memberExists(from)) {
        int i;
        for (i = 0; i < members.size(); ++i) if (from == members[i].getName()) break;
        double rest, balance = atof(_balance.c_str());
        rest = balance / members.size();
        members[i].addToBalance(balance);
        for (int j = 0; j < members.size(); ++j) members[j].addToBalance(-rest);
        saved = false;
    } else msg = ">> ERROR: NO SUCH NAME\n";
}

void Bank::setAllToZero() {
    for (int i = 0; i < members.size(); ++i) {
        members[i].setBalance(0);
    }
    saved = false;
}

void Bank::removeAll() {
    members.clear();
    saved = false;
}

bool Bank::handleInput(std::vector<std::string> input) {
    if (input[0] == "add") addMember(input[1]);
    else if (input[0] == "remove") removeMember(input[1]);
    else if (input[0] == "show") showData();
    else if (input[0] == "update") updateData();
    else if (input[0] == "pay") {
        if (input.size() == 3) {
            pay(input[1], input[2]);
        } else if (input.size() == 4) {
            pay(input[1], input[2], input[3]);
        } else if (input[3] == "exclude") {
            std::cout << "A";
            int x;
            std::cin >> x;
            std::vector<std::string> without(input.begin() + 4, input.end());
            pay(input[1], input[2], without);
        }
    } else if (input[0] == "exit") {
        if (!saved) {
            std::cout << "\a";
            colorizer.setColor("RED");
            std::cout << "\nDATA UNSAVED! DO YOU WANT TO SAVE? (y/n)\n";
            colorizer.setColor("WHITE");
            std::cout << ">> ";
            char temp;
            std::cin >> temp;
            if (temp == 'n') return false;
            else if (temp == 'y') {
                updateData();
                return false;
            }
        }
        return false;
    } else if (input[0] == "clear") {
        if (input[1] == "members") {
            std::cout << "\a";
            colorizer.setColor("RED");
            std::cout << "\nMEMBERS WILL BE CLEARED! ARE YOU SURE? (y/n)\n";
            colorizer.setColor("WHITE");
            std::cout << ">> ";
            char temp;
            std::cin >> temp;
            if (temp == 'y') {
                removeAll();
                saved = false;
            }
        } else if (input[1] == "balance") {
            std::cout << "\a";
            colorizer.setColor("RED");
            std::cout << "\nBALANCE WILL BE CLEARED! ARE YOU SURE? (y/n)\n";
            colorizer.setColor("WHITE");
            std::cout << ">> ";
            char temp;
            std::cin >> temp;
            if (temp == 'y') {
                setAllToZero();
                saved = false;
            }
        }
    } else if (input[0] == "help") {
        needHelp = true;
    }

    return true;
}