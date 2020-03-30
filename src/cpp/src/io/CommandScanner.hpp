//
// Created by Kalelzar on 25/03/2020.
//

#ifndef OOPPROJECT_COMMANDSCANNER_HPP
#define OOPPROJECT_COMMANDSCANNER_HPP

#include<iostream>
#include "ScannerContext.hpp"
#include "../parser/Command.hpp"

namespace Hotel {


    class CommandScanner {
    private:
        ScannerContext sc;
        std::istream input;
    public:
        CommandScanner(ScannerContext sc, std::istream input);

        void nextLine(char *(&line));

        Command asCommand(char *(&line)) const;

        Command nextCommand();

        Command *scan();

    };

}


#endif //OOPPROJECT_COMMANDSCANNER_HPP
