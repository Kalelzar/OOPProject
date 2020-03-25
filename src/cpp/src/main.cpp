#include<iostream>
#include <cstring>
#include "RoomList.hpp"

#define PRINT

using namespace Hotel;

int main(){

    RoomList rl(1);
    Room r(5);
    Room r2(1);
    
    rl.add(r);
    rl.add(r2);
    
    //
//
//    //EXPECT_EQ(rl.length(), 1);
//    //EXPECT_TRUE(rl.get(0) == r);
//    
//
//    //EXPECT_EQ(rl.length(), 2);
//    //EXPECT_TRUE(rl.get(1) == r2);
//    

}
