//
// Created by Kalelzar on 27/03/2020.
//

#include "HashMap.hpp"
#include "Room.hpp"
#include "gtest/gtest.h"

TEST(HashMap, Put){
    HashMap<int, int> map;
    map.put(1, 1);
    map.put(2, 2);
    EXPECT_EQ(map.length(), 2);
    EXPECT_EQ(map.get(1)->get(), 1);
    EXPECT_EQ(map.get(2)->get(), 2);
    map.put(1, 2);
    EXPECT_EQ(map.length(), 2);
    EXPECT_EQ(map.get(1)->get(), 2);
    EXPECT_THROW(map.get(3)->get(), NoValueException);
}
