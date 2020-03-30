//
// Created by Kalelzar on 25/03/2020.
//

#ifndef OOPPROJECT_COMMANDINTERPRETER_HPP
#define OOPPROJECT_COMMANDINTERPRETER_HPP

#include "Command.hpp"
#include "../HotelState.hpp"
#include <iostream>

namespace Hotel {

    class CommandInterpreter {
    private:
    public:

        static void parse(HotelState &state, Command *commands);

        static void parse(HotelState &state, std::istream &input);

    };

}
#endif //OOPPROJECT_COMMANDINTERPRETER_HPP
