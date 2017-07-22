//
// Created by mkondratek on 22.07.17.
//

#ifndef TRIPBANK_COLORIZER_H
#define TRIPBANK_COLORIZER_H

#include <map>

class Colorizer {
#ifdef __WIN32
    static const std::map<std::string, unsigned short int> colors;
#elif __unix__
    static const std::map<std::string, std::string> colors;
#endif

    std::ostream &stream;

public:

    Colorizer(std::ostream &ostr) : stream(ostr) {};

    void setColor(std::string);
};


#endif //TRIPBANK_COLORIZER_H
