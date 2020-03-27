#ifndef OOPPROJECT_NOVALUEEXCEPTION_HPP
#define OOPPROJECT_NOVALUEEXCEPTION_HPP

#include <iostream>
#include <exception>
using namespace std;

class NoValueException: public exception
{
    virtual const char* what() const throw()
    {
            return "Attempted to access null value.";
    }
};

#endif //OOPPROJECT_NOVALUEEXCEPTION_HPP
