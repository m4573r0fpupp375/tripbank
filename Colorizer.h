//
// Created by mkondratek on 22.07.17.
//

#ifndef TRIPBANK_COLORIZER_H
#define TRIPBANK_COLORIZER_H

#include <map>

class Colorizer {
    std::ostream &stream;
    static const std::map<std::string, std::string> colors;

public:

    Colorizer(std::ostream &ostr) : stream(ostr) {};

    void setColor(std::string);
};


#endif //TRIPBANK_COLORIZER_H
