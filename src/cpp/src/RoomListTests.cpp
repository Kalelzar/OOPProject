//
// Created by Kalelzar on 25/03/2020.
//

#include "RoomList.hpp"
#include "gtest/gtest.h"

using namespace Hotel;

TEST(RoomList, DefaultConstructor) {
    RoomList rl;
    EXPECT_EQ(rl.capacity(), RoomList::getDefaultReservedSpace());
    EXPECT_EQ(rl.length(), 0);
}

TEST(RoomList, Constructor) {
    int capacity = 4;
    RoomList rl(capacity);
    EXPECT_EQ(rl.capacity(), capacity);
    EXPECT_EQ(rl.length(), 0);
}

TEST(RoomList, AddGet) {
    RoomList rl;
    Room r(0, 1);
    Room r2(1, 1);
    EXPECT_EQ(rl.length(), 0);
    rl.add(r);
    EXPECT_EQ(rl.length(), 1);
    EXPECT_TRUE(rl.get(0) == r);
    rl.add(r2);
    EXPECT_EQ(rl.length(), 2);
    EXPECT_TRUE(rl.get(1) == r2);
}

TEST(RoomList, AddAll) {
    RoomList rl;
    Room r(0, 1);
    Room r2(1, 1);
    rl.add(r);
    rl.add(r2);
    RoomList newList;
    EXPECT_EQ(newList.length(), 0);
    newList.addAll(rl);
    EXPECT_EQ(newList.length(), rl.length());
    EXPECT_EQ(newList.capacity(), rl.capacity());
    EXPECT_TRUE(newList.get(0) == rl.get(0));
    EXPECT_TRUE(newList.get(1) == rl.get(1));
}

TEST(RoomList, Expand) {
    int capacity = 1;
    RoomList rl(capacity);
    EXPECT_EQ(rl.capacity(), capacity);
    for (int i = 0; i < capacity*4; i++) {
        rl.add(Room());
    }
    EXPECT_EQ(rl.capacity(), capacity * 4);
}

TEST(RoomList, Remove){
    RoomList rl;
    Room r1(1, 1);
    Room r2(2, 1);
    Room r3(3, 1);
    rl.add(r1);
    rl.add(r2);
    rl.add(r3);
    rl.remove(r2);
    EXPECT_EQ(rl.length(), 2);
    EXPECT_TRUE(rl.get(0) == r1);
    EXPECT_TRUE(rl.get(1) == r3);
}