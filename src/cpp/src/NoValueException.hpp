#ifndef OOPPROJECT_NOVALUEEXCEPTION_HPP
#define OOPPROJECT_NOVALUEEXCEPTION_HPP

#include <iostream>
#include <cstring>
#include <exception>

using namespace std;

class NoValueException : public exception {
private:
    static const char* DEFAULT_MESSAGE;
    virtual const char *what() const throw() {
        return msg;
    }
    char* msg;

public:
    NoValueException(const char* _msg){
        msg = new char[strlen(_msg)+1];
        strcpy(msg, _msg);
    }

    ~NoValueException(){
        delete [] msg;
    }

    NoValueException() : NoValueException(DEFAULT_MESSAGE){}

};


#endif //OOPPROJECT_NOVALUEEXCEPTION_HPP
