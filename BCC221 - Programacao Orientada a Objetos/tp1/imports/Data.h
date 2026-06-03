#ifndef DATA_H
#define DATA_H

#include <ostream>

// formato da data dd/mm/aaaa
typedef struct data 
{
    int dia;
    int mes;
    int ano;
} Data;

// sobrecarga do cout
std::ostream& operator<<(std::ostream& out, const Data& d);

#endif