#include "Stack.hpp"
#include "Room.hpp"
#include "gtest/gtest.h"

using namespace Hotel;

TEST(Stack, Push_Int){
    Stack<int> s;
    s.push(1);
    EXPECT_EQ(s.peek()->get(), 1);
    EXPECT_EQ(s.length(), 1);
    s.push(2);
    EXPECT_EQ(s.peek()->get(), 2);
    EXPECT_EQ(s.length(), 2);
}

TEST(Stack, Pop_Int){
    Stack<int> s;
    s.push(1);
    EXPECT_EQ(s.peek()->get(), 1);
    EXPECT_EQ(s.length(), 1);
    s.push(2);
    EXPECT_EQ(s.peek()->get(), 2);
    EXPECT_EQ(s.length(), 2);
    EXPECT_EQ(s.pop()->get(), 2);
    EXPECT_EQ(s.peek()->get(), 1);
    EXPECT_EQ(s.length(), 1);
    EXPECT_EQ(s.pop()->get(), 1);
    EXPECT_EQ(s.length(), 0);
}

TEST(Stack, Push_Room){
    Stack<Room> s;
    Room r1(1, 0);
    Room r2(2, 0);
    s.push(r1);
    EXPECT_TRUE(s.peek()->get() == r1);
    EXPECT_EQ(s.length(), 1);
    s.push(r2);
    EXPECT_TRUE(s.peek()->get() == r2);
    EXPECT_EQ(s.length(), 2);
}

TEST(Stack, Pop){
    Stack<Room> s;
    Room r1(1, 0);
    Room r2(2, 0);
    s.push(r1);
    EXPECT_TRUE(s.peek()->get() == r1);
    EXPECT_EQ(s.length(), 1);
    s.push(r2);
    EXPECT_TRUE(s.peek()->get() == r2);
    EXPECT_EQ(s.length(), 2);
    EXPECT_TRUE(s.pop()->get() == r2);
    EXPECT_TRUE(s.peek()->get() == r1);
    EXPECT_EQ(s.length(), 1);
    EXPECT_TRUE(s.pop()->get() == r1);
    EXPECT_EQ(s.length(), 0);
}
