#include<iostream>
#include<cstdlib>
#include<ctime>
#include "src/HotelState.hpp"
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
    cl.registerCommand("checkin", TokenType::TOKEN_CHECKIN, ScannerContext::ALL);

    cl.printCommands();

    Hotel::CommandScanner scanner {ScannerContext::CONSOLE, &std::cin, cl};

    unique_ptr<ArrayList<Token>> tokens = scanner.scanNext();



    tokens->foreach([](Token const& token){
                      std::cout<<token<<std::endl;
                 });


    return 0;
}
