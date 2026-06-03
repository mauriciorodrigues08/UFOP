#include "../imports/Horario.h"

std::ostream& operator<<(std::ostream& out, const Horario& horario)
{
    out << (horario.horas < 10 ? "0" : "") << horario.horas 
        << ":"
        << (horario.minutos < 10 ? "0" : "") << horario.minutos;

    return out;
}