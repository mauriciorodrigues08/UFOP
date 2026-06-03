#ifndef HORARIO_H
#define HORARIO_H

#include <ostream>

// formato da data dd/mm/aaaa
typedef struct horario
{
    int horas;
    int minutos;
} Horario;

// sobrecarga do cout
std::ostream& operator<<(std::ostream& out, const Horario& horario);

#endif