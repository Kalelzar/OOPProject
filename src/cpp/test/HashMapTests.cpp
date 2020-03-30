//
// Created by Kalelzar on 27/03/2020.
//

#include "../src/collection/HashMap.hpp"
#include "../src/Room.hpp"
#include "gtest/gtest.h"

TEST(HashMap, Put) {
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

TEST(HashMap, Remove) {
    HashMap<int, int> map;
    map.put(1, 2);
    EXPECT_EQ(map.length(), 1);
    EXPECT_EQ(map.get(1)->get(), 2);
    map.remove(1);
    EXPECT_EQ(map.length(), 0);
    EXPECT_EQ(map.get(1)->getOrElse(-1), -1);
}

TEST(HashMap, GetEntries) {
    HashMap<int, int> map;
    map.put(2, 5);
    Entry<int, int> entry = {2, 5, false};
    bool found = false;
    for (unsigned i = 0; i < map.capacity(); i++) {
        found = map.underlying()[i] == entry;
        if (found) break;
    }
    ASSERT_TRUE(found);
}

TEST(HashMap, Clear) {
    HashMap<int, int> map;
    map.put(2, 5);
    Entry<int, int> entry = {2, 5, false};
    bool found = false;
    for (unsigned i = 0; i < map.capacity(); i++) {
        found = map.underlying()[i] == entry;
        if (found) break;
    }
    ASSERT_TRUE(found);
    map.clear();
    found = false;
    for (unsigned i = 0; i < map.capacity(); i++) {
        found = map.underlying()[i] == entry;
        if (found) break;
    }
    ASSERT_FALSE(found);
}
