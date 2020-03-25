//
// Created by Kalelzar on 25/03/2020.
//

#include "Room.hpp"
#include "gtest/gtest.h"

using namespace Hotel;

TEST(Room, Constructor){
    Room r(0);
    EXPECT_EQ(r.getID(), 0);
    EXPECT_EQ(r.getState(), RoomState::FREE);
    EXPECT_TRUE(r.getStateFrom() == Date::today() );
    EXPECT_TRUE(r.getStateTo()   == Date::today() );
    EXPECT_STREQ(r.getNote(), "");
}

TEST(Room, SetNote){
    Room r(0);
    EXPECT_STREQ(r.getNote(), "");
    char str[] = "Banana Fish";
    r.setNote(str);
    EXPECT_STREQ(r.getNote(), str);
}

TEST(Room, SetState){
    Room r(0);
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