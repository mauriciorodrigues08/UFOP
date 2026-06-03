// Data.cpp
#include "../imports/Data.h"

std::ostream& operator<<(std::ostream& out, const Data& data) {
    out << (data.dia < 10 ? "0" : "") << data.dia << "/"
        << (data.mes < 10 ? "0" : "") << data.mes << "/"
        << data.ano;
    return out;
}