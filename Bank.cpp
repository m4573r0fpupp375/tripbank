#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "Client.cpp"

using namespace std;

class Bank
{
    vector <Client> members;
    vector <string> commands;
    string msg;
    bool saved;
    bool needHelp;

public:

    Bank()
    {
        fstream file;
        file.open("data.txt", ios::in);
        while(!file.eof())
        {
            saved=true;
            string name;
            file>>name;
            float balance;
            file>>balance;
            Client client(name, balance);
            members.push_back(client);
            msg="";
        }
        file.close();
        file.open("commands.txt", ios::in);
        while(!file.eof())
        {
            string temp;
            getline(file, temp);
            commands.push_back(temp);
        }
        file.close();
        needHelp=false;
    }

    void updateData()
    {
        fstream file;
        file.open("data.txt", ios::out);
        for(int i=0; i<members.size()-1; ++i) file<<members[i].id<<" "<<members[i].balance<<endl;
        file<<members[members.size()-1].id<<" "<<members[members.size()-1].balance;
        file.close();
        saved=true;
    }

    void showCommands()
    {
        for(int i=0;i<commands.size();++i)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            if(i%2==1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
            cout<<commands[i];
            if(i%2==1) cout<<endl;
            else cout <<" - ";
        }
        cout<<endl;
    }

    void addMember(string name)
    {
        if(!memberExists(name))
        {
            Client temp(name);
            members.push_back(temp);
            saved=false;
        }
        else msg="> MEMBER ALREADY EXISTS!\n";
    }

    bool memberExists(string name)
    {
        for(int i=0; i<members.size(); ++i) if(members[i].id==name) return true;
        return false;
    }

    bool memberExists(string name, vector <string> & names)
    {
        for(int i=0; i<names.size(); ++i) if(names[i]==name) return true;
        msg="> NO SUCH NAME\n";
        return false;
    }

    void removeMember(string name)
    {
        if(memberExists(name))
        {
            cout<<members.size();
            for(int i=0; i<members.size(); ++i)
            {
                if(members[i].id==name)
                {
                    members.erase(members.begin()+i);
                    break;
                }
            }
            saved=false;
        }
        else msg="> NO SUCH NAME\n";
    }

    void showData()
    {
        cout<<msg;
        if(needHelp) showCommands();
        needHelp=false;
        msg="";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),79);
        cout<<" ID / NAME         / BALANCE \n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        for(int i=0; i<members.size(); ++i)
        {
            members[i].fixBalance();
            if(i%2==1)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
            string dist="", m=" ";
            int j=13-members[i].id.length();
            for(; j>0; --j) dist+=" ";
            if(members[i].balance>0) m+=" ";
            if(i<10 )cout<<" "<<i<<"  | "<<members[i].id<<dist<<"|"<<m<<members[i].fixed<<endl;
            else cout<<" "<<i<<" | "<<members[i].id<<dist<<"|"<<m<<members[i].fixed<<endl;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    }

    void pay(string from, string bal, vector <string> without)
    {
        if(memberExists(from))
        {
            int i;
            for(i=0; i<members.size(); ++i) if(from==members[i].id) break;
            float rest, balance=(float)atof(bal.c_str());
            cout<<without.size();
            cout<<"A";
            int x;
            cin>>x;
            rest=balance/(members.size()-without.size());
            members[i].balance+=balance;
            for(int j=0; j<members.size(); ++j) if(!memberExists(members[j].id, without)) members[j].balance-=rest;
            saved=false;
        }
        else msg="> NO SUCH NAME\n";
    }

    void pay(string from, string to, string bal)
    {
        if(memberExists(from) && memberExists(to))
        {
            int i;
            for(i=0; i<members.size(); ++i) if(from==members[i].id) break;
            members[i].balance+=(float)atof(bal.c_str());
            for(i=0; i<members.size(); ++i) if(to==members[i].id) break;
            members[i].balance-=(float)atof(bal.c_str());
            saved=false;
        }
        else msg="> NO SUCH NAME\n";
    }

    void pay(string from, string bal)
    {
        if(memberExists(from))
        {
            int i;
            for(i=0; i<members.size(); ++i) if(from==members[i].id) break;
            float rest, balance=(float)atof(bal.c_str());
            rest=balance/members.size();
            members[i].balance+=balance;
            for(int j=0; j<members.size(); ++j) members[j].balance-=rest;
            saved=false;
        }
        else msg="> NO SUCH NAME\n";
    }

    void setAllToZero()
    {
        for(int i=0; i<members.size(); ++i) members[i].balance=0;
        saved=false;
    }

    void removeAll()
    {
        members.clear();
        saved=false;
    }

    bool handleInput(vector <string> input)
    {
        if(input[0]=="add") addMember(input[1]);
        else if(input[0]=="remove") removeMember(input[1]);
        //else if(input[0]=="show") showData();
        else if(input[0]=="update") updateData();
        else if(input[0]=="pay")
        {
            if(input.size()==3)
            {
                pay(input[1],input[2]);
            }
            else if(input.size()==4)
            {
                pay(input[1],input[2],input[3]);
            }
            else if(input[3]=="exclude")
            {
                cout<<"A";
                int x;
                cin>>x;
                vector <string> without(input.begin()+4, input.end());
                pay(input[1],input[2], without);
            }
        }
        else if(input[0]=="exit")
        {
            if(!saved)
            {
                cout<<"\a";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
                cout<<"\nDATA UNSAVED! DO YOU WANT TO SAVE? (y/n)\n";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                cout<<">> ";
                char temp;
                cin>>temp;
                if(temp=='n') return false;
                else if(temp=='y')
                {
                    updateData();
                    return false;
                }
            }
            return false;
        }
        else if(input[0]=="clear")
        {
            if(input[1]=="members")
            {
                cout<<"\a";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
                cout<<"\nMEMBERS WILL BE CLEARED! ARE YOU SURE? (y/n)\n";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                cout<<">> ";
                char temp;
                cin>>temp;
                if(temp=='y')
                {
                    removeAll();
                    saved=false;
                }
            }
            else if(input[1]=="balance")
            {
                cout<<"\a";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
                cout<<"\nBALANCE WILL BE CLEARED! ARE YOU SURE? (y/n)\n";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                cout<<">> ";
                char temp;
                cin>>temp;
                if(temp=='y')
                {
                    setAllToZero();
                    saved=false;
                }
            }
        }
        else if(input[0]=="help") needHelp=true;
        else if(input[0]=="hej" || input[0]=="czesc" || input[0]=="siema" || input[0]=="witam") msg=">> Witam! :D\n";
        else if((input[0]=="co" || input[0]=="jak") && input[1]=="tam?") msg=">> W porzadku :) A tam?\n";
        else if(input[0]=="twoja" && input[1]=="stara") msg=">> Twoja starsza!\n";
        return true;
    }
};
