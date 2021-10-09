#pragma once

#include <string>
#include "Exceptions.h"
class Function
{
public:
    virtual ~Function() = default;
    virtual double operator()(double x) const = 0;
    virtual std::string to_string(const std::string& arg) const = 0;
};
