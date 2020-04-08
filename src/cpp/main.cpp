#include<iostream>
#include<cstdlib>
#include<ctime>
#include "src/HotelState.hpp"
#include <fstream>
#include "src/io/CommandScanner.hpp"
#include  "src/parser/CommandInterpreter.hpp"
int main() {

    Hotel::CommandList cl;

    cl.registerCommand("add", TokenType::TOKEN_ADD, ScannerContext::FILE,
                       " <room> <beds> : Add a new room to the database. (File only)" );
    cl.registerCommand("remove", TokenType::TOKEN_REMOVE, ScannerContext::FILE,
                       " <room> : Remove room from database. (File only)" );

    cl.registerCommand("checkin", TokenType::TOKEN_CHECKIN, ScannerContext::ALL,
                       " <room> <from> <to> <note> : Marks <room> as taken for the period <from> <to>. Also attaches a <note> to the check-in event." );
    cl.registerCommand("checkout", TokenType::TOKEN_CHECKOUT, ScannerContext::ALL,
                       " <room> [date]: If the room is marked taken for a period that includes [date] (defaults to today)\n"
                       " then mark the room as free from <date> until the end of the period.");
    cl.registerCommand("unavailable", TokenType::TOKEN_UNAVAILABLE, ScannerContext::ALL,
                       " <room> <from> <to> <note> : Marks <room> as unavailable for the period <from> <to>. Also attaches a <note> to the unavailable event." );

    cl.registerCommand("report", TokenType::TOKEN_REPORT, ScannerContext::CONSOLE,
                       " <from> <to> : Display when rooms are taken or unavailable for the period <from> <to> (Console only)" );
    cl.registerCommand("find", TokenType::TOKEN_FIND, ScannerContext::CONSOLE,
                       " <beds> <from> <to> : Find a room with at least <beds> beds that is free <from> <to> (Console only)" );
    cl.registerCommand("find!", TokenType::TOKEN_FIND_F, ScannerContext::CONSOLE,
                       " <beds> <from> <to> : Find a room with at least <beds> beds that can be free <from> <to> if the occupants of at most two rooms are moved (Console only)" );
    cl.registerCommand("availability", TokenType::TOKEN_AVAILABILITY, ScannerContext::CONSOLE,
                       " [date] : show all rooms that are free on [date] (defaults to today) (Console only)" );

    cl.registerCommand("open", TokenType::TOKEN_OPEN, ScannerContext::CONSOLE,
                       " <filepath> : Open file at <filepath> (Console only)" );
    cl.registerCommand("close", TokenType::TOKEN_CLOSE, ScannerContext::CONSOLE,
                       " : Close currently opened file. Does not save the file. (Console only)" );
    cl.registerCommand("help", TokenType::TOKEN_HELP, ScannerContext::CONSOLE,
                       " : Displays this message (Console only)" );
    cl.registerCommand("exit", TokenType::TOKEN_EXIT, ScannerContext::CONSOLE,
                       " : Exits the program. (Console only)" );
    cl.registerCommand("save", TokenType::TOKEN_SAVE, ScannerContext::CONSOLE,
                       " : Saves the file if necessary. (Console only)" );
    cl.registerCommand("saveas", TokenType::TOKEN_SAVE_AS, ScannerContext::CONSOLE,
                       " <filepath> : Saves the file to <filepath>. Also sets the currently active file to <filepath>" );

    Hotel::CommandList::setCommandList(cl);

    Hotel::HotelState state;

    Hotel::CommandScanner scanner{ScannerContext::CONSOLE, &std::cin, cl};
    bool run = true;
    while(run){
        if(strlen(state.getFile()) != 0){
            std::cout<<"["<<state.getFile()<<"]";
        }
        std::cout<<"$ ";
        shared_ptr<ArrayList<Token>> tokens = scanner.scanNext();
        // tokens->foreach([](Token const &token) mutable {
        //                     std::cout << token << std::endl;
        //                 });
        Hotel::CommandInterpreter ci(tokens);
        run = ci.parse(state);
    }


    return 0;
}
