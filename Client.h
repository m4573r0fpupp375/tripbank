//
// Created by mkondratek on 22.07.17.
//

#ifndef TRIPBANK_CLIENT_H
#define TRIPBANK_CLIENT_H

#include <string>

class Client {
    std::string id;
    double balance;
public:

    Client(std::string, double = 0.0);

    double getBalance();

    void setBalance(double);

    void addToBalance(double);

    std::string getName();

    void rename(std::string);
};


#endif //TRIPBANK_CLIENT_H
