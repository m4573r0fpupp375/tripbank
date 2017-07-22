//
// Created by mkondratek on 22.07.17.
//

#include "Client.h"

Client::Client(std::string name, double _balance) {
    balance = _balance;
    id = name;
}

double Client::getBalance() {
    return balance;
}

void Client::setBalance(double _balance) {
    balance = _balance;
}

void Client::addToBalance(double _value) {
    balance += _value;
}

std::string Client::getName() {
    return id;
}

void Client::rename(std::string name) {
    id = name;
}