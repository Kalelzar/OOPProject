//
// Created by Kalelzar on 25/03/2020.
//

#include "Room.hpp"
#include "gtest/gtest.h"

using namespace Hotel;

TEST(Room, Constructor){
    Room r(0, 3);
    EXPECT_EQ(r.getID(), 0);
    EXPECT_EQ(r.getBeds(), 3);
    EXPECT_EQ(r.getState(), RoomState::FREE);
    EXPECT_TRUE(r.getStateFrom() == Date::today() );
    EXPECT_TRUE(r.getStateTo()   == Date::today() );
    EXPECT_STREQ(r.getNote(), "");
}

TEST(Room, SetNote){
    Room r(0, 1);
    EXPECT_STREQ(r.getNote(), "");
    char str[] = "Banana Fish";
    r.setNote(str);
    EXPECT_STREQ(r.getNote(), str);
}

TEST(Room, SetState){
    Room r(0, 1);
    EXPECT_EQ(r.getState(), RoomState::FREE);
    EXPECT_TRUE(r.getStateFrom() == Date::today() );
    EXPECT_TRUE(r.getStateTo()   == Date::today() );

    RoomState rs = RoomState::TAKEN;
    Date begin(2020, 1, 1);
    Date end(2020, 1, 10);

    r.setState(rs, begin, end);

    EXPECT_EQ(r.getState(), rs);
    EXPECT_TRUE(r.getStateFrom() == begin );
    EXPECT_TRUE(r.getStateTo()   == end );
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