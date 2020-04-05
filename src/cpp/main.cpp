#include<iostream>
#include<cstdlib>
#include<ctime>
#include "src/HotelState.hpp"
#include <fstream>
#include "src/io/CommandScanner.hpp"

int main() {

    // srand(time(nullptr));
    // Hotel::HotelState state;
    // state.add({1,1});
    // state.add({2,2});
    // state.add({3,3});
    // state.checkin(1, {2020, 1, 1}, {2020, 1, 10}, "The Simpsons" );
    // state.unavailable(1, {2020, 1, 12}, {2020, 1, 24}, "Wut");
    // state.checkin(2, {2020, 1, 6}, {2020, 1, 6}, "d");
    // state.find(1, {2020, 1, 11}, {2020, 1, 11});
    // state.available({2020, 1, 12});
    // state.available({2020, 1, 6});
    // state.available();
    // state.report({2020, 1, 1}, {2020, 2, 1});
     // ArrayList<int> list;
     // for(int i = 0; i < 100000; i++){
     //     list.append(rand() % 100000);
     // }
     // unique_ptr<ArrayList<int>> slist = list.sort([](int const& a, int const& b){
     //               return a > b;
     //           });
     // for(unsigned i = 0; i < slist->length(); i++){
     //     std::cout<<slist->get(i)<<" ";
     // }
     // std::cout<<std::endl;

    Hotel::CommandList cl;
    cl.registerCommand("add", TokenType::TOKEN_ADD, ScannerContext::FILE);
    cl.registerCommand("remove", TokenType::TOKEN_REMOVE, ScannerContext::FILE);

    cl.registerCommand("checkin", TokenType::TOKEN_CHECKIN, ScannerContext::ALL);
    cl.registerCommand("checkout", TokenType::TOKEN_CHECKOUT, ScannerContext::ALL);
    cl.registerCommand("unavailable", TokenType::TOKEN_UNAVAILABLE, ScannerContext::ALL);

    cl.registerCommand("report", TokenType::TOKEN_REPORT, ScannerContext::CONSOLE);
    cl.registerCommand("find", TokenType::TOKEN_FIND, ScannerContext::CONSOLE);
    cl.registerCommand("find!", TokenType::TOKEN_FIND_F, ScannerContext::CONSOLE);
    cl.registerCommand("availability", TokenType::TOKEN_AVAILABILITY, ScannerContext::CONSOLE);

    cl.registerCommand("open", TokenType::TOKEN_OPEN, ScannerContext::CONSOLE);
    cl.registerCommand("close", TokenType::TOKEN_CLOSE, ScannerContext::CONSOLE);
    cl.registerCommand("help", TokenType::TOKEN_HELP, ScannerContext::CONSOLE);
    cl.registerCommand("exit", TokenType::TOKEN_EXIT, ScannerContext::CONSOLE);
    cl.registerCommand("save", TokenType::TOKEN_SAVE, ScannerContext::CONSOLE);
    cl.registerCommand("saveas", TokenType::TOKEN_SAVE_AS, ScannerContext::CONSOLE);

    ifstream file("test.htl");

    if(file.is_open()) {

        Hotel::CommandScanner scanner{ScannerContext::FILE, &file, cl};
        unique_ptr<ArrayList<Token>> tokens = scanner.scan();


        tokens->foreach([](Token const &token) mutable {
            std::cout << token << std::endl;
        });

        file.close();
    }

    return 0;
}
