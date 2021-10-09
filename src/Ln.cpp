#include "Ln.h"

#include <cmath>

double Ln::operator()(double x) const
{
    if (x < 0)
    {
        throw NegativeArgument();
    }
    return std::log(x);
}

std::string Ln::to_string(const std::string& arg) const
{
    return "ln(" + arg + ")";
}
