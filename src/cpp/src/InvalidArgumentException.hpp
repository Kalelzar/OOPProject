#ifndef OOPPROJECT_INVALIDARGUMENTEXCEPTION_HPP
#define OOPPROJECT_INVALIDARGUMENTEXCEPTION_HPP

#include <iostream>
#include <cstring>
#include <exception>

using namespace std;

class InvalidArgumentException : public exception {
private:
    static const char *DEFAULT_MESSAGE;

    virtual const char *what() const throw() {
        return msg;
    }

    char *msg;

public:
    InvalidArgumentException(const char *_msg) {
        msg = new char[strlen(_msg) + 1];
        strcpy(msg, _msg);
    }

    ~InvalidArgumentException() {
        delete[] msg;
    }

    InvalidArgumentException() : InvalidArgumentException(DEFAULT_MESSAGE) {}

};


#endif //OOPPROJECT_INVALIDARGUMENTEXCEPTION_HPP
