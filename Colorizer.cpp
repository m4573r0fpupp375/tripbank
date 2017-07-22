//
// Created by mkondratek on 22.07.17.
//

#include <ostream>
#include "Colorizer.h"

#ifdef _WIN32

#include <windows.h>

const std::map<std::string, unsigned short int> Colorizer::colors =
        {{"RESET",       7},
         {"BLACK",       0},              /* Black */
         {"RED",         12},             /* Red */
         {"GREEN",       10},             /* Green */
         {"YELLOW",      14},             /* Yellow */
         {"BLUE",        9},              /* Blue */
         {"MAGENTA",     13},             /* Magenta */
         {"CYAN",        11},             /* Cyan */
         {"WHITE",       15},             /* White */
         };

void Colorizer::setColor(std::string color) {
    if (color.substr(0, 4) == "BOLD") {
        color = color.substr(4);
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colors.at(color));
}

#elif __unix__

const std::map<std::string, std::string> Colorizer::colors =
        {{"RESET",       "\033[0m"},
         {"BLACK",       "\033[30m"},             /* Black */
         {"RED",         "\033[31m"},             /* Red */
         {"GREEN",       "\033[32m"},             /* Green */
         {"YELLOW",      "\033[33m"},             /* Yellow */
         {"BLUE",        "\033[34m"},             /* Blue */
         {"MAGENTA",     "\033[35m"},             /* Magenta */
         {"CYAN",        "\033[36m"},             /* Cyan */
         {"WHITE",       "\033[37m"},             /* White */
         {"BOLDBLACK",   "\033[1m\033[30m"},      /* Bold Black */
         {"BOLDRED",     "\033[1m\033[31m"},      /* Bold Red */
         {"BOLDGREEN",   "\033[1m\033[32m"},      /* Bold Green */
         {"BOLDYELLOW",  "\033[1m\033[33m"},      /* Bold Yellow */
         {"BOLDBLUE",    "\033[1m\033[34m"},      /* Bold Blue */
         {"BOLDMAGENTA", "\033[1m\033[35m"},      /* Bold Magenta */
         {"BOLDCYAN",    "\033[1m\033[36m"},      /* Bold Cyan */
         {"BOLDWHITE",   "\033[1m\033[37m"}       /* Bold White */
        };

void Colorizer::setColor(std::string color) {
    if (colors.find(color) == colors.end()) {
        color = "RESET";
    }
    stream << colors.at(color);
}

#else
void Colorizer::setColor(std::string) {}

#endif