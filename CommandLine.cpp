//
// Created by mkondratek on 25.07.17.
//

//key map
#define KEY_BACKSPACE 8
#define KEY_ENTER 10
#define KEY_ESCAPE 27
#define KEY_SPACE 32
#define KEY_L_BRACKET 91
#define KEY_UP -2
#define KEY_DO -3
#define KEY_RI -4
#define KEY_LE -5
#define KEY_TILDE 126
#define KEY_DELETE 127
#define KEY_DOT 46

#define RM_LAST "\b \b"

#include <iostream>
#include "CommandLine.h"

//function getkey found at
//https://stackoverflow.com/questions/2984307/how-to-handle-key-pressed-in-a-linux-console-in-c
#include <termios.h>
#include <cstring>

bool _isalnum(int c) {
    return (c <= 'Z' && c >= 'A')
           or (c <= 'z' && c >= 'a')
           or (c <= '9' && c >= '0');
}

int getkey() {
    int character;
    termios orig_term_attr;
    termios new_term_attr;

    /* set the terminal to raw mode */
    tcgetattr(fileno(stdin), &orig_term_attr);
    memcpy(&new_term_attr, &orig_term_attr, sizeof(termios));
    new_term_attr.c_lflag &= ~(ECHO | ICANON);
    new_term_attr.c_cc[VTIME] = 0;
    new_term_attr.c_cc[VMIN] = 0;
    tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);

    /* read a character from the stdin stream without blocking */
    /*   returns EOF (-1) if no character is available */
    character = fgetc(stdin);

    /* restore the original terminal attributes */
    tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);

    return character;
}

int ansiClear(int c) {
    if (c == KEY_ESCAPE) {
        switch (getkey()) {
            case KEY_L_BRACKET:
                switch (getkey()) {
                    case 'A':
                        return KEY_UP;
                    case 'B':
                        return KEY_DO;
                    case 'C':
                        return KEY_RI;
                    case 'D':
                        return KEY_LE;
                    case '1':
                        //f10
                    case '2':
                        //insert
                    case '3':
                        //delete
                    case '4':
                        //f12
                    case '5':
                        //pgup
                    case '6':
                        //pgdown

                        getkey(); //tilde
                        return -1;


                    default:
                        return -1;
                }
            default:
                return -1;
        }
    }

    return c;
}

void trim(std::string &cmd) {
    if (cmd.length() == 0) return;

    for (unsigned long int i = cmd.length() - 1; i > 0; --i) {
        if (cmd[i - 1] == cmd[i] && cmd[i] == ' ') {
            cmd.erase(cmd.begin() + i - 1);
        }
    }

    unsigned long i = 0;
    while (cmd[i] == ' ') i++;
    cmd = cmd.substr(i);
    i = cmd.length() - 1;
    while (cmd[i] == ' ') i--;
    cmd = cmd.substr(0, i + 1);
}

std::string CommandLine::getCommand() {
    command = "";
    int next;

    historyIterator = history.size();
    charCount = 0;

    do {
        do {
            do { next = getkey(); } while (next == -1);
            next = ansiClear(next);
//            std::cout << ">" <<next<< "<";
        } while (next == -1);

        if (next == KEY_DELETE) {
            if (charCount > 0) {
                for (unsigned long int i = charCount; i < command.length(); ++i) {
                    command[i - 1] = command[i];
                }
                unsigned long int tmp = charCount;

                command[command.length() - 1] = ' ';
                clear();

                charCount = tmp - 1;
                std::cout << command;

                setCursor(charCount);
            }
        } else if (next == KEY_ENTER) {
            trim(command);
            break;
        } else if (next == KEY_UP) {
            //get previous command from history

            if (historyIterator == 0) continue;

            historyIterator--;

            clear();

            command = history[historyIterator];
            charCount = command.length();
            std::cout << command;

        } else if (next == KEY_DO) {
            //get next command from history

            if (historyIterator == history.size()) continue;

            historyIterator++;

            if (historyIterator == history.size()) {
                clear();
                command = "";
            } else {
                clear();
                command = history[historyIterator];
                charCount = command.length();
                std::cout << command;
            }

        } else if (next == KEY_RI) {
            if (charCount < command.length()) {
                unsigned long int tmp = charCount;
                clear();
                std::cout << command;
                charCount = tmp + 1;
                setCursor(charCount);
            }
        } else if (next == KEY_LE) {
            if (charCount > 0) {
                std::cout << '\b';
                charCount--;
            }
        } else if (_isalnum(next) || next == KEY_SPACE || next == KEY_DOT) {
            if (charCount == command.length()) {
                command.push_back((char) next);
                std::cout << (char) next;
                charCount++;
            } else {
                if (command[command.length() - 1 != ' ']) {
                    command.push_back(' ');
                }

                for (unsigned long int i = command.length() - 1; i > charCount; --i) {
                    command[i] = command[i - 1];
                }

                command[charCount] = (char) next;
                unsigned long int tmp = charCount;
                clear();
                std::cout << command;
                charCount = tmp + 1;
                setCursor(charCount);
            }

        } else {
        }

    } while (true);

    if (command != "") {
        history.push_back(command);
    }

    return command;
}

CommandLine::CommandLine() {
    historyIterator = 0;
    charCount = 0;
}

void CommandLine::clear() {
    while (charCount) {
        std::cout << RM_LAST;
        charCount--;
    }
}

void CommandLine::setCursor(unsigned long int x) {
    for (int i = 0; i < command.length() - x; i++) {
        std::cout << '\b';
    }
}
