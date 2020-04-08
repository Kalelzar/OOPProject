#ifndef OOPPROJECT_WRONGTOKENTYPEEXCEPTION_HPP
#define OOPPROJECT_WRONGTOKENTYPEEXCEPTION_HPP

#include <iostream>
#include <cstring>
#include <exception>

using namespace std;

class WrongTokenTypeException : public exception {
private:
    char *msg;

public:

    virtual const char *what() const throw() {
        return msg;
    }

    WrongTokenTypeException(const char *_msg) {
        msg = new char[strlen(_msg) + 1];
        strcpy(msg, _msg);
    }

    ~WrongTokenTypeException() {
        delete[] msg;
    }

};


#endif //OOPPROJECT_WRONGTOKENTYPEEXCEPTION_HPP
