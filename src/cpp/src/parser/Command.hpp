//
// Created by Kalelzar on 25/03/2020.
//

#ifndef OOPPROJECT_COMMAND_HPP
#define OOPPROJECT_COMMAND_HPP

#include "../io/ScannerContext.hpp"

class Command {
private:
    char *name;
    int argc;
    char **args;
    ScannerContext sc;

    void copy(Command const &other);

public:

    Command(const char *name, int argc, const char **args, ScannerContext sc);

    Command(Command const &other);

    Command &operator=(Command const &other);

    ~Command();

    char *getName() const { return name; }

    int getArgumentCount() const { return argc; }

    char *getArgument(int index) const {
        if (index < 0 || index >= getArgumentCount()) return nullptr;
        return args[index];
    }

    ScannerContext getScannerContext() { return sc; }

};


#endif //OOPPROJECT_COMMAND_HPP
