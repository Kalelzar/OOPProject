//
// Created by Kalelzar on 26/03/2020.
//

#include "LinkedList.hpp"
#include "Room.hpp"
#include "gtest/gtest.h"

using namespace Hotel;

TEST(LinkedList, Constructor_Int){
    LinkedList<int> ll;
    EXPECT_EQ(ll.head(), int{});
    EXPECT_EQ(ll.last(), int{});
}

TEST(LinkedList, Append_Int){
    LinkedList<int> ll;
    ll.append(1);
    ll.append(2);
    EXPECT_EQ(ll.length(), 2);
    EXPECT_EQ(ll.head(), 1);
    EXPECT_EQ(ll.last(), 2);
}

TEST(LinkedList, Prepend_Int){
    LinkedList<int> ll;
    ll.prepend(1);
    ll.prepend(2);
    EXPECT_EQ(ll.length(), 2);
    EXPECT_EQ(ll.head(), 2);
    EXPECT_EQ(ll.last(), 1);
}

TEST(LinkedList, Insert_Int){
    LinkedList<int> ll;
    ll.append(1);
    ll.append(2);
    ll.insert(3, 1);
    EXPECT_EQ(ll.length(), 3);
    EXPECT_EQ(ll.head(), 1);
    EXPECT_EQ(ll.get(1), 3);
    EXPECT_EQ(ll.last(), 2);
}

TEST(LinkedList, Remove_Int){
    LinkedList<int> ll;
    ll.append(1);
    ll.append(2);
    ll.append(3);
    ll.remove(2);
    EXPECT_EQ(ll.length(), 2);
    EXPECT_EQ(ll.head(), 1);
    EXPECT_EQ(ll.last(), 3);
}

TEST(LinkedList, RemoveAt_Int){
    LinkedList<int> ll;
    ll.append(1);
    ll.append(2);
    ll.append(3);
    ll.removeAt(1);
    EXPECT_EQ(ll.length(), 2);
    EXPECT_EQ(ll.head(), 1);
    EXPECT_EQ(ll.last(), 3);
}

TEST(LinkedList, Pop_Int){
    LinkedList<int> ll;
    ll.append(1);
    ll.append(2);
    ll.append(3);
    ll.pop();
    EXPECT_EQ(ll.length(), 2);
    EXPECT_EQ(ll.head(), 1);
    EXPECT_EQ(ll.last(), 2);
}

TEST(LinkedList, Shift_Int){
    LinkedList<int> ll;
    ll.append(1);
    ll.append(2);
    ll.append(3);
    ll.shift();
    EXPECT_EQ(ll.length(), 2);
    EXPECT_EQ(ll.head(), 2);
    EXPECT_EQ(ll.last(), 3);
}

TEST(LinkedList, Constructor_Room){
    LinkedList<Room> ll;
    EXPECT_EQ(ll.head(), Room{});
    EXPECT_EQ(ll.last(), Room{});
}

TEST(LinkedList, Append_Room){
    LinkedList<Room> ll;
    Room r1(1, 0);
    Room r2(2, 0);
    ll.append(r1);
    ll.append(r2);
    EXPECT_EQ(ll.length(), 2);
    EXPECT_TRUE(ll.head() == r1);
    EXPECT_TRUE(ll.last() == r2);
}

TEST(LinkedList, Prepend_Room){
    LinkedList<Room> ll;
    Room r1(1, 0);
    Room r2(2, 0);
    ll.prepend(r1);
    ll.prepend(r2);
    EXPECT_EQ(ll.length(), 2);
    EXPECT_TRUE(ll.head() == r2);
    EXPECT_TRUE(ll.last() == r1);
}

TEST(LinkedList, Insert_Room){
    LinkedList<Room> ll;
    Room r1(1, 0);
    Room r2(2, 0);
    Room r3(3, 0);
    ll.append(r1);
    ll.append(r2);
    ll.insert(r3, 1);
    EXPECT_EQ(ll.length(), 3);
    EXPECT_TRUE(ll.head() ==r1);
    EXPECT_TRUE(ll.get(1) ==r3);
    EXPECT_TRUE(ll.last() ==r2);
}

TEST(LinkedList, Remove_Room){
    LinkedList<Room> ll;
    Room r1(1, 0);
    Room r2(2, 0);
    Room r3(3, 0);
    ll.append(r1);
    ll.append(r2);
    ll.append(r3);
    ll.remove(r2);
    EXPECT_EQ(ll.length(), 2);
    EXPECT_TRUE(ll.head() == r1);
    EXPECT_TRUE(ll.last() == r3);
}

TEST(LinkedList, RemoveAt_Room){
    LinkedList<Room> ll;
    Room r1(1, 0);
    Room r2(2, 0);
    Room r3(3, 0);
    ll.append(r1);
    ll.append(r2);
    ll.append(r3);
    ll.removeAt(1);
    EXPECT_EQ(ll.length(), 2);
    EXPECT_TRUE(ll.head() == r1);
    EXPECT_TRUE(ll.last() == r3);
}

TEST(LinkedList, Pop_Room){
    LinkedList<Room> ll;
    Room r1(1, 0);
    Room r2(2, 0);
    Room r3(3, 0);
    ll.append(r1);
    ll.append(r2);
    ll.append(r3);
    ll.pop();
    EXPECT_EQ(ll.length(), 2);
    EXPECT_TRUE(ll.head() == r1);
    EXPECT_TRUE(ll.last() == r2);
}

TEST(LinkedList, Shift_Room){
    LinkedList<Room> ll;
    Room r1(1, 0);
    Room r2(2, 0);
    Room r3(3, 0);
    ll.append(r1);
    ll.append(r2);
    ll.append(r3);
    ll.shift();
    EXPECT_EQ(ll.length(), 2);
    EXPECT_TRUE(ll.head() == r2);
    EXPECT_TRUE(ll.last() == r3);
}