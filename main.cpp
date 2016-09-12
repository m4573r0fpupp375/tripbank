#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include "Bank.cpp"

using namespace std;

vector <string> splitCommand(string str)
{
    vector <string> temp;
    size_t pos=str.find(" ");
    while(pos!=string::npos)
    {
        string found=str.substr(0,pos);
        temp.push_back(found);
        str=str.substr(pos+1);
        pos=str.find(" ");
    }
    temp.push_back(str);
    return temp;
}

int main()
{
    Bank bank;
    vector <string> command;

    while(true)
    {
        string input;
        system("CLS");
        bank.showData();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),79);
        cout<<"-----------------------------\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        cout<<">> ";
        getline(cin,input);
        command=splitCommand(input);
        if(!bank.handleInput(command)) break;
    }
    return 0;
}
