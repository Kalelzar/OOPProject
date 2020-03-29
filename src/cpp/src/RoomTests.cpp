//
// Created by Kalelzar on 25/03/2020.
//

#include "Room.hpp"
#include "gtest/gtest.h"

using namespace Hotel;


TEST(RoomStateEvent, Equals){
    RoomStateEvent rse1 = {RoomState::FREE, {1, 1}, {2020, 2, 1}, {2020, 2, 10}};
    RoomStateEvent rse2 = {RoomState::TAKEN, {1, 1}, {2020, 2, 1}, {2020, 2, 10}};
    RoomStateEvent rse3 = {RoomState::FREE, {1, 1}, {2020, 2, 11}, {2020, 2, 20}};
    RoomStateEvent rse4 = {RoomState::FREE, {1, 1}, {2020, 1, 15}, {2020, 1, 31}};
    EXPECT_TRUE(rse1 == rse1);
    EXPECT_FALSE(rse1 == rse2);
    EXPECT_FALSE(rse1 == rse3);
    EXPECT_FALSE(rse1 == rse4);
}

TEST(RoomStateEvent, NotEquals){
    RoomStateEvent rse1 = {RoomState::FREE, {1, 1}, {2020, 2, 1}, {2020, 2, 10}};
    RoomStateEvent rse2 = {RoomState::TAKEN, {1, 1}, {2020, 2, 1}, {2020, 2, 10}};
    RoomStateEvent rse3 = {RoomState::FREE, {1, 1}, {2020, 2, 11}, {2020, 2, 20}};
    RoomStateEvent rse4 = {RoomState::FREE, {1, 1}, {2020, 1, 15}, {2020, 1, 31}};
    EXPECT_FALSE(rse1 != rse1);
    EXPECT_TRUE(rse1 != rse2);
    EXPECT_TRUE(rse1 != rse3);
    EXPECT_TRUE(rse1 != rse4);
}

TEST(RoomStateEvent, Greater){
    RoomStateEvent rse1 = {RoomState::FREE, {1, 1}, {2020, 2, 1}, {2020, 2, 10}};
    RoomStateEvent rse2 = {RoomState::TAKEN, {1, 1}, {2020, 2, 1}, {2020, 2, 10}};
    RoomStateEvent rse3 = {RoomState::FREE, {1, 1}, {2020, 2, 11}, {2020, 2, 20}};
    RoomStateEvent rse4 = {RoomState::FREE, {1, 1}, {2020, 1, 15}, {2020, 1, 31}};
    RoomStateEvent rse5 = {RoomState::FREE, {1, 1}, {2020, 2, 1}, {2020, 2, 20}};
    RoomStateEvent rse6 = {RoomState::FREE, {1, 1} , {2020, 1, 15}, {2020, 2, 10}};
    EXPECT_FALSE(rse1 > rse1);
    EXPECT_FALSE(rse1 > rse2);
    EXPECT_FALSE(rse1 > rse3);
    EXPECT_TRUE (rse1 > rse4);
    EXPECT_FALSE(rse1 > rse5);
    EXPECT_FALSE(rse1 > rse6);
}

TEST(RoomStateEvent, GreaterEq){
    RoomStateEvent rse1 = {RoomState::FREE, {1, 1}, {2020, 2, 1}, {2020, 2, 10}};
    RoomStateEvent rse2 = {RoomState::TAKEN, {1, 1}, {2020, 2, 1}, {2020, 2, 10}};
    RoomStateEvent rse3 = {RoomState::FREE, {1, 1}, {2020, 2, 11}, {2020, 2, 20}};
    RoomStateEvent rse4 = {RoomState::FREE, {1, 1}, {2020, 1, 15}, {2020, 1, 31}};
    RoomStateEvent rse5 = {RoomState::FREE, {1, 1}, {2020, 2, 1}, {2020, 2, 20}};
    RoomStateEvent rse6 = {RoomState::FREE, {1, 1} , {2020, 1, 15}, {2020, 2, 10}};
    EXPECT_TRUE (rse1 >= rse1);
    EXPECT_TRUE (rse1 >= rse2);
    EXPECT_FALSE(rse1 >= rse3);
    EXPECT_TRUE (rse1 >= rse4);
    EXPECT_TRUE (rse1 >= rse5);
    EXPECT_TRUE (rse1 >= rse6);
}

TEST(RoomStateEvent, Less){
    RoomStateEvent rse1 = {RoomState::FREE, {1, 1}, {2020, 2, 1}, {2020, 2, 10}};
    RoomStateEvent rse2 = {RoomState::TAKEN, {1, 1}, {2020, 2, 1}, {2020, 2, 10}};
    RoomStateEvent rse3 = {RoomState::FREE, {1, 1}, {2020, 2, 11}, {2020, 2, 20}};
    RoomStateEvent rse4 = {RoomState::FREE, {1, 1}, {2020, 1, 15}, {2020, 1, 31}};
    RoomStateEvent rse5 = {RoomState::FREE, {1, 1}, {2020, 2, 1}, {2020, 2, 20}};
    RoomStateEvent rse6 = {RoomState::FREE, {1, 1} , {2020, 1, 15}, {2020, 2, 10}};
    EXPECT_FALSE(rse1 < rse1);
    EXPECT_FALSE(rse1 < rse2);
    EXPECT_TRUE (rse1 < rse3);
    EXPECT_FALSE(rse1 < rse4);
    EXPECT_FALSE(rse1 < rse5);
    EXPECT_FALSE(rse1 < rse6);
}

TEST(RoomStateEvent, LessEq){
    RoomStateEvent rse1 = {RoomState::FREE, {1, 1}, {2020, 2, 1}, {2020, 2, 10}};
    RoomStateEvent rse2 = {RoomState::TAKEN, {1, 1}, {2020, 2, 1}, {2020, 2, 10}};
    RoomStateEvent rse3 = {RoomState::FREE, {1, 1}, {2020, 2, 11}, {2020, 2, 20}};
    RoomStateEvent rse4 = {RoomState::FREE, {1, 1}, {2020, 1, 15}, {2020, 1, 31}};
    RoomStateEvent rse5 = {RoomState::FREE, {1, 1}, {2020, 2, 1}, {2020, 2, 20}};
    RoomStateEvent rse6 = {RoomState::FREE, {1, 1} , {2020, 1, 15}, {2020, 2, 10}};
    EXPECT_TRUE (rse1 <= rse1);
    EXPECT_TRUE (rse1 <= rse2);
    EXPECT_TRUE (rse1 <= rse3);
    EXPECT_FALSE(rse1 <= rse4);
    EXPECT_TRUE (rse1 <= rse5);
    EXPECT_TRUE (rse1 <= rse6);
}

TEST(Room, Constructor){
    Room r(0, 3);
    EXPECT_EQ(r.getID(), 0);
    EXPECT_EQ(r.getBeds(), 3);
    EXPECT_STREQ(r.getNote(), "");
}

TEST(Room, SetNote){
    Room r(0, 1);
    EXPECT_STREQ(r.getNote(), "");
    char str[] = "Banana Fish";
    r.setNote(str);
    EXPECT_STREQ(r.getNote(), str);
}

TEST(Room, Equality){
    Room r1(0, 1);
    Room r2(1, 1);
    Room r3(0, 5);
    EXPECT_TRUE(r1 == r3);
    EXPECT_FALSE(r1 == r2);
    EXPECT_FALSE(r2 == r3);
}


TEST(Room, Unequality){
    Room r1(0, 1);
    Room r2(1, 1);
    Room r3(0, 5);
    EXPECT_FALSE(r1 != r3);
    EXPECT_TRUE(r1 != r2);
    EXPECT_TRUE(r2 != r3);
}
